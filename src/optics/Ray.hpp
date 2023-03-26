#ifndef RAY_HPP
#define RAY_HPP

#include "../math/Vector.hpp"

using Point = Vector<3>;

class Ray {
    Point     origin;
    Vector<3> direction;

public:
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
    get_origin() const
    {
        return origin;
    }

    Vector<3>
    get_direction() const
    {
        return direction;
    }

    Point
    at(const double t) const
    {
        return origin + (t * direction);
    }
};

#endif