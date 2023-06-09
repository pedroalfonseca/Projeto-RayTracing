#ifndef TEXTURE_UTILS_HPP
#define TEXTURE_UTILS_HPP

#include "../optics/Ray.hpp"

#include <memory>

class Texture {
public:
    virtual Color
    get_value(const Point &p) const = 0;
};

class Matte : public Texture {
    Color value;

public:
    Matte()
    {
    }

    Matte(const double r,
          const double g,
          const double b)
        : value{r, g, b}
    {
    }

    Matte(const Color &c)
        : value(c)
    {
    }

    virtual Color
    get_value(const Point &p) const override
    {
        return value;
    }
};

class Checker : public Texture {
    std::shared_ptr<Texture> odd;
    std::shared_ptr<Texture> even;

public:
    Checker()
    {
    }

    Checker(std::shared_ptr<Texture> t1,
            std::shared_ptr<Texture> t2)
        : odd(t1)
        , even(t2)
    {
    }

    Checker(const Color &c1,
            const Color &c2)
        : odd(std::make_shared<Matte>(c1))
        , even(std::make_shared<Matte>(c2))
    {
    }

    virtual Color
    get_value(const Point &p) const override
    {
        const double sin_product = sin(10 * p[0]) * sin(10 * p[1]) * sin(10 * p[2]);

        if (sin_product < 0)
            return odd->get_value(p);

        return even->get_value(p);
    }
};

#endif