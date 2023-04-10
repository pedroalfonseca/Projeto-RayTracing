#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../optics/Ray.hpp"

class Camera {
    Point     origin;
    Point     lower_left;
    Vector<3> horizontal;
    Vector<3> vertical;

    Vector<3> w;
    Vector<3> u;
    Vector<3> v;

    Vector<3> v_up;
    double    viewport_height;
    double    viewport_width;

    void
    recalc_attributes_tilt()
    {
        u = unit_vector(cross_product(v_up, w));
        v = cross_product(w, u);

        horizontal = viewport_width * u;
        vertical   = viewport_height * v;
        lower_left = origin - (horizontal / 2) - (vertical / 2) - w;
    }

    void
    recalc_attributes_move()
    {
        lower_left = origin - (horizontal / 2) - (vertical / 2) - w;
    }

public:
    Camera(const Point     &look_from,
           const Point     &look_at,
           const Vector<3> &up,
           const double     vfov,
           const double     aspect_ratio)
    {
        const double theta           = to_radians(vfov);
        const double height          = tan(theta / 2);
                     viewport_height = 2 * height;
                     viewport_width  = aspect_ratio * viewport_height;

        v_up = up;

        w = unit_vector(look_from - look_at);
        u = unit_vector(cross_product(up, w));
        v = cross_product(w, u);

        origin     = look_from;
        horizontal = viewport_width * u;
        vertical   = viewport_height * v;
        lower_left = origin - (horizontal / 2) - (vertical / 2) - w;
    }

    Ray
    get_ray(const double s,
            const double t) const
    {
        return {origin, lower_left + (s * horizontal) + (t * vertical) - origin};
    }

    void
    v_tilt(const double degrees)
    {
        w = x_rotate(w, degrees);
        recalc_attributes_tilt();
    }

    void
    h_tilt(const double degrees)
    {
        w = y_rotate(w, degrees);
        recalc_attributes_tilt();
    }

    void
    move(const double x,
         const double y,
         const double z)
    {
        origin = translate(origin, x, y, z);
        recalc_attributes_move();
    }
};

#endif