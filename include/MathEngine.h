//
// Created by Abhishek Singal on 09/07/25.
//

#ifndef MATHENGINE_H
#define MATHENGINE_H

#include <iostream>
#include <math.h>
#include <cmath>
namespace MathEngine{

    namespace Core {
        typedef unsigned long long Natural;
        typedef signed long long Integer;
        typedef long double Rational;



        namespace Constants {
            extern const Rational Pi;
            extern const Rational Pi_2;
            extern const Rational Pi_4;
            extern const Rational e;
        }
    }

}

#endif //MATHENGINE_H
