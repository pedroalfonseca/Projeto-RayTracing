#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "entity_utils.hpp"

class Sphere : public Entity {
    Point    center;
    double   radius;
    Material material;

    static std::pair<double, double>
    get_uv(const Point &p)
    {
        const double theta = acos(-p[1]);
        const double phi   = atan2(-p[2], p[0]) + pi;

        double u = phi / (2 * pi);
        double v = theta / pi;

        return {u, v};
    }

public:
    Sphere()
    {
    }

    Sphere(const Point    &c,
           const double    r,
           const Material &m)
        : center(c)
        , radius(r)
        , material(m)
    {
    }

    virtual bool
    intersect(const Ray          &r,
              const double        t_min,
              const double        t_max,
                    Intersection &info) const override
    {
        const Vector<3> oc     = r.origin - center;
        const double    a      = r.direction.norm_squared();
        const double    half_b = dot_product(oc, r.direction);
        const double    c      = oc.norm_squared() - radius * radius;
        const double    delta  = half_b * half_b - a * c;

        if (delta < 0)
            return false;

        const double sqrt_delta = sqrt(delta);

        const auto is_invalid = [](const double val,
                                   const double min,
                                   const double max) {
            return val < min || val > max;
        };

        double t = (-half_b - sqrt_delta) / a;
        if (is_invalid(t, t_min, t_max)) {
            t = (-half_b + sqrt_delta) / a;

            if (is_invalid(t, t_min, t_max))
                return false;
        }

        info.t        = t;
        info.point    = r.at(info.t);
        info.material = material;

        const Vector<3> outward_normal = (info.point - center) / radius;
        info.set_face_normal(r, outward_normal);

        const std::pair<double, double> uv = get_uv(outward_normal);
        info.u = uv.first;
        info.v = uv.second;

        return true;
    }

    virtual void
    move(const double x,
         const double y,
         const double z) override
    {
        center = translate(center, x, y, z);
    }
};

#endif