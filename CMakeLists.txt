cmake_minimum_required(VERSION 3.31)
project(MathEngine)

set(CMAKE_CXX_STANDARD 20)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(MathEngine SHARED
        source/Core/ExpressionEvaluater.cpp
        include/Core/ExpressionEvaluater.h
        include/MathEngine.h
        include/Errors/MathEngineErrors.h
        source/Core/Utils.cpp
        include/Core/Utils.h
        source/MathEngine.cpp
        source/Core/Function.cpp
        include/Core/Function.h
        source/Core/Complex.cpp
        include/Core/Complex.h
        include/Core/Functions.h
        source/Algebra/BasicAlgebraicExpression.cpp
        include/Algebra/BasicAlgebraicExpression.h
        include/Algebra/Quadratic.h
        source/Algebra/Quadratic.cpp
        include/Algebra/Cubic.h
        source/Algebra/Cubic.cpp
        include/Algebra/AlgebraicTerm.h
        source/Algebra/AlgebraicTerm.cpp
)


add_executable(main main/main.cpp
        include/Algebra/AlgebraicTerm.h
        source/Algebra/AlgebraicTerm.cpp
)
add_executable(MathConsole source/MathConsole/MathConsole.cpp
        include/Algebra/AlgebraicTerm.h
        source/Algebra/AlgebraicTerm.cpp
)

target_link_libraries(main PRIVATE MathEngine)
target_link_libraries(MathConsole PRIVATE MathEngine)

