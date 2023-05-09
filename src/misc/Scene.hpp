#ifndef SCENE_HPP
#define SCENE_HPP

#include "../entities/Plane.hpp"
#include "../entities/Sphere.hpp"
#include "../entities/Mesh.hpp"
#include "../optics/Light.hpp"

#include <vector>

class Scene : public Entity {
    std::vector<std::shared_ptr<Entity>> entities;
    std::vector<Light>                   lights;

    double
    get_k_shadow(const Ray    &r,
               const double  t_min,
               const double  t_max) const
    {
        Intersection cur_info;

        for (auto &entity : entities)
            if (entity->intersect(r, t_min, t_max, cur_info))
                return cur_info.material.kt;

        return 1.0;
    }

public:
    Scene()
    {
    }

    std::shared_ptr<Entity>
    get_entity(const size_t i)
    {
        return entities[i];
    }

    void
    add_entity(std::shared_ptr<Entity> entity)
    {
        entities.push_back(entity);
    }

    void
    add_light(const Light &light)
    {
        lights.push_back(light);
    }

    Color
    phong(const Point        &cam_origin,
          const Color        &background,
          const Ray          &r,
                Intersection &info) const
    {
        const Vector<3> view_direction = unit_vector(cam_origin - info.point);

        Color I = background * info.material.ka;

        for (const auto &light : lights) {
            const Vector<3> light_direction = light.position - info.point;

            const Ray light_ray{info.point + info.face_normal * 0.01, light_direction};

            const double k_shadow = get_k_shadow(light_ray, 0.0001, infinity);

            const Vector<3> reflected_direction = unit_vector(reflected_vector(-light_direction, info.face_normal));

            const double diffuse_factor = dot_product(light_direction, info.face_normal);
            const Color  tmp            = light.albedo * info.material.albedo->get_value(info.point);
            const Color  diffuse_color  = tmp * info.material.kd * fmax(diffuse_factor, 0.0);

            const double specular_factor = pow(dot_product(reflected_direction, view_direction), info.material.p);
            const Color  specular_color  = light.albedo * info.material.ks * fmax(specular_factor, 0.0);

            I += (diffuse_color + specular_color) * k_shadow;
        }

        return I;
    }

    virtual bool
    intersect(const Ray          &r,
              const double        t_min,
              const double        t_max,
                    Intersection &info) const override
    {
        Intersection cur_info;

        bool   intersect   = false;
        double cur_closest = t_max;

        for (const auto &entity : entities) {
            if (entity->intersect(r, t_min, cur_closest, cur_info)) {
                intersect   = true;
                cur_closest = cur_info.t;
                info        = cur_info;
            }
        }

        return intersect;
    }

    virtual void
    move(const double x,
         const double y,
         const double z) override
    {
        for (auto &entity : entities)
            entity->move(x, y, z);
    }
};

#endif