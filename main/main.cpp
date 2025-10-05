//
// Created by Abhishek Singal on 09/07/25.
//

#include <iostream>
#include <regex>

#include <MathEngine.h>
#include <ranges>
#include <Core/ExpressionEvaluater.h>
#include <Core/Function.h>
#include <Core/Functions.h>
#include <Core/Complex.h>
#include <Core/Utils.h>

#include "Algebra/AlgebraicTerm.h"
#include "Algebra/BasicAlgebraicExpression.h"
#include "Algebra/Cubic.h"
#include "Algebra/Quadratic.h"

using MathEngine::Core::ExpressionEvaluater;
using MathEngine::Core::Function;
using MathEngine::Core::Complex;
using MathEngine::Algebra::Quadratic;
using MathEngine::Algebra::Cubic;
using MathEngine::Algebra::BasicAlgebraicExpression;
using MathEngine::Algebra::AlgebraicTerm;

typedef BasicAlgebraicExpression ALGBEXP;


int main(int argc, const char * argv[]) {

    std::cout << "C++(20) Computer Algebra System\n" << std::endl;
    std::string exp = "";
    while (exp != "exit") {
        std::cout << ">> : ";
        std::getline(std::cin, exp);
        exp = BasicAlgebraicExpression::division_preprocessor(exp);
        // exp = BasicAlgebraicExpression::Preprocess(exp);
        BasicAlgebraicExpression algbexp(exp);
        // std::cout << exp << std::endl;
        std::cout << algbexp << '\n' << std::endl;
    }
    return 0;
}