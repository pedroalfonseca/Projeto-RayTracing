#ifndef MATERIAL_UTILS_HPP
#define MATERIAL_UTILS_HPP

#include "entity_utils.hpp"
#include "texture_utils.hpp"

struct Intersect_info;

class Material {
public:
    virtual Color
    emitted(const double  u,
            const double  v,
            const Point  &p) const
    {
        return Color{};
    }

    virtual bool
    scatter(const Ray            &r_in,
            const Intersect_info &info,
                  Color          &attenuation,
                  Ray            &scattered) const = 0;
};

class Diffuse : public Material {
    std::shared_ptr<Texture> albedo;

public:
    Diffuse(const Color &a)
        : albedo(std::make_shared<Solid>(a))
    {
    }

    Diffuse(std::shared_ptr<Texture> a)
        : albedo(a)
    {
    }

    virtual bool
    scatter(const Ray            &r_in,
            const Intersect_info &info,
                  Color          &attenuation,
                  Ray            &scattered) const override
    {
        Vector<3> scatter_direction = info.face_normal + random_unit_vector<3>();

        if (scatter_direction.is_near_null())
            scatter_direction = info.face_normal;

        scattered   = {info.point, scatter_direction};
        attenuation = albedo->get_value(info.u, info.v, info.point);

        return true;
    }
};

class Specular : public Material {
    Color albedo;
    double fuzz;

public:
    Specular(const Color &a, const double f)
        : albedo(a)
        , fuzz(f)
    {
    }

    virtual bool
    scatter(const Ray            &r_in,
            const Intersect_info &info,
                  Color          &attenuation,
                  Ray            &scattered) const override
    {
        const Vector<3> reflected = reflected_vector(unit_vector(r_in.get_direction()), info.face_normal);

        scattered   = {info.point, reflected + fuzz * random_vector_in_unit_sphere<3>()};
        attenuation = albedo;

        return dot_product(scattered.get_direction(), info.face_normal) > 0;
    }
};

class Dielectric : public Material {
    double refraction_index;

public:
    Dielectric(const double ri)
        : refraction_index(ri)
    {
    }

    virtual bool
    scatter(const Ray            &r_in,
            const Intersect_info &info,
                  Color          &attenuation,
                  Ray            &scattered) const override
    {
        attenuation = {1.0, 1.0, 1.0};

        const double refraction_ratio = info.intersects_front_face ? (1 / refraction_index) : refraction_index;

        const Vector<3> unit_direction = unit_vector(r_in.get_direction());
        const double    cos_theta      = fmin(dot_product(-unit_direction, info.face_normal), 1.0);
        const double    sin_theta      = sqrt(1.0 - cos_theta * cos_theta);
        const bool      cannot_refract = (refraction_ratio * sin_theta) > 1.0;
        const double    r0             = pow((1 - cos_theta) / (1 + refraction_ratio), 2);
        const double    reflectance    = r0 + (1 - r0) * pow((1 - cos_theta), 5);

        const Vector<3> direction = cannot_refract || (reflectance > random_double())
                                        ? reflected_vector(unit_direction, info.face_normal)
                                        : refracted_vector(unit_direction, info.face_normal, refraction_ratio);

        scattered = {info.point, direction};

        return true;
    }
};

class Light : public Material {
    std::shared_ptr<Texture> emit;

public:
    Light(std::shared_ptr<Texture> a)
        : emit(a)
    {
    }

    Light(const Color &c)
        : emit(std::make_shared<Solid>(c))
    {
    }

    virtual bool
    scatter(const Ray            &r_in,
            const Intersect_info &info,
                  Color          &attenuation,
                  Ray            &scattered) const override
    {
        return false;
    }

    virtual Color
    emitted(const double  u,
            const double  v,
            const Point  &p) const override
    {
        return emit->get_value(u, v, p);
    }
};

const auto grass  = std::make_shared<Diffuse>(Color{0.3,  0.4, 0.1 });
const auto rubber = std::make_shared<Diffuse>(Color{0.5,  0.1, 0.1 });
const auto aqua   = std::make_shared<Diffuse>(Color{0.01, 0.5, 0.31});

auto checker = std::make_shared<Checker>(Color{0.0, 0.0, 0.0}, Color{1.0, 1.0, 1.0});
const auto chess   = std::make_shared<Diffuse>(checker);

const auto mirror = std::make_shared<Specular>(Color{0.8, 0.8, 0.8}, 0.0);
const auto gold   = std::make_shared<Specular>(Color{0.8, 0.6, 0.2}, 1.0);

const auto glass = std::make_shared<Dielectric>(1.5);

const auto light = std::make_shared<Light>(Color{4.0, 4.0, 4.0});

#endif