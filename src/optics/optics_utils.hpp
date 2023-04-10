#ifndef COLOR_UTILS_HPP
#define COLOR_UTILS_HPP

#include "../math/Vector.hpp"

#include <iostream>

using Point = Vector<3>;
using Color = Vector<3>;

inline Point
translate(const Point  &p,
          const double  x_translation,
          const double  y_translation,
          const double  z_translation)
{
    const Matrix<4, 4> translation_matrix{{1, 0, 0, x_translation},
                                          {0, 1, 0, y_translation},
                                          {0, 0, 1, z_translation},
                                          {0, 0, 0,             1}};

    const Vector<4> homogenized_point{p[0],
                                      p[1],
                                      p[2],
                                         1};

    const Vector<4> translated_point = translation_matrix * homogenized_point;

    return {translated_point[0],
            translated_point[1],
            translated_point[2]};
}

inline Point
x_rotate(const Point  &p,
         const double  degrees)
{
    const double theta = to_radians(degrees);

    const Matrix<4, 4> rotation_matrix{{1,          0,           0, 0},
                                       {0, cos(theta), -sin(theta), 0},
                                       {0, sin(theta),  cos(theta), 0},
                                       {0,          0,           0, 1}};

    const Vector<4> homogenized_point{p[0],
                                      p[1],
                                      p[2],
                                         1};

    const Vector<4> rotated_point = rotation_matrix * homogenized_point;

    return {rotated_point[0],
            rotated_point[1],
            rotated_point[2]};
}

inline Point
y_rotate(const Point  &p,
         const double  degrees)
{
    const double theta = to_radians(degrees);

    const Matrix<4, 4> rotation_matrix{{ cos(theta), 0, sin(theta), 0},
                                       {          0, 1,          0, 0},
                                       {-sin(theta), 0, cos(theta), 0},
                                       {          0, 0,          0, 1}};

    const Vector<4> homogenized_point{p[0],
                                      p[1],
                                      p[2],
                                         1};

    const Vector<4> rotated_point = rotation_matrix * homogenized_point;

    return {rotated_point[0],
            rotated_point[1],
            rotated_point[2]};
}

inline Point
z_rotate(const Point  &p,
         const double  degrees)
{
    const double theta = to_radians(degrees);

    const Matrix<4, 4> rotation_matrix{{cos(theta), -sin(theta), 0, 0},
                                       {sin(theta),  cos(theta), 0, 0},
                                       {         0,           0, 1, 0},
                                       {         0,           0, 0, 1}};

    const Vector<4> homogenized_point{p[0],
                                      p[1],
                                      p[2],
                                         1};

    const Vector<4> rotated_point = rotation_matrix * homogenized_point;

    return {rotated_point[0],
            rotated_point[1],
            rotated_point[2]};
}

inline void
paint_pixel(      std::ostream &out,
            const Color        &pixel_color,
            const size_t        samples_per_pixel)
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