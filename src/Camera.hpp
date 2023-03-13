#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Ray.hpp"

struct Camera {
    Point_3D origin;
    Point_3D lower_left;
    Vector_3D horizontal;
    Vector_3D vertical;

    Camera() {
        const double aspect_ratio = 16.0 / 9;
        const double viewport_height = 2;
        const double viewport_width = aspect_ratio * viewport_height;
        const double focal_length = 1;

        horizontal = {viewport_width, 0, 0};
        vertical = {0, viewport_height, 0};
        lower_left = origin - (horizontal / 2) - (vertical / 2)
                     - Point_3D{0, 0, focal_length};
    }

    Ray get_ray(const double horizontal_coef, const double vertical_coef) const {
        return {origin, lower_left + (horizontal_coef * horizontal)
                        + (vertical_coef * vertical) - origin};
    }
};

#endif