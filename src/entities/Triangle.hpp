#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "entity_utils.hpp"

class Triangle : public Entity {
    std::array<Point, 3>      vertices;
    Vector<3>                 normal;
    std::shared_ptr<Material> material;

public:
    Triangle()
    {
    }

    Triangle(const Point                     &p1,
             const Point                     &p2,
             const Point                     &p3,
             const Vector<3>                 &n,
                   std::shared_ptr<Material>  m)
        : vertices({p1, p2, p3})
        , normal(n)
        , material(m)
    {
    }

    virtual bool
    intersect(const Ray            &r,
              const double          t_min,
              const double          t_max,
                    Intersect_info &info) const override
    {
        const Vector<3> edge1 = vertices[1] - vertices[0];
        const Vector<3> edge2 = vertices[2] - vertices[0];
        const Vector<3> h     = cross_product(r.direction, edge2);

        const double a = dot_product(edge1, h);
        if (a == 0.0)
            return false;

        const Vector<3> s    = r.origin - vertices[0];
        const double    beta = dot_product(s, h) / a;
        if (beta < 0.0 || beta > 1.0)
            return false;

        const Vector<3> q     = cross_product(s, edge1);
        const double    gamma = dot_product(r.direction, q) / a;
        if (gamma < 0.0 || beta + gamma > 1.0)
            return false;

        const double t = dot_product(edge2, q) / a;
        if (t > t_min && t < t_max) {
            info.t        = t;
            info.point    = r.at(info.t);
            info.material = material;

            info.set_face_normal(r, normal);

            return true;
        }

        return false;
    }

    virtual void
    move(const double x,
         const double y,
         const double z) override
    {
        for (size_t i = 0; i < 3; i++)
            vertices[i] = translate(vertices[i], x, y, z);
    }
};

#endif