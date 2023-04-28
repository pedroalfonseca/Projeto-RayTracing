#ifndef RAY_HPP
#define RAY_HPP

#include "optics_utils.hpp"

struct Ray {
    Point     origin;
    Vector<3> direction;

    Point
    at(const double t) const
    {
        return origin + (t * direction);
    }
};

inline Ray
reflected_ray(const Ray       &r_in,
              const Point     &point,
              const Vector<3> &face_normal)
{
    Point     reflected_origin    = point + face_normal * 0.01;
    Vector<3> reflected_direction = reflected_vector(r_in.direction, face_normal);

    return {reflected_origin, reflected_direction};
}

inline Ray
refracted_ray(const Ray       &r_in,
              const double     refraction_index,
              const bool       intersects_front_face,
              const Point     &point,
              const Vector<3> &face_normal,
                    bool      &total_reflection)
{
    const double refraction_ratio = intersects_front_face ? (1 / refraction_index) : refraction_index;

    Vector<3> refracted_origin    = point - face_normal * 0.01;
    Vector<3> refracted_direction = refracted_vector(r_in.direction, face_normal, refraction_ratio);

    if (!refracted_direction.is_null())
        return {refracted_origin, refracted_direction};

    total_reflection = true;

    return reflected_ray(r_in, point, face_normal);
}

#endif