#ifndef ENTITY_UTILS_HPP
#define ENTITY_UTILS_HPP

#include "../optics/color_utils.hpp"
#include "../optics/Ray.hpp"
#include "material_utils.hpp"

#include <memory>

class Material;

struct Intersect_info {
    Point                     point;
    Vector<3>                 face_normal;
    double                    t;
    double                    u;
    double                    v;
    bool                      intersects_front_face;
    std::shared_ptr<Material> material;

    void
    set_face_normal(const Ray       &r,
                    const Vector<3> &outward_normal)
    {
        intersects_front_face = dot_product(r.get_direction(), outward_normal) < 0.0;

        face_normal = intersects_front_face ? outward_normal : -outward_normal;
    }
};

class Entity {
public:
    virtual bool
    intersect(const Ray            &r,
              const double          t_min,
              const double          t_max,
                    Intersect_info &info) const = 0;
};

#endif