#include "entities/material_utils.hpp"
#include "misc/Renderer.hpp"
#include "misc/Scene.hpp"

// Image

constexpr double aspect_ratio      = 16.0 / 9;
constexpr int    img_width         = 400;
constexpr int    img_height        = static_cast<int>(img_width / aspect_ratio);
constexpr int    samples_per_pixel = 100;
constexpr int    max_depth         = 50;

// Camera

//const Point look_from{-2.0, 2.0,  1.0};
const Point look_from{0.0, 0.0,  4.0};
const Point look_at  {0.0, 0.0, -1.0};

//alternative vfov: 90.0
Camera camera{look_from, look_at, {0.0, 1.0, 0.0}, 20.0, aspect_ratio};

// Scene

Color background{1.0, 0.44, 0.8};
Scene scene;

// Render

Renderer renderer{img_width, img_height, samples_per_pixel, max_depth};

// Main

int
main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    //camera.move(1.0, 0.0, 0.0);
    //camera.v_tilt(10);

    scene.add(std::make_shared<Plane>(Point{0.0, -0.5, 0.0}, Vector<3>{0.0, -0.5, 0.0}, chess));

    scene.add(std::make_shared<Sphere>(Point{0.0, 1.5,  1.5}, 1.0, light));

    scene.add(std::make_shared<Sphere>(Point{ 0.0,  0.0, -1.0},   0.5, turquoise));
    scene.add(std::make_shared<Sphere>(Point{ 1.0,  0.0, -1.0},   0.5,    mirror));
    scene.add(std::make_shared<Sphere>(Point{-1.0,  0.0, -1.0},   0.5,     glass));
    scene.add(std::make_shared<Sphere>(Point{-1.0,  0.0, -1.0}, -0.45,     glass));

    renderer.render(camera, background, scene);
}