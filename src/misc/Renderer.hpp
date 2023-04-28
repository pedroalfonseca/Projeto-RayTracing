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
    shade(const Point  &cam_origin,
          const Color  &background,
          const Scene  &scene,
          const Ray    &r,
          const size_t  depth)
    {
        Intersection info;
        Color        emitted;

        if (scene.intersect(r, 0.0001, infinity, info)) {
            emitted += scene.phong(cam_origin, background, r, info);

            if (depth <= 0)
                return emitted;

            if (info.material.kr > 0.0) {
                Ray r_reflected = reflected_ray(r, info.point, info.face_normal);

                emitted += shade(cam_origin, background, scene, r_reflected, depth - 1) * info.material.kr;
            }

            if (info.material.refraction_index > 0 && info.material.kt > 0) {
                bool total_reflection = false;

                Ray r_refracted = refracted_ray(r, info.material.refraction_index, info.intersects_front_face,
                                                info.point, info.face_normal, total_reflection);

                const double k = total_reflection ? info.material.kr : info.material.kt;

                emitted += shade(cam_origin, background, scene, r_refracted, depth - 1) * k;
            }

            return emitted;
        }

        return background;
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

                    pixel_color += shade(r.origin, background, scene, r, max_depth);
                }

                paint_pixel(std::cout, pixel_color, samples_per_pixel);
            }
        }
    }
};

#endif