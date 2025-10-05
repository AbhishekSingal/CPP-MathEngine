//
// Created by Abhishek Singal on 09/07/25.
//

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include "MathEngine.h"
#include <Core/Functions.h>

using namespace MathEngine::Core;

namespace MathEngine {
    namespace Core{
    namespace Utils {
        //Conversion Methods
        std::string GetIntegralString(Integer n);
        std::string GetRationalString(Rational r,Rational acc = 1e10L);
        Rational StrToRational(std::string r);

        //Numerical Methods
        Rational Round(Rational r,int decimal_places);
        Rational HCF(Integer a, Integer b);
        Rational LCM(Integer a, Integer b);
        Rational ToRadians(Rational r);
        Rational ToDegrees(Rational r);
        Rational NormalizeAngle(Rational r);
        bool IsPrime(Natural n);
        bool IsEven(Natural n);
        bool IsOdd(Natural n);
        bool IsPerfectSquare(Natural n);
        std::vector<Integer> PrimeNumbers(Natural from, Natural to);
        std::vector<Integer> Divisors(Natural n);
        std::vector<std::pair<Integer, Integer> > PrimeFactors(Natural n);

        //Utilary Classes
        class Fraction {
        private:
            Integer numerator, denominator;
            Rational value;
            void reduce();
            void updateValue();

        public:
            Fraction(){;};
            Fraction(std::string s);
            Fraction(Integer n, Integer d);
            Fraction(Rational r);

            Integer Numerator() const;
            Integer Denominator() const;
            Rational Value() const;
            std::string ToString() const;

            void setNumerator(Integer n);
            void setDenominator(Integer d);
            void setValue(Rational r);
            void Reciprocal();

            //Overload Operators
            Fraction operator+(const Fraction& rhs) const;
            Fraction operator-(const Fraction& rhs) const;
            Fraction operator*(const Fraction& rhs) const;
            Fraction operator/(const Fraction& rhs) const;

            bool operator==(const Fraction& rhs) const;
            bool operator!=(const Fraction& rhs) const;
            bool operator<(const Fraction& rhs) const;
            bool operator>(const Fraction& rhs) const;
            bool operator<=(const Fraction& rhs) const;
            bool operator>=(const Fraction& rhs) const;

            operator Integer() const;
            operator Rational() const;
            operator std::string() const;

        };

        Fraction operator+(Rational r,const Fraction& rhs);
        Fraction operator-(Rational r,const Fraction& rhs);
        Fraction operator*(Rational r,const Fraction& rhs);
        Fraction operator/(Rational r,const Fraction& rhs);
        std::ostream& operator<<(std::ostream& os, const Fraction& f);
        std::istream& operator>>(std::istream& is, Fraction& f);
    }
    }
}


#endif //UTILS_H
