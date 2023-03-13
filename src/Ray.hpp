#ifndef RAY_HPP
#define RAY_HPP

#include "Vector_3D.hpp"

using Point_3D = Vector_3D;

struct Ray {
    Point_3D origin;
    Vector_3D direction;

    Point_3D at(const double scalar) const {
        return origin + (scalar * direction);
    }
};

#endif