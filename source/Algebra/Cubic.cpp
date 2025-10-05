//
// Created by Abhishek Singal on 15/07/25.
//

#include <Algebra/Cubic.h>

#include "Core/Utils.h"

using namespace MathEngine::Core;
using namespace MathEngine::Core::Functions;
using namespace MathEngine::Core::Utils;
namespace MathEngine {
    namespace Algebra {

        Cubic::Cubic(Rational a, Rational b, Rational c, Rational d) {
            this->a = a;
            this->b = b;
            this->c = c;
            this->d = d;
        }

        Cubic::Cubic(Rational sum, Rational pairwiseSum, Rational product) {
            a = 1;
            b = -sum;
            c = pairwiseSum;
            d = -product;
        }

        std::vector<Rational> Cubic::GetRealRoots() {
            std::vector<Complex> c_roots = GetComplexRoots();
            std::vector<Rational> roots;
            for (int i = 0; i < c_roots.size(); ++i) {
                if (c_roots[i].Imaginary() == 0) {
                    roots.push_back(c_roots[i].Real());
                }
            }
            return roots;
        }

        std::vector<Complex> Cubic::GetComplexRoots() {
            std::vector<Complex> roots;

            // Compute Δ0 and Δ1
            Rational delta0 = b*b - 3*a*c;
            Rational delta1 = 2*b*b*b - 9*a*b*c + 27*a*a*d;

            // Compute discriminant D = Δ1^2 - 4*Δ0^3
            Rational discriminant = delta1*delta1 - 4*delta0*delta0*delta0;

            // Function to compute complex cube root of a complex number
            auto ComplexCubeRoot = [](const Complex& z) -> Complex {
                double r = std::pow(z.Modulus(), 1.0 / 3.0);
                double theta = z.Argument() / 3.0;
                return Complex(r * std::cos(theta), r * std::sin(theta));
            };

            Complex C;
            // Compute C = cube root of (Δ1 ± sqrt(Δ1^2 - 4Δ0^3)) / 2
            if (discriminant >= 0) {
                Rational sqrtD = Sqrt(discriminant);
                Complex candidate1((delta1 + sqrtD) / 2, 0);
                Complex candidate2((delta1 - sqrtD) / 2, 0);

                // Choose the one with larger modulus to avoid division by zero
                C = (candidate1.Modulus() >= candidate2.Modulus()) ? ComplexCubeRoot(candidate1) : ComplexCubeRoot(candidate2);
            } else {
                Complex sqrtD(delta1 / 2.0, Sqrt(-discriminant) / 2.0);
                C = ComplexCubeRoot(sqrtD);
            }

            // Handle special case: C ≈ 0 (triple root)
            if (C.Modulus() < 1e-10) {
                Complex tripleRoot = Complex(-b / (3.0 * a), 0);
                for (int i = 0; i < 3; ++i)
                    roots.push_back(tripleRoot);
                return roots;
            }

            // Cube roots of unity: 1, w, w^2
            Complex w1(-0.5, std::sqrt(3) / 2);
            Complex w2(-0.5, -std::sqrt(3) / 2);

            std::vector<Complex> omega = { Complex(1, 0), w1, w2 };

            for (int k = 0; k < 3; ++k) {
                Complex omegaK = omega[k];
                Complex term1 = omegaK * C;
                Complex term2 = delta0 / (omegaK * C);
                Complex root = (-1.0 / (3.0 * a)) * (b + term1 + term2);

                // Round to 6 decimal places
                root.setReal(Utils::Round(root.Real(), 6));
                root.setImaginary(Utils::Round(root.Imaginary(), 6));
                roots.push_back(root);
            }

            return roots;
        }

        Rational Cubic::EvaluateAt(Rational x) {
            return a*Pow(x,3) + b*Pow(x,2) + c*x + d;
        }

        Complex Cubic::EvaluateAt(Complex x) {
            return a*Pow(x,3) + b*Pow(x,2) + c*x + d;
        }

        Rational Cubic::DifferentiateAt(Rational x) {
            return 3*a*Pow(x,2) + 2*b*x + c;
        }

        Rational Cubic::DefiniteIntegral(Rational lowerLimit, Rational upperLimit) {
            Rational U = a*Pow(upperLimit,4)/4 + b*Pow(upperLimit,3)/3 + c*Pow(upperLimit,2)/2 + d*upperLimit;
            Rational L = a*Pow(lowerLimit,4)/4 + b*Pow(lowerLimit,3)/3 + c*Pow(lowerLimit,2)/2 + d*lowerLimit;
            return U-L;
        }
    }
}