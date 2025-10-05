//
// Created by Abhishek Singal on 09/07/25.
//
#include <Core/Utils.h>

namespace MathEngine {
    namespace Core {

        namespace Utils {
            std::string GetIntegralString(Integer n) {
                if (n == 0) return "0";

                bool isNegative = (n < 0);
                if (isNegative) n = -n;

                std::string digits;
                while (n > 0) {
                    digits.push_back('0' + (n % 10));
                    n /= 10;
                }

                if (isNegative) {
                    digits.push_back('-');
                }

                // Now reverse the whole string once
                std::reverse(digits.begin(), digits.end());
                return digits;
            }

            std::string GetRationalString(Rational value,Rational acc) {
                // Round to 10 decimal places
                long double rounded = std::round(value * acc) / acc;

                // Format with fixed-point notation, 10 decimal places
                char buffer[64];
                std::snprintf(buffer, sizeof(buffer), "%.10Lf", rounded);

                // Trim trailing zeros and decimal point
                char* end = buffer + std::strlen(buffer) - 1;
                while (*end == '0') --end;
                if (*end == '.') --end;
                *(end + 1) = '\0';

                return std::string(buffer);
            }

            Rational StrToRational(std::string r) {
                return std::stold(r);
            }

            Rational Round(Rational r,int decimal_places) {
                Rational scale = std::pow(10.0L, decimal_places);
                return std::round(r * scale) / scale;
            }

            Rational HCF(Integer a, Integer b) {
                a = std::abs(a);
                b = std::abs(b);
                while (b != 0) {
                    int temp = b;
                    b = a % b;
                    a = temp;
                }
                return Rational(a);
            }

            Rational LCM(Integer a, Integer b) {
                if (a == 0 || b == 0) return Rational(0);

                Rational gcd = HCF(a, b);
                Rational product = Rational(std::abs(a)) * Rational(std::abs(b));
                return product / gcd;
            }

            Rational ToRadians(Rational r) {
                return r * (Constants::Pi/180.00);
            }

            Rational ToDegrees(Rational r) {
                return r * (180.0/Constants::Pi);
            }

            Rational NormalizeAngle(Rational r) {
                long double normalized = fmod(r, 360.0L);

                if (normalized < 0)
                    normalized += 360.0L;

                return Rational(normalized);
            }

            bool IsPrime(Natural n) {
                if (n <= 1) return false;
                if (n <= 3) return true;
                if (n % 2 == 0 || n % 3 == 0) return false;

                for (Natural i = 5; i * i <= n; i += 6) {
                    if (n % i == 0 || n % (i + 2) == 0)
                        return false;
                }

                return true;
            }

            bool IsEven(Natural n) {
                return n % 2 == 0;
            }

            bool IsOdd(Natural n) {
                return n % 2 == 1;
            }

            bool IsPerfectSquare(Natural n) {
                Rational r =  Core::Functions::Sqrt(n);
                return Core::Functions::Modulus(r-Integer(r)) == 0;
            }

            std::vector<Integer> PrimeNumbers(Natural from, Natural to) {
                std::vector<Integer> primes;

                if (to < 2 || from > to) return primes;
                if (from < 2) from = 2;

                for (Natural i = from; i <= to; ++i) {
                    if (IsPrime(i)) {
                        primes.push_back(i);
                    }
                }

                return primes;
            }

            std::vector<Integer> Divisors(Natural n) {
                std::vector<Integer> divisors;

                if (n == 0)
                    return divisors; // or throw error if you want to handle Divisors(0) as undefined

                Integer root = static_cast<Integer>(std::sqrt(n));

                for (Integer i = 1; i <= root; ++i) {
                    if (n % i == 0) {
                        divisors.push_back(i);
                        if (i != n / i) {
                            divisors.push_back(n / i);
                        }
                    }
                }

                std::sort(divisors.begin(), divisors.end());
                return divisors;
            }

            std::vector<std::pair<Integer, Integer>> PrimeFactors(Natural n) {
                std::vector<std::pair<Integer, Integer>> factors;

                if (n < 2)
                    return factors;  // 0 and 1 have no prime factorization

                for (Integer p = 2; p * p <= n; ++p) {
                    if (n % p == 0) {
                        Integer count = 0;
                        while (n % p == 0) {
                            ++count;
                            n /= p;
                        }
                        factors.push_back({p, count});
                    }
                }

                if (n > 1) {
                    // what's left is a prime > sqrt(original n)
                    factors.push_back({n, 1});
                }

                return factors;
            }


            void Fraction::reduce() {
                Integer gcd = HCF(std::abs(numerator), std::abs(denominator));
                numerator /= gcd;
                denominator /= gcd;
            }

            // Helper to keep value updated
            void Fraction::updateValue() {
                if (denominator == 0) {
                    throw std::runtime_error("Denominator cannot be zero");
                }
                reduce();
                value = Rational(numerator) / Rational(denominator);
            }

            Fraction::Fraction(std::string s) {
                if (s.find("/") == std::string::npos) {
                    const Integer precision = 1000000;
                    numerator = static_cast<Integer>(std::stold(s) * precision);
                    denominator = precision;
                    updateValue();
                    return;
                }
                std::string n = "" , d = "";
                std::string curr = "";
                for (int i = 0 ; i < s.length() ; ++i) {
                    char c = s[i];
                    if (c != '/' && c != ' ') {
                        curr += c;
                    }else {
                        n = curr;
                        curr = "";
                    }
                }

                d = curr;
                numerator = std::stold(n);
                denominator = std::stold(d);
                updateValue();

            }

            // Constructor: Integer numerator and denominator
            Fraction::Fraction(Integer n, Integer d) : numerator(n), denominator(d) {
                updateValue();
            }

            // Constructor: from Rational — approximate as fraction
            Fraction::Fraction(Rational r) : value(r) {
                const Integer precision = 1000000;
                numerator = static_cast<Integer>(r * precision);
                denominator = precision;
                updateValue();
            }

            // Getters
            Integer Fraction::Numerator() const  {
                return numerator;
            }

            Integer Fraction::Denominator() const {
                return denominator;
            }

            Rational Fraction::Value() const{
                return value;
            }

            std::string Fraction::ToString() const {
                return std::string(*this);
            }

            // Setters
            void Fraction::setNumerator(Integer n) {
                numerator = n;
                updateValue();
            }

            void Fraction::setDenominator(Integer d) {
                if (d == 0) {
                    throw std::runtime_error("Denominator cannot be zero");
                }
                denominator = d;
                updateValue();
            }

            void Fraction::setValue(Rational r) {
                value = r;
                const Integer precision = 1000000;
                numerator = static_cast<Integer>(r * precision);
                denominator = precision;
                updateValue(); // Recalculate using new values
            }

            void Fraction::Reciprocal() {
                Integer temp = denominator;
                denominator = numerator;
                numerator = temp;
                updateValue();
            }

            Fraction Fraction::operator+(const Fraction &rhs) const {
                Fraction result((numerator*rhs.denominator + rhs.numerator*denominator) , (denominator*rhs.denominator));
                return result;
            }

            Fraction Fraction::operator-(const Fraction &rhs) const {
                Fraction result((numerator*rhs.denominator - rhs.numerator*denominator) , (denominator*rhs.denominator));
                return result;
            }

            Fraction Fraction::operator*(const Fraction &rhs) const {
                Fraction result((numerator * rhs.numerator),(denominator * rhs.denominator));
                return result;
            }

            Fraction Fraction::operator/(const Fraction &rhs) const {
                Fraction result ((numerator * rhs.denominator) , (denominator * rhs.numerator));
                return result;
            }

            bool Fraction::operator==(const Fraction &rhs) const {
                return value == rhs.value;
            }

            bool Fraction::operator!=(const Fraction &rhs) const {
                return value != rhs.value;
            }

            bool Fraction::operator<(const Fraction &rhs) const {
                return value < rhs.value;
            }

            bool Fraction::operator>(const Fraction &rhs) const {
                return value > rhs.value;
            }

            bool Fraction::operator<=(const Fraction &rhs) const {
                return value <= rhs.value;
            }

            bool Fraction::operator>=(const Fraction &rhs) const {
                return value >= rhs.value;
            }

            Fraction::operator signed long long() const {
                return static_cast<signed long long>(value) ;
            }

            Fraction::operator long double() const {
                return value;
            }

            Fraction::operator std::string() const {
                return GetRationalString(numerator) + "/" + GetRationalString(denominator);
            }


            Fraction operator+(Rational r,const Fraction& rhs) {return Fraction(r) + rhs;};
            Fraction operator-(Rational r,const Fraction& rhs) {return Fraction(r) - rhs;};
            Fraction operator*(Rational r,const Fraction& rhs) {return Fraction(r) * rhs;};
            Fraction operator/(Rational r,const Fraction& rhs) {return Fraction(r) / rhs;};

            std::ostream& operator<<(std::ostream& os, const MathEngine::Core::Utils::Fraction& f) {
                if (f.Denominator() == 1)
                    os << f.Numerator();
                else
                    os << f.Numerator() << "/" << f.Denominator();
                return os;
            }

            std::istream & operator>>(std::istream &is, Fraction &f) {
                std::string s;
                is >> s;
                f = Fraction(s);
                return is;
            }
        }
    }
}