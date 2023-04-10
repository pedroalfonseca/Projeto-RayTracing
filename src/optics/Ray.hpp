#ifndef RAY_HPP
#define RAY_HPP

#include "optics_utils.hpp"

struct Ray {
    Point     origin;
    Vector<3> direction;

    Ray()
    {
    }

    Ray(const Point     &orig,
        const Vector<3> &dir)
        : origin(orig)
        , direction(dir)
    {
    }

    Point
    at(const double t) const
    {
        return origin + (t * direction);
    }
};

#endif