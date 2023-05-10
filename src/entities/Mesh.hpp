#ifndef MESH_HPP
#define MESH_HPP

#include "Triangle.hpp"

#include <vector>

class Mesh : public Entity {
    std::vector<Point>                 vertices;
    std::vector<std::array<size_t, 3>> indices;
    std::vector<Triangle>              triangles;
    Material                           material;

    void
    set_triangles()
    {
        for (size_t t = 0; t < indices.size(); t++) {
            triangles.push_back({{vertices[indices[t][0]],
                                  vertices[indices[t][1]],
                                  vertices[indices[t][2]]},
                                 material});
        }
    }

    void
    set_indices(const std::vector<size_t> &angles,
                const size_t               angular_diff)
    {
        size_t lower_bound = 0;
        size_t upper_bound = angles.size() - 1;

        if (upper_bound - lower_bound < 2)
            return;

        for (size_t i = lower_bound; i <= upper_bound - 2; i++) {
            for (size_t j = i + 1; j <= upper_bound - 1; j++) {
                for (size_t k = j + 1; k <= upper_bound; k++) {
                    if (fabs((int)angles[i] - (int)angles[j]) <= angular_diff &&
                        fabs((int)angles[i] - (int)angles[k]) <= angular_diff &&
                        fabs((int)angles[j] - (int)angles[k]) <= angular_diff) {
                        std::array<size_t, 3> subset{i, j, k};
                        indices.push_back(subset);
                    }
                }
            }
        }
    }

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
        set_triangles();
    }

    Mesh(const Point    &center,
         const double    minor_radius,
         const double    major_radius,
         const size_t    num_circles,
         const size_t    verts_per_circle,
         const Material &mat)
    {
        std::vector<size_t> angles;

        for (size_t theta = 0; theta <= 360; theta += (360 / num_circles)) {
            double theta_rad = to_radians(theta);

            Vector<3> p{major_radius * cos(theta_rad),
                        major_radius * sin(theta_rad),
                                                  0.0};

            Vector<3> v1{cos(theta_rad),
                         sin(theta_rad),
                                    0.0};

            Vector<3> v2{0.0,
                         0.0,
                         1.0};

            for (size_t phi = 0; phi <= 360; phi += (360 / verts_per_circle)) {
                double phi_rad = to_radians(phi);

                Point vert = center + p + (minor_radius * cos(phi_rad) * v1) + (minor_radius * sin(phi_rad) * v2);

                vertices.push_back(vert);
                angles.push_back(theta);
            }
        }

        material = mat;

        set_indices(angles, (360 / num_circles));
        set_triangles();
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
