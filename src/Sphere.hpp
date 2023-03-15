#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "entity_utils.hpp"

struct Sphere {
    Point_3D center;
    double radius;
    Material material;

    bool intersect(const Ray &ray, const double t_min, const double t_max,
                   Intersect_info &info) {
        Vector_3D oc = ray.origin - center;
        double a = ray.direction.norm_squared();
        double half_b = dot_product(oc, ray.direction);
        double c = oc.norm_squared() - radius * radius;
        double delta = half_b * half_b - a * c;

        if (delta < 0) return false;

        double sqrt_delta = sqrt(delta);

        auto is_invalid = [](const double val, const double min,
                             const double max) {
            return val < min || val > max;
        };

        double root = (-half_b - sqrt_delta) / a;
        if (is_invalid(root, t_min, t_max)) {
            root = (-half_b + sqrt_delta) / a;

            if (is_invalid(root, t_min, t_max)) return false;
        }

        info.t = root;
        info.point = ray.at(info.t);
        Vector_3D outward_normal = (info.point - center) / radius;
        info.set_face_normal(ray, outward_normal);
        info.material = material;

        return true;
    }
};

#endif