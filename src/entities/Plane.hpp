#ifndef PLANE_HPP
#define PLANE_HPP

#include "entity_utils.hpp"

class Plane : public Entity {
    Point                     point;
    Vector<3>                 normal;
    std::shared_ptr<Material> material;

public:
    Plane()
    {
    }

    Plane(const Point                     &p,
          const Vector<3>                 &n,
                std::shared_ptr<Material>  m)
        : point(p)
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
        constexpr double epsilon = 0.000000000000001;

        const double a = dot_product(r.direction, normal);
        if (a > -epsilon && a < epsilon)
            return false;

        const double t = dot_product((point - r.origin), normal) / a;
        if (t > epsilon) {
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
        point = translate(point, x, y, z);
    }
};

#endif