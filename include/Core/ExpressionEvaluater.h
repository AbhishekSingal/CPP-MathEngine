//
// Created by Abhishek Singal on 09/07/25.
//

#ifndef EXPRESSIONEVALUATER_H
#define EXPRESSIONEVALUATER_H

//STL Includes
#include <iostream>
#include <stack>
#include <vector>

//Project Includes
#include "MathEngine.h"
#include <Core/Functions.h>


namespace MathEngine
{
    namespace Core {
        /**
         *
         * @param op1 Operator 1
         * @param op2 Operator 2
         * @return Returns Bool , whether op1 has higher precedence than op2
         */
        bool compareOperators(char op1 , char op2);

        class ExpressionEvaluater
        {
        private:
            //Core Variables
            std::string expression;
            std::vector<std::string> infixArr;
            std::vector<std::string> postfixArr;
            Rational value;

            //Core Methods
            void evaluatePostfixArray();
            void createInfixArray();
            void createPostFixArray();

            //Utils
            bool isOperator(char c);

        public:
            //Constructors
            ExpressionEvaluater(){;};

            //High Level Methods

            /**
             *
             * @param expression Arithematic Expression
             * @details Only Digits , Decimals , Operators (^,/,*,+,-) and Parenthesis (,) are allowed in the Expression
             * @warning Passing Invalid Characters or Invlaid Expressions will throw exception or cause undefined behaviour
             * @return Rational - Value of the Expression
             */
            Rational evaluateArithmetic(std::string expression);


            /**
             * @param expression Mathematical Expression
             * @details Only Digits , Decimals , Operators (^,/,*,+,-) , Parenthesis (,) , Standard Math Functions and Standard Constants are allowed in the Expression
             * @details Supported Functions : arcsin,arccos,arctan,cosec,sec,sin,cos,tan,cot,ln,log<base>
             * @details Supported Constants : PI , e
             * @warning Passing Invalid Characters or Invlaid Expressions will throw exception or cause undefined behaviour
             * @return Rational - Value of the Expression
             */
            Rational evaluateExpression(std::string expression);

        };
    }
}


#endif //EXPRESSIONEVALUATER_H
