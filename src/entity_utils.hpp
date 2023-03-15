#ifndef MATERIAL_UTILS_HPP
#define MATERIAL_UTILS_HPP

#include "color_utils.hpp"
#include "Ray.hpp"

struct Intersect_info;

enum Material_tag { DIFFUSE, SPECULAR };

struct Material {
    Material_tag tag;
    Color albedo;
    double fuzz;

    bool scatter(const Ray &r_in, const Intersect_info &info,
                 Color &attenuation, Ray &scattered) const;
};

struct Intersect_info {
    double t;
    Point_3D point;
    Vector_3D face_normal;
    bool intersects_front_face;
    Material material;

    void set_face_normal(const Ray &ray, const Vector_3D &outward_normal) {
        intersects_front_face = dot_product(ray.direction, outward_normal) < 0.0;
        face_normal = intersects_front_face ? outward_normal : -outward_normal;
    }
};

bool Material::scatter(const Ray &r_in, const Intersect_info &info,
                       Color &attenuation, Ray &scattered) const {
    if (tag == DIFFUSE) {
        Vector_3D scatter_direction = info.face_normal + random_unit_vector();

        if (scatter_direction.is_near_null())
            scatter_direction = info.face_normal;

        scattered = {info.point, scatter_direction};
        attenuation = albedo;

        return true;
    } else {
        Vector_3D reflected = reflected_vector(unit_vector(r_in.direction),
                                                info.face_normal);
        scattered = {info.point,
                        reflected + fuzz * random_vector_in_unit_sphere()};
        attenuation = albedo;

        return (dot_product(scattered.direction, info.face_normal) > 0);
    }

    return false;
}

#endif