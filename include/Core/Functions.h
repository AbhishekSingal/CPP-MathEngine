//
// Created by Abhishek Singal on 13/07/25.
//

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <MathEngine.h>

namespace MathEngine {
    namespace Core {
        namespace Functions {
            inline Rational Sin(Rational x) {
                return std::sin(x);
            }

            inline Rational Cos(Rational x) {
                return std::cos(x);
            }

            inline Rational Tan(Rational x) {
                return std::tan(x);
            }

            inline Rational Cosec(Rational x) {
                return 1/std::sin(x);
            }

            inline Rational Sec(Rational x) {
                return 1/std::cos(x);
            }

            inline Rational Cot(Rational x) {
                return 1/std::tan(x);
            }

            inline Rational Modulus(Rational x) {
                return std::abs(x);
            }

            inline Rational Sqrt(Rational x) {
                return std::sqrt(x);
            }

            inline Rational Arcsin(Rational x) {
                return std::asin(x);
            }

            inline Rational Arccos(Rational x) {
                return std::acos(x);
            }

            inline Rational Arctan(Rational x) {
                return std::atan(x);
            }

            inline Rational Arccosec(Rational x) {
                return std::asin(1 / x);
            }

            inline Rational Arcsec(Rational x) {
                return std::acos(1 / x);
            }

            inline Rational Arccot(Rational x) {
                return std::atan(1 / x);
            }

            inline Rational Log10(Rational x) {
                return std::log10(x);
            }

            inline Rational Loge(Rational x) {
                return std::log(x);
            }

            inline Rational Log(Rational base , Rational val) {
                return std::log(val)/std::log(base);
            }

            inline Rational Pow(Rational r , Rational n) {
                return std::pow(r, n);
            }

            inline Rational Exp(Rational x) {
                return std::exp(x);
            }

            inline Rational SinH(Rational x) {
                return std::sinh(x);
            }

            inline Rational CosH(Rational x) {
                return std::cosh(x);
            }

            inline Rational TanH(Rational x) {
                return std::tanh(x);
            }


        }
    }
}

#endif //FUNCTIONS_H
