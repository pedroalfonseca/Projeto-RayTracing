#include "Camera.hpp"
#include "Scene.hpp"

// Image

constexpr double aspect_ratio = 16.0 / 9;
constexpr int img_width = 400;
constexpr int img_height = static_cast<int>(img_width / aspect_ratio);
constexpr int samples_per_pixel = 100;
constexpr int max_depth = 50;

// Camera

const Camera camera;

// World

const Material ground{DIFFUSE, Color{0.3, 0.4, 0.1}, 0};
const Material center{DIFFUSE, Color{0.5, 0.1, 0.1}, 0};
const Material left{SPECULAR, Color{0.8, 0.8, 0.8}, 0};
const Material right{SPECULAR, Color{0.8, 0.6, 0.2}, 1};

Sphere spheres[4]{{Point_3D{0, -100.5, -1}, 100, ground},
                  {Point_3D{0, 0, -1}, 0.5, center},
                  {Point_3D{-1, 0, -1}, 0.5, left},
                  {Point_3D{1, 0, -1}, 0.5, right}};

// Render

Color shade(const Ray &ray, int depth) {
    Intersect_info info;

    if (depth <= 0) return Color();

    if (intersect_all(spheres, 4, ray, 0.001, infinity, info)) {
        Ray scattered;
        Color attenuation;
        if (info.material.scatter(ray, info, attenuation, scattered))
            return attenuation * shade(scattered, depth - 1);

        return Color{0, 0, 0};
    }

    Vector_3D uvec = unit_vector(ray.direction);
    double t = 0.5 * (uvec.y + 1);

    return ((1 - t) * Color{1, 1, 1}) + (t * Color{0.5, 0.7, 1});
}

int main() {
    FILE *img = fopen("./image.ppm", "wb");

    fprintf(img, "P3\n%d %d\n255\n", img_width, img_height);
    for (int j = img_height - 1; j >= 0; j--) {
        for (int i = 0; i < img_width; i++) {
            Color pixel_color;
            for (int sample = 0; sample < samples_per_pixel; sample++) {
                double horizontal_coef = (i + random_double()) / (img_width - 1);
                double vertical_coef = (j + random_double()) / (img_height - 1);

                Ray ray = camera.get_ray(horizontal_coef, vertical_coef);
                pixel_color = pixel_color + shade(ray, max_depth);
            }
            paint_pixel(img, pixel_color, samples_per_pixel);
        }
    }

    fclose(img);
}