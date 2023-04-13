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

    scene.add(std::make_shared<Plane>(Point{0.0, -0.5, 0.0}, Vector<3>{0.0, -0.5, 0.0}, chess));

    scene.add(std::make_shared<Sphere>(Point{0.0, 1.5,  1.5}, 1.0, light));

/*
    scene.add(std::make_shared<Sphere>(Point{ 0.0,  0.0, -1.0},   0.5, turquoise));
    scene.add(std::make_shared<Sphere>(Point{ 1.0,  0.0, -1.0},   0.5,    mirror));
    scene.add(std::make_shared<Sphere>(Point{-1.0,  0.0, -1.0},   0.5,     glass));
    scene.add(std::make_shared<Sphere>(Point{-1.0,  0.0, -1.0}, -0.45,     glass));
*/
    const std::vector<Point> vertices{Point{ 0.25,  0.1,  0.0},
                                      Point{-0.25,  0.1,  0.0},
                                      Point{  0.0, 0.35,  0.0},
                                      Point{  0.4,  0.5, 0.25}};

    const std::vector<std::array<size_t, 3>> indices{{0, 1, 2},
                                                     {1, 2, 3}};

    const std::vector<Vector<3>> triangle_normals{Vector<3>{ 0.0,    0.0,  1.0},
                                                  Vector<3>{-0.41, -0.42, 0.42}};

    scene.add(std::make_shared<Mesh>(vertices, indices, triangle_normals, crimson));

    //camera.move(-4.0, 0.0, -3.0);
    //camera.h_tilt(-70);

    //camera.move(0.0, 0.0, 7.0);

    renderer.render(camera, background, scene);
}