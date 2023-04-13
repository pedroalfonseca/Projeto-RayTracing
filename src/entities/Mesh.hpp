#ifndef MESH_HPP
#define MESH_HPP

#include "Triangle.hpp"

#include <vector>

class Mesh : public Entity {
    std::vector<Point>                 vertices;
    std::vector<std::array<size_t, 3>> indices;
    std::vector<Triangle>              triangles;
    std::shared_ptr<Material>          material;

public:
    Mesh()
    {
    }

    Mesh(const std::vector<Point>                 &v,
         const std::vector<std::array<size_t, 3>> &i,
               std::shared_ptr<Material>           m)
        : vertices(v)
        , indices(i)
        , material(m)
    {
        for (size_t i = 0; i < indices.size(); i++) {
            triangles.emplace_back(vertices[indices[i][0]],
                                   vertices[indices[i][1]],
                                   vertices[indices[i][2]],
                                   material);
        }
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
