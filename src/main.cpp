#include "Camera.hpp"
#include "color_utils.hpp"
#include "Sphere.hpp"

// Image

constexpr double aspect_ratio = 16.0 / 9;
constexpr int img_width = 400;
constexpr int img_height = static_cast<int>(img_width / aspect_ratio);
constexpr int samples_per_pixel = 100;
constexpr int max_depth = 50;

// Camera

const Camera camera;

// World

Sphere spheres[2]{{Point_3D{0, 0, -1}, 0.5},
                  {Point_3D{0, -100.5, -1}, 100}};

// Render

Color shade(const Ray &ray, int depth) {
    Intersect_info info;

    if (depth <= 0) return Color();

    if (intersect_all(spheres, 2, ray, 0.001, infinity, info)) {
        Point_3D target = info.point
                          + Vector_3D::random_in_hemisphere(info.face_normal);
        return 0.5 * shade(Ray{info.point, target - info.point}, depth - 1);
    }

    Vector_3D unit_vector = ray.direction.normalized();
    double t = 0.5 * (unit_vector.y + 1);

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