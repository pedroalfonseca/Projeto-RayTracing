#ifndef COLOR_UTILS_HPP
#define COLOR_UTILS_HPP

#include "../math/Vector.hpp"

#include <iostream>

using Color = Vector<3>;

inline void
paint_pixel(      std::ostream  &out,
            const Color         &pixel_color,
            const size_t         samples_per_pixel)
{
    const double quotient = 1.0 / samples_per_pixel;

    const double r = sqrt(pixel_color[0] * quotient);
    const double g = sqrt(pixel_color[1] * quotient);
    const double b = sqrt(pixel_color[2] * quotient);

    out << static_cast<int>(256 * truncate(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * truncate(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * truncate(b, 0.0, 0.999)) << '\n';
}

#endif