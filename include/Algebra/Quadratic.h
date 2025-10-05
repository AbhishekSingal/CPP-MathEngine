//
// Created by Abhishek Singal on 15/07/25.
//

#ifndef QUADRATIC_H
#define QUADRATIC_H

#include <MathEngine.h>
#include <Core/Complex.h>


namespace MathEngine {
    namespace Algebra {
        class Quadratic {
        private:
            Core::Rational a, b, c;
        public:
            Quadratic(Core::Rational a, Core::Rational b, Core::Rational c);
            Quadratic(Core::Rational sum, Core::Rational product);
            Core::Rational Discriminant();
            std::pair<Core::Rational,Core::Rational> GetRealRoots();
            std::pair<Core::Complex,Core::Complex> GetComplexRoots();
            Core::Rational EvaluateAt(Core::Rational x);
            Core::Complex EvaluateAt(Core::Complex x);
            Core::Rational DifferentiateAt(Core::Rational x);
            Core::Rational DefiniteIntegral(Core::Rational lowerLimit, Core::Rational upperLimit);

        };
    }
}


#endif //QUADRATIC_H
