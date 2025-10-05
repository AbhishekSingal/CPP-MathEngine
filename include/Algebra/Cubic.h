//
// Created by Abhishek Singal on 15/07/25.
//

#ifndef CUBIC_H
#define CUBIC_H

#include <MathEngine.h>
#include <Core/Complex.h>

namespace MathEngine {
    namespace Algebra {
        class Cubic {
        private:
            Core::Rational a, b, c , d;
        public:
            Cubic(Core::Rational a, Core::Rational b, Core::Rational c,Core::Rational d);
            Cubic(Core::Rational sum, Core::Rational pairwiseSum, Core::Rational product);
            std::vector<Core::Rational> GetRealRoots();
            std::vector<Core::Complex> GetComplexRoots();
            Core::Rational EvaluateAt(Core::Rational x);
            Core::Complex EvaluateAt(Core::Complex x);
            Core::Rational DifferentiateAt(Core::Rational x);
            Core::Rational DefiniteIntegral(Core::Rational lowerLimit, Core::Rational upperLimit);
        };
    }
}

#endif //CUBIC_H
