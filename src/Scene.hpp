#ifndef SCENE_HPP
#define SCENE_HPP

#include "Sphere.hpp"

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