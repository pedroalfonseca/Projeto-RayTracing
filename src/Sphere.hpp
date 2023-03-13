#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Ray.hpp"

struct Intersect_info {
    double t;
    Point_3D point;
    Vector_3D face_normal;
    bool hits_front_face;

    void set_face_normal(const Ray &ray, const Vector_3D &outward_normal) {
        hits_front_face = dot_product(ray.direction, outward_normal) < 0.0;
        face_normal = hits_front_face ? outward_normal : -outward_normal;
    }
};

struct Sphere {
    Point_3D center;
    double radius;

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

        return true;
    }
};

bool intersect_all(Sphere spheres[], const size_t n, const Ray &ray,
                   const double t_min, const double t_max,
                   Intersect_info &info) {
    Intersect_info cur_info;
    bool intersect = false;
    double cur_t_max = t_max;

    for (size_t i = 0; i < n; i++) {
        if (spheres[i].intersect(ray, t_min, cur_t_max, cur_info)) {
            intersect = true;
            cur_t_max = cur_info.t;
            info = cur_info;
        }
    }

    return intersect;
}

#endif