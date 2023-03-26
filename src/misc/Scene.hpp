#ifndef SCENE_HPP
#define SCENE_HPP

#include "../entities/Sphere.hpp"

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

        bool   intersect = false;
        double cur_t_max = t_max;

        for (auto &entity : entities) {
            if (entity->intersect(r, t_min, cur_t_max, cur_info)) {
                intersect = true;
                cur_t_max = cur_info.t;
                info      = cur_info;
            }
        }

        return intersect;
    }
};

#endif