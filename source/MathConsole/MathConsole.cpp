//
// Created by Abhishek Singal on 09/07/25.
//


#include <MathEngine.h>

#include <Core/ExpressionEvaluater.h>
#include "../../include/Core/Utils.h"

int main(int argc , char *argv[]) {
    MathEngine::Core::ExpressionEvaluater evaluator;
    std::string expression = "";

    std::string doc = R"(
MathEngine Console (v1.0.0)
C++20 Expression Evaluator

Console tool for evaluating complex mathematical expressions with support
for rational arithmetic, constants, and advanced mathematical functions.

────────────────────────────────────────────────────────────

Supported Syntax:
-----------------
Operators :      +  -  *  /  ^    (with proper precedence)
Parentheses (,) :    Fully supported, including nested expressions
Constants :      PI, e
Functions :
  - Trigonometric:      sin, cos, tan, cot, sec, cosec
  - Inverse trig :      arcsin, arccos, arctan
  - Logarithmic :       log<base>(x), ln(x)
  - Others : sqrt, mod

Notes:
------
>> Constants and functions are resolved before arithmetic.
>> Nested and composite expressions are supported.

Enter an expression and press [Enter] to evaluate.
)";

    std::cout << doc << std::endl;

    while (expression != "exit") {
        std::cout << ">> : ";
        std::getline(std::cin, expression);
        MathEngine::Core::Rational result = evaluator.evaluateExpression(expression);
        MathEngine::Core::Utils::Fraction frac(result);
        std::cout << MathEngine::Core::Utils::GetRationalString(result,1e9) <<"   [ " << frac.ToString() <<  " ]\n" <<
                std::endl;
    }
}
