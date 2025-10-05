//
// Created by Abhishek Singal on 10/07/25.
//

#ifndef FUNCTION_H
#define FUNCTION_H

#include <Core/ExpressionEvaluater.h>

#include "Complex.h"


namespace MathEngine {
    namespace Core{
        class Function {
        private:
            std::string fx;
            std::vector<std::string> compiled_fx;
            ExpressionEvaluater evaluator;
        public:
            Function(std::string fx);
            Rational evaluateAt(Rational x);
            Rational LimitRH(Rational x);
            Rational LimitLH(Rational x);
            Rational Limit(Rational x);
            Rational DifferentiateAt(Rational x);
            Rational DefiniteIntegral(Rational lowerLimit , Rational upperLimit ,int n = 1000);
            Rational FindRoot(Rational a, Rational b, Rational tolerance = 1e-5);
        };

    }
}


#endif //FUNCTION_H
