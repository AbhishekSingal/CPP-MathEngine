//
// Created by Abhishek Singal on 15/07/25.
//


#include <Algebra/Quadratic.h>

using namespace MathEngine::Core;
using namespace MathEngine::Core::Functions;

namespace MathEngine {
    namespace Algebra {
        Quadratic::Quadratic(Rational a, Rational b, Rational c) {
            this->a = a;
            this->b = b;
            this->c = c;
        }

        Quadratic::Quadratic(Rational sum, Rational product) {
            a = 1;
            b = -sum;
            c = product;
        }

        Rational Quadratic::Discriminant() {
            return Functions::Pow(b,2) - 4*a*c;
        }

        std::pair<Rational, Rational> Quadratic::GetRealRoots() {
            Rational d = Discriminant();
            Rational r1;
            Rational r2;
            if (d >= 0) {
                r1 = (-b + Functions::Sqrt(d))/2*a;
                r2 = (-b - Functions::Sqrt(d))/2*a;
            }

            return std::make_pair(r1,r2);
        }

        std::pair<Complex, Complex> Quadratic::GetComplexRoots() {
            Rational d = Discriminant();
            Complex r1;
            Complex r2;
            r1 = (-b + Sqrt(Modulus(d)) * Complex::Iota)/2*a;
            r2 = (-b - Sqrt(Modulus(d)) * Complex::Iota)/2*a;
            return std::make_pair(r1,r2);
        }

        Rational Quadratic::EvaluateAt(Rational x) {
            return a*x*x + b*x + c;
        }

        Complex Quadratic::EvaluateAt(Complex x) {
            return a*x*x + b*x + c;
        }

        Rational Quadratic::DifferentiateAt(Rational x) {
            return 2*a*x + b*x;
        }

        Rational Quadratic::DefiniteIntegral(Rational lowerLimit, Rational upperLimit) {
            Rational U = a*Pow(upperLimit,3)/3 + b*Pow(upperLimit,2)/2 + c*upperLimit;
            Rational L = a*Pow(lowerLimit,3)/3 + b*Pow(lowerLimit,2)/2 + c*lowerLimit;
            return U-L;
        }
    }
}
