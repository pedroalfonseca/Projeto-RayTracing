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

const Material crimson  {std::make_shared<Matte>(Color{0.5, 0.1, 0.1}), 0.0, 0.1, 0.6, 0.3, 0.0, 0.0, 3.0};
const Material indigo   {std::make_shared<Matte>(Color{0.1, 0.0, 0.5}), 0.0, 0.1, 0.6, 0.3, 0.0, 0.0, 3.0};
const Material turquoise{std::make_shared<Matte>(Color{0.0, 0.5, 0.3}), 0.0, 0.1, 0.6, 0.3, 0.0, 0.0, 3.0};
const Material olive    {std::make_shared<Matte>(Color{0.3, 0.4, 0.1}), 0.0, 0.1, 0.6, 0.3, 0.0, 0.0, 3.0};

const Material chess{std::make_shared<Checker>(Color{0.0, 0.0, 0.0}, Color{1.0, 1.0, 1.0}), 0.0, 0.1, 0.6, 0.3, 0.0, 0.0, 3.0};

const Material steel {std::make_shared<Matte>(Color{0.2, 0.2, 0.2}), 0.0, 0.1, 0.6, 0.6, 0.2, 0.0, 3.0};
const Material gold  {std::make_shared<Matte>(Color{0.8, 0.6, 0.2}), 0.0, 0.1, 0.6, 0.6, 0.2, 0.0, 3.0};
const Material mirror{std::make_shared<Matte>(Color{0.4, 0.4, 0.4}), 0.0, 0.1, 0.3, 0.6, 0.6, 0.0, 3.0};
const Material ivory {std::make_shared<Matte>(Color{0.4, 0.4, 0.3}), 0.0, 0.1, 0.6, 0.6, 0.1, 0.0, 3.0};

const Material glass{std::make_shared<Matte>(Color{0.0, 0.0, 1.0}), 1.5, 0.1, 0.0, 0.0, 0.1, 0.9, 3.0};
const Material ruby {std::make_shared<Matte>(Color{0.3, 0.0, 0.0}), 1.5, 0.1, 0.6, 0.0, 0.1, 0.3, 3.0};

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