//
// Created by Abhishek Singal on 12/07/25.
//

#ifndef COMPLEX_H
#define COMPLEX_H

#include <MathEngine.h>
#include <Core/Functions.h>
#include <sstream>

namespace MathEngine {
    namespace Core {
        class Complex {
        protected:
            Rational real;
            Rational imaginary;


        public:
            Complex(){;};
            Complex(Rational real);
            Complex(Rational real, Rational imaginary);
            static Complex FromPolar(Rational mod , Rational argument , bool radians = true);
            static std::vector<Complex> GetNthRootsOfUnity(int n);
            static const Complex Iota;


            Rational Real() const;
            Rational Imaginary() const;
            Rational Modulus() const;
            Rational Argument(bool radians = true) const;
            Complex Conjugate() const;
            Complex Pow(Rational n) const;
            Complex Inverse() const;
            Complex Normalized() const;
            Complex Rotate(Rational angle,bool radians=true) const;
            std::string toString() const;

            void setReal(Rational real);
            void setImaginary(Rational imaginary);


            Complex operator+(const Complex &f) const;
            Complex operator-(const Complex &f) const;
            Complex operator*(const Complex &f) const;
            Complex operator/(const Complex &f) const;
            Complex operator-() const;
            bool operator==(const Complex& other) const;
            bool operator!=(const Complex& other) const;
            operator std::string() const;



        };
        Complex operator+(Rational r,const Complex& c);
        Complex operator-(Rational r,const Complex& c);
        Complex operator*(Rational r,const Complex& c);
        Complex operator/(Rational r,const Complex& c);
        std::ostream& operator<<(std::ostream& os, const Complex& f);






        namespace Functions {
            Core::Complex Pow(Core::Complex c , Rational n);
            Core::Complex Sqrt(Core::Complex c);
            Rational Modulus(Core::Complex c);
            Core::Complex Sin(Core::Complex c);
            Core::Complex Cos(Core::Complex c);
            Core::Complex Tan(Core::Complex c);
            Core::Complex Cosec(Core::Complex c);
            Core::Complex Sec(Core::Complex c);
            Core::Complex Cot(Core::Complex c);
            Core::Complex Loge(Core::Complex c);
            Core::Complex Log10(Core::Complex c);
            Core::Complex Log(Rational base , Core::Complex c);
            Core::Complex Exp(Core::Complex c);

        }
    }
}




#endif //COMPLEX_H
