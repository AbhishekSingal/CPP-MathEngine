//
// Created by Abhishek Singal on 10/07/25.
//

#include <Core/Function.h>
#include <Core/Utils.h>

#include "Core/Complex.h"

using MathEngine::Core::Functions::Pow;
using MathEngine::Core::Functions::Sqrt;
using MathEngine::Core::Functions::Modulus;


namespace MathEngine {
    namespace Core{
        Function::Function(std::string fx) {
            this->fx = fx;

            std::string t_exp = "";
            for (int i = 0; i < this->fx.length(); i++) {
                if (this->fx[i] != ' ') {
                    t_exp += this->fx[i];
                }
            }

            this->fx = t_exp;

            std::string sub_exp = "";
            for (size_t i = 0; i < this->fx.length(); ++i) {
                char c = this->fx[i];
                if (c != 'x') {
                    sub_exp += c;
                }else {
                    if (i > 0) {
                        char prev = this->fx[i - 1];

                        if (std::isdigit(prev) || std::isalpha(prev) || prev == ')') {
                            sub_exp += '*';
                        }
                    }
                    if (sub_exp != "")
                        compiled_fx.push_back(sub_exp);
                    compiled_fx.push_back("x");
                    sub_exp = "";
                }
            }

            compiled_fx.push_back(sub_exp);

        }


        Rational Function::evaluateAt(Rational x) {
            std::string exp = "";
            std::string x_str = Utils::GetRationalString(x);
            for (int i = 0 ; i < compiled_fx.size(); i++) {
                std::string token = compiled_fx[i];
                if (token == "x") {
                    exp += x_str;
                }else {
                    exp += token;
                }
            }
            return evaluator.evaluateExpression(exp);
        }

        Rational Function::LimitRH(Rational x) {
            return evaluateAt(x+0.0000000001);
        }

        Rational Function::LimitLH(Rational x) {
            return evaluateAt(x-0.0000000001);
        }

        Rational Function::Limit(Rational x) {
            if (Utils::Round(LimitRH(x),3) == Utils::Round(LimitLH(x),3)) { return LimitLH(x); }
            return NAN;
        }


        Rational Function::DifferentiateAt(Rational x) {
            Rational dx = 0.0000000001;
            Rational dy = evaluateAt(x + dx) - evaluateAt(x - dx);

            return Utils::Round(dy / (2 * dx), 5);
        }

        Rational Function::DefiniteIntegral(Rational lowerLimit, Rational upperLimit,int n) {
            Rational dx = (upperLimit - lowerLimit) / n;
            Rational x = lowerLimit;
            Rational fh1 = evaluateAt(lowerLimit);
            Rational fh2 ;

            Rational area = 0;
            while (x <= upperLimit) {
                fh2 = evaluateAt(x + dx);
                Rational da = ((fh1+fh2)*dx)/2;
                area += da;
                fh1 = fh2;
                x += dx;
            }

            return area;

        }

        Rational Function::FindRoot(Rational a, Rational b, Rational tolerance) {
            Rational fa = evaluateAt(a);
            Rational fb = evaluateAt(b);

            if (std::abs(fa) < tolerance) return a;
            if (std::abs(fb) < tolerance) return b;

            if (fa * fb > 0) {
                throw std::runtime_error("Root not guaranteed: f(a) and f(b) must have opposite signs");
            }

            Rational mid, fmid;
            int maxIterations = 1000;

            for (int i = 0; i < maxIterations && (b - a) > tolerance; ++i) {
                mid = (a + b) / 2;
                fmid = evaluateAt(mid);

                if (std::abs(fmid) < tolerance) return mid;

                if (fa * fmid < 0) {
                    b = mid;
                    fb = fmid;
                } else {
                    a = mid;
                    fa = fmid;
                }
            }

            return (a + b) / 2;
        }

    }
}
