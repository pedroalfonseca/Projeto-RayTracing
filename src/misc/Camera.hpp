#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../optics/Ray.hpp"

class Camera {
    Point     origin;
    Point     lower_left;
    Vector<3> horizontal;
    Vector<3> vertical;

public:
    Camera(const Point     &look_from,
           const Point     &look_at,
           const Vector<3> &up,
           const double     vfov,
           const double     aspect_ratio)
    {
        const double theta           = to_radians(vfov);
        const double height          = tan(theta / 2);
        const double viewport_height = 2 * height;
        const double viewport_width  = aspect_ratio * viewport_height;

        const Vector<3> w = unit_vector(look_from - look_at);
        const Vector<3> u = unit_vector(cross_product(up, w));
        const Vector<3> v = cross_product(w, u);

        origin     = look_from;
        horizontal = viewport_width * u;
        vertical   = viewport_height * v;
        lower_left = origin - (horizontal / 2) - (vertical / 2) - w;
    }

    Ray
    get_ray(const double s,
            const double t) const
    {
        return {origin,
                lower_left + (s * horizontal) + (t * vertical) - origin};
    }
};

#endif