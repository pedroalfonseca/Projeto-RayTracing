#ifndef MESH_HPP
#define MESH_HPP

#include "Triangle.hpp"

#include <vector>

class Mesh : public Entity {
    std::vector<Point>                 vertices;
    std::vector<std::array<size_t, 3>> indices;
    std::vector<Triangle>              triangles;
    Material                           material;

public:
    Mesh()
    {
    }

    Mesh(const std::vector<Point>                 &v,
         const std::vector<std::array<size_t, 3>> &i,
         const Material                           &m)
        : vertices(v)
        , indices(i)
        , material(m)
    {
        for (size_t t = 0; t < indices.size(); t++) {
            triangles.push_back({{vertices[indices[t][0]],
                                  vertices[indices[t][1]],
                                  vertices[indices[t][2]]},
                                 material});
        }
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

        for (const auto &triangle : triangles) {
            if (triangle.intersect(r, t_min, cur_closest, cur_info)) {
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
        for (auto &triangle : triangles)
            triangle.move(x, y, z);
    }
};

#endif
