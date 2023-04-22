#include "Vector.hpp"
#include "../optics/optics_utils.hpp"

#include <iostream>

int
main()
{
/*
    Matrix<2, 3> M0;

    Matrix<2, 3> M1{{1, 2, 3},
                    {4, 5, 6}};

    Matrix<2, 3> M2 = M1;

    Matrix<2, 3> N{M1};

    std::cout << M1[0][1] << '\n';

    Matrix<2, 3> M2{{7,  8,  9 },
                    {10, 11, 12}};

    Matrix<2, 3> M3 = M1 + M2;

    Matrix<2, 3> M4 = M2 - M1;

    Matrix<2, 3> M5 = -M2;

    Matrix<3, 1> M6 = {{2},
                       {3},
                       {4}};

    Matrix<2, 1> M7 = M1 * M6;

    Matrix<3, 1> M8 = M6 * 2;

    Matrix<2, 1> M9 = 3 * M7;

    const double theta = to_radians(180);

    const Matrix<3, 3> M{{cos(theta), -sin(theta), 0},
                         {sin(theta),  cos(theta), 0},
                         {         0,           0, 1}};

    const Vector<3> V{1,
                      2,
                      3};

    const Vector<3> res = M * V;
*/

    const Vector<3> vec1{0.0,
                         0.0,
                         5.0};

    const Vector<3> vec2{0.0,
                         0.0,
                        -1.0};

    const Vector<3> vec3 = unit_vector(vec1 - vec2);

    const Vector<3> vec4 = translate(vec3, -vec3[0], -vec3[1], -vec3[2]);
}