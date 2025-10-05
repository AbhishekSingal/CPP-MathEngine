//
// Created by Abhishek Singal on 19/08/25.
//

#ifndef ALGEBRAICTERM_H
#define ALGEBRAICTERM_H

//STL Includes
#include <set>
#include <string>
#include <map>

//Project Includes
#include <MathEngine.h>
#include <Core/ExpressionEvaluater.h>



namespace MathEngine {
    namespace Algebra {
        class AlgebraicTerm {
        private:
            std::string exp;
            MathEngine::Core::Rational coefficient;
            std::set<std::string> variables;
            std::map<std::string, MathEngine::Core::Rational> exponents;
            MathEngine::Core::ExpressionEvaluater evaluator;

            bool CompareVariableMap(const AlgebraicTerm &other) const;

            AlgebraicTerm(){;};


        public:
            AlgebraicTerm(MathEngine::Core::Rational coefficient);
            AlgebraicTerm(std::string exp);
            void ParseExpression(std::string exp);
            std::string GetString() const;
            MathEngine::Core::Rational GetCoefficient() const;
            std::string GetLiteral() const;
            MathEngine::Core::Rational GetDegree() const;
            AlgebraicTerm Evaluate(std::map<std::string, MathEngine::Core::Rational> variables) const;
            static bool AreLikeTerms(AlgebraicTerm term1, AlgebraicTerm term2);

            AlgebraicTerm operator*(const AlgebraicTerm& other) const;
            AlgebraicTerm operator/(const AlgebraicTerm& other) const;
            bool operator==(const AlgebraicTerm& other) const;
            bool operator!=(const AlgebraicTerm& other) const;

            friend class BasicAlgebraicExpression;
        };
        AlgebraicTerm operator*(MathEngine::Core::Rational coefficient, const AlgebraicTerm& other);
        AlgebraicTerm operator/(MathEngine::Core::Rational coefficient, const AlgebraicTerm& other);
        std::ostream& operator<<(std::ostream& os, const AlgebraicTerm& algb);
    }
}


#endif //ALGEBRAICTERM_H
