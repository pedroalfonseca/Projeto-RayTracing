#ifndef SCENE_HPP
#define SCENE_HPP

#include "../entities/Plane.hpp"
#include "../entities/Sphere.hpp"
#include "../entities/Mesh.hpp"
//#include "../optics/Light.hpp"

#include <vector>

class Scene : public Entity {
    std::vector<std::shared_ptr<Entity>> entities;
    //std::vector<Light>                   lights;

public:
    Scene()
    {
    }

    void
    add_entity(std::shared_ptr<Entity> entity)
    {
        entities.push_back(entity);
    }

/*
    void
    add_light(const Light &light)
    {
        lights.push_back(light);
    }
*/

    virtual bool
    intersect(const Ray            &r,
              const double          t_min,
              const double          t_max,
                    Intersect_info &info) const override
    {
        Intersect_info cur_info;

        bool   intersect   = false;
        double cur_closest = t_max;

        for (auto &entity : entities) {
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