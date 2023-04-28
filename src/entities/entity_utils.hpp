#ifndef ENTITY_UTILS_HPP
#define ENTITY_UTILS_HPP

#include "../optics/Ray.hpp"
#include "texture_utils.hpp"

struct Material {
    std::shared_ptr<Texture> albedo;
    double                   refraction_index;
    double                   ka;
    double                   kd;
    double                   ks;
    double                   kr;
    double                   kt;
    double                   p;
};

struct Intersection {
    Point     point;
    Vector<3> face_normal;
    double    t;
    double    u;
    double    v;
    bool      intersects_front_face;
    Material  material;

    void
    set_face_normal(const Ray       &r,
                    const Vector<3> &outward_normal)
    {
        intersects_front_face = dot_product(r.direction, outward_normal) < 0.0;

        face_normal = intersects_front_face ? outward_normal : -outward_normal;
    }
};

class Entity {
public:
    virtual bool
    intersect(const Ray          &r,
              const double        t_min,
              const double        t_max,
                    Intersection &info) const = 0;

    virtual void
    move(const double x,
         const double y,
         const double z) = 0;
};

#endif