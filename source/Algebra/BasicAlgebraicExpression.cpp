//
// Created by Abhishek Singal on 14/07/25.
//

#include "Algebra/BasicAlgebraicExpression.h"
#include <Algebra/AlgebraicTerm.h>
#include <Core/Utils.h>


namespace MathEngine {
    namespace Algebra {

        BasicAlgebraicExpression::BasicAlgebraicExpression(std::string exp) {
            ParseExpression(exp);
            this->exp = GetString();
        }

        void BasicAlgebraicExpression::ParseExpression(std::string exp) {
            std::vector<std::string> parnethesis_terms;
            std::string p_term = "";
            int bracket_counter = 0;

            for (int i = 0; i < exp.length(); i++) {
                char c = exp[i];
                if (c == '*' || c == '+' || c == '-') {
                    if (p_term.back() == '^') {
                        p_term += c;
                        continue;
                    }

                    if (bracket_counter == 0) {
                        if (p_term != "") { parnethesis_terms.push_back(p_term); }
                        parnethesis_terms.push_back(std::string(1, c));
                        p_term = "";
                    } else {
                        p_term += c;
                    }
                } else {
                    if (c == '(') {
                        bracket_counter++;
                        p_term += c;
                    } else if (c == ')') {
                        bracket_counter--;
                        p_term += c;
                        if (bracket_counter == 0) {
                            parnethesis_terms.push_back(p_term);
                            p_term = "";
                        }
                    } else if (c != ' ') {
                        p_term += c;
                    }
                }
                if (i == exp.length() - 1) {
                    if (p_term != "") { parnethesis_terms.push_back(p_term); }
                }
            }

            std::vector<std::string> temp_p_array;
            for (int i = 0; i < parnethesis_terms.size(); i++) {
                std::string term = parnethesis_terms.at(i);
                if (term[0] != '^') {
                    temp_p_array.push_back(term);
                }else {
                    BasicAlgebraicExpression algbexp = parnethesis_terms.at(i-1);
                    std::string exponent = term.substr(1);
                    if (exponent == ""){exponent += (parnethesis_terms.at(i + 1)+parnethesis_terms.at(i+2));i+=2;};
                    Rational expo = std::stod(exponent);
                    algbexp = algbexp.Pow(expo);
                    temp_p_array.back() = "("+algbexp.GetString()+")";
                }
            }

            parnethesis_terms = temp_p_array;
            temp_p_array.clear();

//std::regex pattern("^\\^-\\d+\\)$")
            std::string prev = "";
            for (int i = 0; i < parnethesis_terms.size(); i++) {
                std::string term = parnethesis_terms.at(i);
                if (term != "*") {
                    temp_p_array.push_back(term);
                    prev = "";
                } else {
                    prev = (prev == "" ? parnethesis_terms.at(i - 1) : prev);
                    std::string next = parnethesis_terms.at(i + 1);
                    std::string sub_res = (BasicAlgebraicExpression(prev) * BasicAlgebraicExpression(next)).GetString();
                    prev = sub_res;
                    temp_p_array.back() = sub_res;
                    i += 1;
                }
            }

            parnethesis_terms = temp_p_array;

            std::string temp_exp = "";
            std::string m_term = "";
            for (int i = 0; i < parnethesis_terms.size(); i++) {
                std::string s = parnethesis_terms.at(i);
                char start = s[0];
                if (start != '(') {
                    temp_exp += s;
                } else {
                    std::string a1 = s.substr(1, s.length() - 2);
                    std::string op = (i != parnethesis_terms.size() - 1) ? parnethesis_terms.at(i + 1) : "";
                    std::string prev_op = (i != 0) ? parnethesis_terms.at(i - 1) : "";
                    if (op == "+" || op == "-" || op == "") {
                        BasicAlgebraicExpression sub_res = BasicAlgebraicExpression(a1);
                        if (prev_op != "-") {
                            temp_exp += sub_res.GetString();
                        } else {
                            temp_exp.pop_back();
                            sub_res = sub_res * -1;
                            std::string m_s = sub_res.GetString();
                            temp_exp += ((m_s[0] == '+' || m_s[0] == '-') ? "" : "+") + m_s;
                        }
                        temp_exp += op;
                        i += 1;
                    } else if (op == "*") {
                        int k = 0;
                        std::string next_op = parnethesis_terms.at(i + 1 + k);;
                        BasicAlgebraicExpression sub_res = BasicAlgebraicExpression(a1);
                        while (next_op == "*") {
                            std::string a2 = parnethesis_terms.at(i + 2 + k);
                            if (a2[0] == '(') {
                                a2 = a2.substr(1, a2.length() - 2);
                            }
                            sub_res = sub_res * BasicAlgebraicExpression(a2);
                            k += 2;
                            if (i + k + 2 < parnethesis_terms.size()) {
                                next_op = parnethesis_terms.at(i + k + 1);
                            } else { next_op = ""; }
                        }
                        if (prev_op != "-") {
                            temp_exp += BasicAlgebraicExpression(sub_res).GetString();
                        } else {
                            temp_exp.pop_back();
                            sub_res = sub_res * -1;
                            std::string m_s = sub_res.GetString();
                            temp_exp += ((m_s[0] == '+' || m_s[0] == '-') ? "" : "+") + m_s;
                        }
                        i += k;
                    } else if (op == "^") {
                        std::string exponent = parnethesis_terms.at(i + 2);
                        if (exponent == "-") {
                            exponent += parnethesis_terms.at(i + 3);
                            i += 1;
                        } else if (exponent == "+") {
                            exponent = parnethesis_terms.at(i + 3);
                            i += 1;
                        }
                        BasicAlgebraicExpression sub_res = BasicAlgebraicExpression(a1).Pow(std::stold(exponent));
                        if (prev_op != "-") {
                            temp_exp += BasicAlgebraicExpression(sub_res).GetString();
                        } else {
                            temp_exp.pop_back();
                            sub_res = sub_res * -1;
                            std::string m_s = sub_res.GetString();
                            temp_exp += ((m_s[0] == '+' || m_s[0] == '-') ? "" : "+") + m_s;
                        }
                        i += 2;
                    }
                }
            }

            exp = temp_exp;

            //Parse Individual Terms
            std::vector<std::string> terms_array;
            std::string term = "";
            for (int i = 0; i < exp.length(); i++) {
                char c = exp[i];
                if (c != ' ') {
                    if (c != '+' && c != '-') {
                        term += c;
                    } else {
                        char prev = i != 0 ? exp[i - 1] : '_';
                        if (prev != '^' && prev != '/' && prev != '*' && prev != '+' && prev != '-' && prev != '_') {
                            if (term != "") {
                                terms_array.push_back(term);
                                term = "";
                                term += c;
                            }
                        } else {
                            if (term.back() != '+' && term.back() != '-') {
                                term += c;
                            } else {
                                char s = term.back();
                                term.back() = (s == '+' ? 1 : -1) * (c == '+' ? 1 : -1) > 0 ? '+' : '-';
                            }
                        }
                    }
                }
                if (i == exp.length() - 1) {
                    terms_array.push_back(term);
                }
            }

            for (int i = 0; i < terms_array.size(); i++) {
                std::string term_str = terms_array[i];
                if (term_str.find("*") == std::string::npos && term_str.find("/") == std::string::npos) {
                    AlgebraicTerm Algbterm = AlgebraicTerm(term_str);
                    std::string literal = Algbterm.GetLiteral();
                    if (literal != "") {
                        literals.insert(literal);
                        terms_map[literal] += Algbterm.GetCoefficient();
                    } else {
                        literals.insert("constant");
                        terms_map["constant"] += Algbterm.GetCoefficient();
                    }
                } else {
                    std::vector<AlgebraicTerm> sub_terms;
                    std::vector<char> operators;
                    std::string sub_term = "";
                    for (int j = 0; j < term_str.length(); j++) {
                        char c = term_str[j];
                        if (c != '*' && c != '/') {
                            sub_term += c;
                        } else {
                            sub_terms.push_back(AlgebraicTerm(sub_term));
                            sub_term = "";
                            operators.push_back(c);
                        }
                        if (j == term_str.length() - 1) {
                            sub_terms.push_back(AlgebraicTerm(sub_term));
                        }
                    }
                    AlgebraicTerm tterm = sub_terms[0];
                    for (int i = 0; i < operators.size(); i++) {
                        if (operators[i] == '*') {
                            tterm = tterm * sub_terms[i + 1];
                        } else if (operators[i] == '/') {
                            tterm = tterm / sub_terms[i + 1];
                        }
                    }

                    AlgebraicTerm Algbterm = AlgebraicTerm(tterm);
                    std::string literal = Algbterm.GetLiteral();
                    if (literal != "") {
                        literals.insert(literal);
                        terms_map[literal] += Algbterm.GetCoefficient();
                    } else {
                        literals.insert("constant");
                        terms_map["constant"] += Algbterm.GetCoefficient();
                    }
                }
            }
        }

        std::string BasicAlgebraicExpression::GetString() const {
            std::vector<std::pair<std::string, AlgebraicTerm> > terms;

            // Collect non-constant terms
            for (const auto &[literal, coeff]: terms_map) {
                if (literal == "constant") continue;
                AlgebraicTerm term(literal);
                terms.emplace_back(literal, term);
            }

            // Build variable order: "a" to "z"
            std::vector<std::string> var_order;
            for (char ch = 'a'; ch <= 'z'; ++ch) {
                var_order.emplace_back(1, ch); // create string from char
            }

            // Sort terms using custom comparator
            std::sort(terms.begin(), terms.end(),
                      [&var_order](const auto &a, const auto &b) {
                          const AlgebraicTerm &termA = a.second;
                          const AlgebraicTerm &termB = b.second;

                          Rational degA = termA.GetDegree();
                          Rational degB = termB.GetDegree();
                          if (degA != degB) return degA > degB;

                          // 🆕 Sort by number of variables (fewer comes first)
                          size_t varsA = termA.exponents.size();
                          size_t varsB = termB.exponents.size();
                          if (varsA != varsB) return varsA < varsB;

                          // Then by literal length
                          if (a.first.length() != b.first.length())
                              return a.first.length() < b.first.length();

                          // Then by variable order
                          for (const std::string &var: var_order) {
                              Rational expA = termA.exponents.count(var) ? termA.exponents.at(var) : 0;
                              Rational expB = termB.exponents.count(var) ? termB.exponents.at(var) : 0;
                              if (expA != expB) return expA > expB;
                          }

                          return a.first < b.first;
                      });


            std::string exp = "";

            // Format sorted terms
            for (const auto &[literal, term]: terms) {
                Rational coeff = terms_map.at(literal);
                if (coeff == 0) continue;

                std::string sign = coeff > 0 ? " + " : " - ";
                if (!exp.empty()) {
                    exp += sign;
                } else if (coeff < 0) {
                    exp += "-";
                }

                Rational abs_coeff = Functions::Modulus(coeff);
                if (abs_coeff != 1) {
                    exp += Utils::GetRationalString(abs_coeff);
                } else if (literal.empty()) {
                    exp += Utils::GetRationalString(abs_coeff); // For standalone coefficient
                }

                exp += literal;
            }

            // Handle constant term
            auto it = terms_map.find("constant");
            if (it != terms_map.end()) {
                Rational constant_ = it->second;
                if (constant_ != 0) {
                    std::string sign = constant_ > 0 ? " + " : " - ";
                    if (!exp.empty()) {
                        exp += sign;
                    } else if (constant_ < 0) {
                        exp += "-";
                    }
                    exp += Utils::GetRationalString(Functions::Modulus(constant_));
                }
            }

            return exp.empty() ? "0" : exp;
        }


        BasicAlgebraicExpression BasicAlgebraicExpression::Pow(int n) {
            BasicAlgebraicExpression algbexp = *this;
            if (IsArithematicalExpression()) {
                Rational base = std::stold(GetString());
                Rational val = std::pow(base, n);
                return BasicAlgebraicExpression(Utils::GetRationalString(val));
            }

            for (int i = 1; i < n; i++) {
                algbexp = algbexp * (*this);
            }

            return algbexp;
        }

        BasicAlgebraicExpression BasicAlgebraicExpression::Evaluate(std::map<std::string, Rational> values) const {
            BasicAlgebraicExpression algbexp = *this;
            auto terms_copy = algbexp.terms_map;
            algbexp.terms_map.clear();
            algbexp.literals.clear();
            for (const auto &[literal, coeff]: terms_copy) {
                if (literal != "constant") {
                    AlgebraicTerm term = AlgebraicTerm(literal) * AlgebraicTerm(coeff);
                    term = term.Evaluate(values);

                    if (term.GetLiteral() != "") {
                        algbexp.terms_map[term.GetLiteral()] += term.GetCoefficient();
                        algbexp.literals.insert(term.GetLiteral());
                    } else {
                        algbexp.terms_map["constant"] += term.GetCoefficient();
                    }
                } else {
                    algbexp.terms_map["constant"] += coeff;
                }
            }
            return algbexp;
        }

        bool BasicAlgebraicExpression::IsArithematicalExpression() const {
            std::string exp_str = GetString();
            static const std::regex number_regex(R"(^[+-]?(\d+(\.\d*)?|\.\d+)$)");
            return std::regex_match(exp_str, number_regex);
        }

        std::string BasicAlgebraicExpression::division_preprocessor(std::string expr) {
            std::string result;
            size_t i = 0;
            while (i < expr.length()) {
                if (expr[i] == '/') {
                    result += "*(";  // replace '/' with '*('
                    ++i; // move past '/'

                    // Handle potential nested parentheses or variable/number
                    if (expr[i] == '(') {
                        int open = 1;
                        size_t start = i + 1;
                        ++i;
                        while (i < expr.length() && open > 0) {
                            if (expr[i] == '(') ++open;
                            else if (expr[i] == ')') --open;
                            ++i;
                        }
                        std::string subexpr = expr.substr(start - 1, i - start + 1); // includes outer parentheses
                        result += subexpr + "^-1)";
                    } else {
                        // parse a variable or number
                        size_t start = i;
                        while (i < expr.length() &&
                               (isalnum(expr[i]) || expr[i] == '^')) {
                            ++i;
                               }
                        std::string token = expr.substr(start, i - start);
                        result += token + "^-1)";
                    }
                } else {
                    result += expr[i];
                    ++i;
                }
            }
            return result;
        }


        BasicAlgebraicExpression BasicAlgebraicExpression::operator+(const BasicAlgebraicExpression &other) const {
            BasicAlgebraicExpression result;
            for (std::string literal: literals) {
                result.literals.insert(literal);
                result.terms_map[literal] = terms_map.at(literal);
            }

            for (std::string literal: other.literals) {
                result.literals.insert(literal);
                result.terms_map[literal] += other.terms_map.at(literal);
            }

            return result;
        }

        BasicAlgebraicExpression BasicAlgebraicExpression::operator-(const BasicAlgebraicExpression &other) const {
            BasicAlgebraicExpression result;
            for (std::string literal: literals) {
                result.literals.insert(literal);
                result.terms_map[literal] = terms_map.at(literal);
            }

            for (std::string literal: other.literals) {
                result.literals.insert(literal);
                result.terms_map[literal] -= other.terms_map.at(literal);
            }

            return result;
        }

        BasicAlgebraicExpression BasicAlgebraicExpression::operator*(const Rational r) const {
            BasicAlgebraicExpression result = *this;
            for (const auto &[literal, val]: result.terms_map) {
                result.terms_map[literal] = val * r;
            }

            return result;
        }

        BasicAlgebraicExpression BasicAlgebraicExpression::operator*(const BasicAlgebraicExpression &other) const {
            BasicAlgebraicExpression result;
            for (std::string literal1: literals) {
                for (std::string literal2: other.literals) {
                    AlgebraicTerm term1(literal1 != "constant" ? literal1 : "1");
                    AlgebraicTerm term2(literal2 != "constant" ? literal2 : "1");
                    Rational coeff1 = terms_map.at(literal1);
                    Rational coeff2 = other.terms_map.at(literal2);

                    AlgebraicTerm sub_result = term1 * term2;
                    std::string sub_result_literal = sub_result.GetLiteral();


                    if (sub_result_literal != "") {
                        result.literals.insert(sub_result_literal);
                        result.terms_map[sub_result_literal] += coeff1 * coeff2;
                    } else {
                        result.literals.insert("constant");
                        result.terms_map["constant"] += coeff1 * coeff2;
                    }
                }
            }

            return result;
        }


        std::ostream &operator<<(std::ostream &os, const BasicAlgebraicExpression &algb) {
            os << algb.GetString();
            return os;
        }
    }
}
