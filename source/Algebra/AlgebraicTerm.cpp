//
// Created by Abhishek Singal on 19/08/25.
//

#include "Algebra/AlgebraicTerm.h"
#include <Core/Utils.h>

using namespace MathEngine::Core::Utils;

namespace MathEngine {
    namespace Algebra {
        bool AlgebraicTerm::CompareVariableMap(const AlgebraicTerm &other) const {
            const long double EPSILON = 1e-9;
            // Compare variables
            if (variables != other.variables) {
                return false;
            }

            // Compare exponents map with epsilon
            if (exponents.size() != other.exponents.size()) {
                return false;
            }

            for (const auto &[var, expA]: exponents) {
                auto it = other.exponents.find(var);
                if (it == other.exponents.end()) {
                    return false;
                }

                Rational expB = it->second;
                if (std::abs(expA - expB) > EPSILON) {
                    return false;
                }
            }

            return true;
        }

        AlgebraicTerm::AlgebraicTerm(Rational coefficient) {
            this->coefficient = coefficient;
        }

        AlgebraicTerm::AlgebraicTerm(std::string exp) {
            ParseExpression(exp);
            this->exp = GetString();
        }

        void AlgebraicTerm::ParseExpression(std::string exp) {
            int i = 0;
            std::string coeff_str = "";
            if (exp[i] == '+') {
                i += 1;
            }

            //Get Leading Coefficient
            while (!isalpha(exp[i]) && i < exp.length()) {
                coeff_str += exp[i];
                i++;
            }
            if (coeff_str != "" && coeff_str != "-") {
                coefficient = evaluator.evaluateArithmetic(coeff_str);
            } else if (coeff_str == "-") {
                coefficient = -1;
            } else {
                coefficient = 1;
            }


            //Get Variables and their Exponents
            while (i < exp.length()) {
                char var = exp[i];
                std::string var_str(1, var);

                if (exponents.count(var_str) == 0) {
                    variables.insert(var_str);
                }

                std::string exponent_str = "";

                if (i != exp.length() - 1 && exp[i + 1] == '^') {
                    i += 2; // move past '^'
                    // While still in bounds and not a letter (part of number)
                    while (i < exp.length() && !isalpha(exp[i])) {
                        exponent_str += exp[i];
                        i++;
                    }

                    // Evaluate only if we got a valid string
                    if (!exponent_str.empty()) {
                        Rational exponent = evaluator.evaluateArithmetic(exponent_str);
                        exponents[var_str] += exponent;
                    } else {
                        exponents[var_str] += 1; // default if no number after '^'
                    }

                    i--; // step back so next loop handles the right character
                } else {
                    exponents[var_str] += 1;
                }

                i++;
            }
        }

        std::string AlgebraicTerm::GetString() const {
            std::string exp = "";
            std::string literal = GetLiteral();

            if (literal == "") {
                return Utils::GetRationalString(coefficient);
            }

            if (coefficient != 1 and coefficient != -1) { exp += Utils::GetRationalString(coefficient); } else if (
                coefficient == -1) {
                exp += "-";
                }


            exp += literal;

            return exp;
        }

        Rational AlgebraicTerm::GetCoefficient() const {
            return coefficient;
        }

        std::string AlgebraicTerm::GetLiteral() const {
            std::string exp = "";
            for (const auto &[var,exponent]: exponents) {
                if (exponent != 0) {
                    exp += var;
                }

                if (exponent != 1 && exponent != 0) {
                    exp += "^";
                    exp += Utils::GetRationalString(exponent);
                }
            }

            return exp;
        }

        Rational AlgebraicTerm::GetDegree() const {
            Rational degree = 0;
            for (std::string var: variables) {
                degree += exponents.at(var);
            }

            return degree;
        }

        AlgebraicTerm AlgebraicTerm::Evaluate(std::map<std::string, Rational> variables) const {
            AlgebraicTerm term = *this;
            for (const auto &[var,val]: variables) {
                if (exponents.count(var) != 0) {
                    term.exponents.erase(var);
                    term.coefficient *= val * exponents.at(var);
                    term.variables.erase(var);
                }
            }
            return term;
        }


        bool AlgebraicTerm::AreLikeTerms(AlgebraicTerm term1, AlgebraicTerm term2) {
            return term1.CompareVariableMap(term2);
        }

        AlgebraicTerm AlgebraicTerm::operator*(const AlgebraicTerm &other) const {
            AlgebraicTerm result;

            result.coefficient = coefficient * other.coefficient;

            for (const std::string &var: variables) {
                result.variables.insert(var);
                result.exponents[var] = exponents.at(var);
            }

            for (const std::string &var: other.variables) {
                result.variables.insert(var);
                result.exponents[var] += other.exponents.at(var);
            }

            return result;
        }

        AlgebraicTerm AlgebraicTerm::operator/(const AlgebraicTerm &other) const {
            AlgebraicTerm inv = other;
            for (std::string var: inv.variables) {
                inv.exponents[var] = -inv.exponents.at(var);
            }

            AlgebraicTerm result = (*this) * inv;
            result.coefficient = coefficient / other.coefficient;

            return result;
        }

        bool AlgebraicTerm::operator==(const AlgebraicTerm &other) const {
            const long double EPSILON = 1e-9;

            // Compare coefficients with epsilon tolerance
            if (std::abs(coefficient - other.coefficient) > EPSILON) {
                return false;
            }

            return CompareVariableMap(other);
        }

        bool AlgebraicTerm::operator!=(const AlgebraicTerm &other) const {
            return !((*this) == other);
        }


        AlgebraicTerm operator*(Rational coefficient, const AlgebraicTerm &other) {
            return other * AlgebraicTerm(coefficient);
        }

        AlgebraicTerm operator/(Rational coefficient, const AlgebraicTerm &other) {
            return AlgebraicTerm(coefficient) / other;
        }

        std::ostream &operator<<(std::ostream &os, const AlgebraicTerm &algb) {
            os << algb.GetString();
            return os;
        }
    }
}
