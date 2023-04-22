#include "entities/material_utils.hpp"
#include "misc/Renderer.hpp"
#include "misc/Scene.hpp"

int
main(int   argc,
     char *argv[])
{
    if (argc != 2)
        exit(1);

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    constexpr size_t samples_per_pixel = 100;
    constexpr size_t max_depth         = 50;

    constexpr size_t img_width  = 400;
    constexpr size_t img_height = 225;

    const Point look_from{0.0, 0.0,  4.0};
    const Point look_at  {0.0, 0.0, -1.0};

    Camera camera;

    Color background;

    Scene scene;

    char scene_option = argv[1][1];
    switch (scene_option) {
    case 's':
        {
            camera = {look_from, look_at, {0.0, 1.0, 0.0}, 20.0, (static_cast<double>(img_width) / img_height)};

            background = {0.5, 0.7, 1.0};

            scene.add_entity(std::make_shared<Plane>(Point{0.0, -0.5, 0.0}, Vector<3>{0.0, -0.5, 0.0}, olive));

            scene.add_entity(std::make_shared<Sphere>(Point{ 0.0, 1.5,  1.5},   1.0,  light));
            scene.add_entity(std::make_shared<Sphere>(Point{ 0.0, 0.0, -1.0},   0.5,   gold));
            scene.add_entity(std::make_shared<Sphere>(Point{ 1.0, 0.0, -1.0},   0.5, mirror));
            scene.add_entity(std::make_shared<Sphere>(Point{-1.0, 0.0, -1.0},   0.5,  glass));
            scene.add_entity(std::make_shared<Sphere>(Point{-1.0, 0.0, -1.0}, -0.45,  glass));

            const std::vector<Point> vertices{Point{ 0.25,  0.1,  0.0},
                                              Point{-0.25,  0.1,  0.0},
                                              Point{  0.0, 0.35,  0.0},
                                              Point{  0.4,  0.5, 0.25}};

            const std::vector<std::array<size_t, 3>> indices{{0, 1, 2},
                                                             {1, 2, 3}};

            scene.add_entity(std::make_shared<Mesh>(vertices, indices, crimson));

            // Movimentação das entidades

            // Esfera
            //scene[2]->move( 1.0, 1.0, -2.0);

            // Malha
            //scene[6]->move(-1.0, 0.0,  0.0);
            //scene[6]->move( 0.0, 0.0, -5.0);

            // Toda a cena (aproximação)
            //scene.move(0.0,  0.0,  2.0);
            //camera.v_tilt(10);

            // Toda a cena (afastamento)
            //scene.move(0.0, 0.45, -3.0);

            break;
        }
    case 'd':
        {
            camera = {look_from, look_at, {0.0, 1.0, 0.0}, 20.0, ((double)img_width) / img_height};

            background = {1.0, 0.44, 0.8};

            scene.add_entity(std::make_shared<Plane>(Point{0.0, -0.5, 0.0}, Vector<3>{0.0, -0.5, 0.0}, chess));

            scene.add_entity(std::make_shared<Sphere>(Point{ 0.0, 1.5,  1.5},   1.0,     light));
            scene.add_entity(std::make_shared<Sphere>(Point{ 0.0, 0.0, -1.0},   0.5, turquoise));
            scene.add_entity(std::make_shared<Sphere>(Point{ 1.0, 0.0, -1.0},   0.5,    mirror));
            scene.add_entity(std::make_shared<Sphere>(Point{-1.0, 0.0, -1.0},   0.5,     glass));
            scene.add_entity(std::make_shared<Sphere>(Point{-1.0, 0.0, -1.0}, -0.45,     glass));

/*
            const std::vector<Point> vertices{Point{0.5, -0.5, -1.5},
                                              Point{1.5, -0.5, -1.5},
                                              Point{1.0, -0.5, -0.5},
                                              Point{1.0,  0.5, -1.0}};

            const std::vector<std::array<size_t, 3>> indices{{0, 1, 2},
                                                             {0, 1, 3},
                                                             {0, 2, 3},
                                                             {1, 2, 3}};

            scene.add(std::make_shared<Mesh>(vertices, indices, crimson));
*/

            break;
        }
    case 'c':
        {
            char id;
            while (std::cin >> id) {
                if (id == 's') {
                    double cx, cy, cz;
                    double Or, Og, Ob;
                    double ks, ka, kr, kt;
                    double p;

                    std::cin >> cx >> cy >> cz
                             >> Or >> Og >> Ob
                             >> ks >> ka >> kr >> kt
                             >> p;

                    
                } else if (id == 'p') {
                    double px, py, pz;
                    double vx, vy, vz;
                    double Or, Og, Ob;
                    double ks, ka, kr, kt;
                    double p;

                    std::cin >> px >> py >> pz
                             >> vx >> vy >> vz
                             >> Or >> Og >> Ob
                             >> ks >> ka >> kr >> kt
                             >> p;

                    
                } else if (id == 't') {
                    size_t nt, nv;

                    std::cin >> nt >> nv;

                    std::vector<Point> vertices;
                    while (nv--) {
                        double px, py, pz;

                        std::cin >> px >> py >> pz;

                        vertices.push_back({px, py, pz});
                    }

                    std::vector<std::array<size_t, 3>> indices;
                    while (nt--) {
                        size_t ta, tb, tc;

                        std::cin >> ta >> tb >> tc;

                        indices.push_back({ta, tb, tc});
                    }

                    
                } else if (id == 'l') {
                    double lx, ly, lz;

                    std::cin >> lx >> ly >> lz;


                } else if (id == 'a') {
                    double Ix, Iy, Iz;

                    std::cin >> Ix >> Iy >> Iz;

                    background = {Ix, Iy, Iz};
                } else
                    exit(1);
            }

            break;
        }
    default:
        exit(1);
    }

    // Movimentação da câmera

    // Visão do lado esquerdo
    //camera.move(-4.0, 0.0, -3.0);
    //camera.h_tilt(-70);

    // Visão do lado direito
    //camera.move(4.0, 0.0, -3.0);
    //camera.h_tilt(70);

    // Visão de cima
    //camera.move(0.0, 15.0, -3.5);
    //camera.v_tilt(-90);

    // Visão afastado
    //camera.move(0.0, 0.0, 7.0);

    Renderer renderer{img_width, img_height, samples_per_pixel, max_depth};
    renderer.render(camera, background, scene);
}