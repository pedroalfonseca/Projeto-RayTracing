#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "Camera.hpp"
#include "Scene.hpp"

class Renderer {
    size_t img_width;
    size_t img_height;
    size_t samples_per_pixel;
    size_t max_depth;

    Color
    shade(const Color  &background,
          const Scene  &scene,
          const Ray    &r,
          const size_t  depth)
    {
        Intersect_info info;

        if (depth <= 0)
            return Color{};

        if (!scene.intersect(r, 0.001, infinity, info))
            return background;

        Ray   scattered;
        Color attenuation;
        Color emitted = info.material->emitted(info.u, info.v, info.point);

        if (!info.material->scatter(r, info, attenuation, scattered))
            return emitted;

        return emitted + (attenuation * shade(background, scene, scattered, depth - 1));
    }

public:
    Renderer(const size_t iw,
             const size_t ih,
             const size_t spp,
             const size_t md)
        : img_width(iw)
        , img_height(ih)
        , samples_per_pixel(spp)
        , max_depth(md)
    {
    }

    void
    render(const Camera &camera,
           const Color  &background,
           const Scene  &scene)
    {
        std::cout << "P3\n" << img_width << ' ' << img_height << "\n255\n";
        for (long j = img_height - 1; j >= 0; j--) {
            for (size_t i = 0; i < img_width; i++) {
                Color pixel_color;

                for (size_t sample = 0; sample < samples_per_pixel; sample++) {
                    const double hcoef = (i + random_double()) / (img_width - 1);
                    const double vcoef = (j + random_double()) / (img_height - 1);

                    const Ray r = camera.get_ray(hcoef, vcoef);

                    pixel_color += shade(background, scene, r, max_depth);
                }

                paint_pixel(std::cout, pixel_color, samples_per_pixel);
            }
        }
    }
};

#endif