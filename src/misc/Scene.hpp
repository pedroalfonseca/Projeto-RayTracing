#ifndef SCENE_HPP
#define SCENE_HPP

#include "../entities/Plane.hpp"
#include "../entities/Sphere.hpp"
#include "../entities/Mesh.hpp"

#include <vector>

class Scene : public Entity {
    std::vector<std::shared_ptr<Entity>> entities;

public:
    Scene()
    {
    }

    void
    add(std::shared_ptr<Entity> entity)
    {
        entities.push_back(entity);
    }

    void
    clear()
    {
        entities.clear();
    }

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

    std::shared_ptr<Entity>
    operator[](const size_t i)
    {
        return entities[i];
    }
};

#endif