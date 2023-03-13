#ifndef COLOR_UTILS_HPP
#define COLOR_UTILS_HPP

#include <cstdio>
#include "Vector_3D.hpp"

using Color = Vector_3D;

inline void paint_pixel(FILE *img, const Color &pixel_color,
                        const size_t samples_per_pixel) {
    double r = sqrt(pixel_color.x / samples_per_pixel);
    double g = sqrt(pixel_color.y / samples_per_pixel);
    double b = sqrt(pixel_color.z / samples_per_pixel);

    fprintf(img, "%d %d %d\n", static_cast<int>(256 * truncate(r, 0.0, 0.999)),
                               static_cast<int>(256 * truncate(g, 0.0, 0.999)),
                               static_cast<int>(256 * truncate(b, 0.0, 0.999)));
}

#endif