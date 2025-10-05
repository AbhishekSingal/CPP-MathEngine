//
// Created by Abhishek Singal on 12/07/25.
//

#include <Core/Complex.h>

#include "../../include/Core/Utils.h"

namespace MathEngine {
    namespace Core {
        const Complex Complex::Iota = Complex(0,1);

        Complex::Complex(Rational real) {
            this->real = real;
            this->imaginary = 0;
        }

        Complex::Complex(Rational real, Rational imaginary) {
            this->real = real;
            this->imaginary = imaginary;
        }

        Complex Complex::FromPolar(Rational mod, Rational argument, bool radians) {
            Complex result;
            Rational r = mod;
            if (!radians) {
                argument = Utils::ToRadians(argument);
            }

            result.real = r * Functions::Cos(argument);
            result.imaginary = r * Functions::Sin(argument);

            return result;

        }

        std::vector<Complex> Complex::GetNthRootsOfUnity(int n) {
            std::vector<Complex> roots;
            if (n <= 0) return roots;

            const Rational twoPi = 2 * Constants::Pi;
            const Rational step = twoPi / Rational(n);

            for (int k = 0; k < n; ++k) {
                Rational angle = step * k;
                Complex root = Complex::FromPolar(Rational(1), angle, true);
                roots.push_back(root);
            }

            return roots;
        }

        Rational Complex::Real() const {
            return this->real;
        }

        Rational Complex::Imaginary() const {
            return this->imaginary;
        }

        Rational Complex::Modulus() const {
            return Functions::Sqrt(this->real * this->real + this->imaginary * this->imaginary);
        }

        Rational Complex::Argument(bool radians) const {
            if (radians) {
                return std::atan2(this->imaginary, this->real);
            }
            else {
                return Utils::ToDegrees(std::atan2(this->imaginary, this->real));
            }
        }

        void Complex::setReal(Rational real) {
            this->real = real;
        }

        void Complex::setImaginary(Rational imaginary) {
            this->imaginary = imaginary;
        }


        Complex Complex::Conjugate() const {
            return Complex(real, -imaginary);
        }

        Complex Complex::Pow(Rational n) const {
            Rational r = Functions::Pow(Modulus(),n);
            Rational arg = n*Argument();
            return Complex(Utils::Round(r*Functions::Cos(arg),10), Utils::Round(r*Functions::Sin(arg),10));
        }

        Complex Complex::Inverse() const {
            return 1/(*this);
        }

        Complex Complex::Normalized() const {
            return (*this)/Modulus();
        }

        Complex Complex::Rotate(Rational angle,bool radians) const {
            return Complex::FromPolar(1, angle,radians)*(*this);
        }


        std::string Complex::toString() const {
            std::ostringstream os;
            Rational r = Utils::Round(real,10);
            Rational imag =Utils::Round(imaginary,10);

            if (r > 0 && imag > 0) {
                os << Utils::GetRationalString(r) << " + " << (imag != 1 ?  Utils::GetRationalString(imag) : "") << "i";
            }
            else if (r > 0 && imag < 0) {
                os << Utils::GetRationalString(r) << " - " <<(imag != -1 ?  Utils::GetRationalString(Functions::Modulus(imag)) : "") << "i";
            }
            else if (r < 0 && imag > 0) {
                os << Utils::GetRationalString(r) << " + " << (imag != 1 ?  Utils::GetRationalString(imag) : "") << "i";
            }
            else if (r < 0 && imag < 0) {
                os << Utils::GetRationalString(r) << " - " << (imag != -1 ?  Utils::GetRationalString(Functions::Modulus(imag)) : "")<< "i";
            }
            else if (r != 0 && imag == 0) {
                os << Utils::GetRationalString(r) ;
            }
            else if (r == 0 && imag != 0) {
                if (imag != 1 && imag != -1) {
                    os << imag << "i";
                }
                else if (imag == 1) {
                    os << "i";
                }
                else if (imag == -1) {
                    os << "-i";
                }
            }
            else if (r == 0 && imag == 0) {
                os << 0;
            }
            return os.str();
        }

        Complex Complex::operator+(const Complex &f) const {
            Complex result(this->real + f.real, this->imaginary + f.imaginary);
            return result;
        }

        Complex Complex::operator-(const Complex &f) const {
            Complex result(this->real - f.real, this->imaginary - f.imaginary);
            return result;
        }

        Complex Complex::operator*(const Complex &f) const {
            Complex result(this->real*f.real - this->imaginary*f.imaginary, this->imaginary*f.real + this->real*f.imaginary);
            return result;
        }

        Complex Complex::operator/(const Complex &f) const {
            Complex d_conj = f*f.Conjugate();
            Complex numerator = *this * f.Conjugate();
            Complex result(numerator.Real()/d_conj.Real(), numerator.Imaginary()/d_conj.Real());
            return result;
        }

        Complex Complex::operator-() const {
            return Complex(-real,-imaginary);
        }

        bool Complex::operator==(const Complex &other) const {
            return real == other.real && imaginary == other.imaginary;
        }

        bool Complex::operator!=(const Complex &other) const {
            return real != other.real || imaginary != other.imaginary;
        }

        Complex::operator std::string() const {
            return this->toString();
        }

        Complex operator+(Rational r, const Complex &c) {
            return Complex(r,0) + c;
        }

        Complex operator-(Rational r, const Complex &c) {
            return Complex(r,0) - c;
        }

        Complex operator*(Rational r, const Complex &c) {
            return Complex(r,0) * c;
        }

        Complex operator/(Rational r, const Complex &c) {
            return Complex(r,0)/c;
        }


        std::ostream & operator<<(std::ostream &os, const Complex &f) {
            os << f.toString();
            return os;
        }


        Core::Complex Functions::Pow(Core::Complex c, Rational n) {
            return c.Pow(n);
        }

        Core::Complex Functions::Sqrt(Core::Complex c) {
            return c.Pow(0.5);
        }

        Rational Functions::Modulus(Core::Complex c) {
            return c.Modulus();
        }

        Core::Complex Functions::Sin(Core::Complex c) {
            return Core::Complex(
                    Sin(c.Real())*CosH(c.Imaginary()),
                    Cos(c.Real())*SinH(c.Imaginary())
                );
        }

        Core::Complex Functions::Cos(const Core::Complex c) {
            return Core::Complex(
                Cos(c.Real()) * CosH(c.Imaginary()),
                -Sin(c.Real()) * SinH(c.Imaginary())
            );
        }

        Core::Complex Functions::Tan(Core::Complex c) {
            return Sin(c)/Cos(c);
        }

        Core::Complex Functions::Cosec(Core::Complex c) {
            return 1/Sin(c);
        }

        Core::Complex Functions::Sec(Core::Complex c) {
            return 1/Cos(c);
        }

        Core::Complex Functions::Cot(Core::Complex c) {
            return 1/Tan(c);
        }

        Core::Complex Functions::Loge(Core::Complex c) {
            return Core::Complex(
                std::log(c.Modulus()),
                c.Argument()
            );
        }

        Core::Complex Functions::Log10(Core::Complex c) {
            return Loge(c)/Loge(10);
        }

        Core::Complex Functions::Log(Rational base, Core::Complex c) {
            return Loge(c)/Loge(base);
        }

        Core::Complex Functions::Exp(Core::Complex c) {
            return Exp(c.Real())*Complex(Cos(c.Imaginary()),Sin(c.Imaginary()));
        }
    }
}

