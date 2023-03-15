#ifndef COLOR_UTILS_HPP
#define COLOR_UTILS_HPP

#include "Vector_3D.hpp"

#include <cstdio>

using Color = Vector_3D;

inline void paint_pixel(FILE *img, const Color &pixel_color,
                        const size_t samples_per_pixel) {
    const double quotient = 1.0 / samples_per_pixel;

    const double r = sqrt(pixel_color.x * quotient);
    const double g = sqrt(pixel_color.y * quotient);
    const double b = sqrt(pixel_color.z * quotient);

    fprintf(img, "%d %d %d\n", static_cast<int>(256 * truncate(r, 0.0, 0.999)),
                               static_cast<int>(256 * truncate(g, 0.0, 0.999)),
                               static_cast<int>(256 * truncate(b, 0.0, 0.999)));
}

#endif