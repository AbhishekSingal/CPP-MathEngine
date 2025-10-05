//
// Created by Abhishek Singal on 14/07/25.
//

#ifndef ALGEBRAICEXPRESSION_H
#define ALGEBRAICEXPRESSION_H

//STL Includes
#include <set>
#include <string>
#include <map>
#include <regex>

//Project Includes
#include <MathEngine.h>
#include <Core/ExpressionEvaluater.h>



namespace MathEngine {
    namespace Algebra {
        class BasicAlgebraicExpression {
            private:
            std::string exp;
            std::set<std::string> literals;
            std::map<std::string,MathEngine::Core::Rational> terms_map;

            BasicAlgebraicExpression(){;};
            void ParseExpression(std::string exp);

        public:
            BasicAlgebraicExpression(std::string exp);
            std::string GetString() const;
            BasicAlgebraicExpression Pow(int n);
            BasicAlgebraicExpression Evaluate(std::map<std::string,MathEngine::Core::Rational> values) const;
            bool IsArithematicalExpression() const;

            static std::string division_preprocessor(std::string exp);
            static std::string Preprocess(const std::string &exp);

            BasicAlgebraicExpression operator+(const BasicAlgebraicExpression& other) const;
            BasicAlgebraicExpression operator-(const BasicAlgebraicExpression& other) const;
            BasicAlgebraicExpression operator*(const MathEngine::Core::Rational r) const;
            BasicAlgebraicExpression operator*(const BasicAlgebraicExpression& other) const;

        };

        std::ostream& operator<<(std::ostream& os, const BasicAlgebraicExpression& algb);


    }
}


#endif //ALGEBRAICEXPRESSION_H
