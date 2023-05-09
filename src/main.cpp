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
    constexpr size_t max_depth         = 5;

    size_t img_width;
    size_t img_height;

    Point look_from;
    Point look_at;

    Camera camera;

    Color background;

    Scene scene;

    char scene_option = argv[1][1];
    switch (scene_option) {
    case 's':
        {
            img_width  = 400;
            img_height = 225;

            look_from = {0.0, 0.0,  4.0};
            look_at   = {0.0, 0.0, -1.0};

            camera = {look_from, look_at, {0.0, 1.0, 0.0}, 20.0, (static_cast<double>(img_width) / img_height)};

            background = {0.5, 0.7, 1.0};

            scene.add_light({Point{0.0, 1.5, 1.5}, Color{1.0, 1.0, 1.0}});

            scene.add_entity(std::make_shared<Plane>(Point{0.0, -0.5, 0.0}, Vector<3>{0.0, -0.5, 0.0}, olive));

            scene.add_entity(std::make_shared<Sphere>(Point{ 0.0, -0.2, -1.0}, 0.3, crimson));
            scene.add_entity(std::make_shared<Sphere>(Point{-0.6, -0.1, -1.3}, 0.4, steel));
            scene.add_entity(std::make_shared<Sphere>(Point{ 0.4, -0.3, -0.7}, 0.2, glass));

            const std::vector<Point> vertices{Point{0.3, -0.5, -1.5},
                                              Point{1.3, -0.5, -1.5},
                                              Point{0.8, -0.5, -0.5},
                                              Point{0.8,  0.5, -1.0}};

            const std::vector<std::array<size_t, 3>> indices{{0, 1, 2},
                                                             {0, 1, 3},
                                                             {0, 2, 3},
                                                             {1, 2, 3}};

            scene.add_entity(std::make_shared<Mesh>(vertices, indices, gold));

            // Plano
            //scene.get_entity(0)->move(0.0, -0.5, 0.0);

            // Esfera
            //scene.get_entity(1)->move(1.0, 1.0, -2.0);

            // Malha
            //scene.get_entity(4)->move(-0.5, 0.0, -1.0);

            // Toda a cena (aproximação)
            //scene.move(0.0, 0.0, 2.0);

            // Toda a cena (afastamento)
            //scene.move(0.0, 0.0, -2.0);

            // Toda a cena (elevação)
            //scene.move(0.0, 0.4, 0.0);

            // Toda a cena (rebaixamento)
            //scene.move(0.0, -0.4, 0.0);

            break;
        }
    case 'd':
        {
            img_width  = 400;
            img_height = 225;

            look_from = {0.0, 0.0,  4.0};
            look_at   = {0.0, 0.0, -1.0};

            camera = {look_from, look_at, {0.0, 1.0, 0.0}, 20.0, (static_cast<double>(img_width) / img_height)};

            background = {1.0, 0.44, 0.8};

            scene.add_light({Point{0.0, 1.5, 1.5}, Color{1.0, 1.0, 1.0}});

            scene.add_entity(std::make_shared<Plane>(Point{0.0, -0.5, 0.0}, Vector<3>{0.0, -0.5, 0.0}, chess));

            scene.add_entity(std::make_shared<Sphere>(Point{ 0.0, 0.0, -1.0}, 0.5, turquoise));
            scene.add_entity(std::make_shared<Sphere>(Point{ 1.0, 0.0, -1.0}, 0.5,    mirror));
            scene.add_entity(std::make_shared<Sphere>(Point{-1.0, 0.0, -1.0}, 0.5,     glass));

            const std::vector<Point> vertices1{Point{-0.75, 0.75, -1.25},
                                               Point{-0.25, 0.75, -1.25},
                                               Point{ -0.5, 0.75, -0.75},
                                               Point{ -0.5, 0.25,  -1.0}};

            const std::vector<Point> vertices2{Point{0.75, 0.75, -1.25},
                                               Point{0.25, 0.75, -1.25},
                                               Point{ 0.5, 0.75, -0.75},
                                               Point{ 0.5, 0.25,  -1.0}};

            const std::vector<std::array<size_t, 3>> indices{{0, 1, 2},
                                                             {0, 1, 3},
                                                             {0, 2, 3},
                                                             {1, 2, 3}};

            scene.add_entity(std::make_shared<Mesh>(vertices1, indices, ivory));
            scene.add_entity(std::make_shared<Mesh>(vertices2, indices,  ruby));

            break;
        }
    case 'c':
        {
            char id;
            while (std::cin >> id) {
                if (id == 's') {
                    double cx, cy, cz;
                    double r;
                    double Or, Og, Ob;
                    double ri;
                    double ka, kd, ks, kr, kt;
                    double p;

                    std::cin >> cx >> cy >> cz
                             >> r
                             >> Or >> Og >> Ob
                             >> ri
                             >> ka >> kd >> ks >> kr >> kt
                             >> p;

                    Material mat{std::make_shared<Matte>(Color{Or, Og, Ob}), ri, ka, kd, ks, kr, kt, p};

                    scene.add_entity(std::make_shared<Sphere>(Point{cx, cy, cz}, r, mat));
                } else if (id == 'p') {
                    double px, py, pz;
                    double vx, vy, vz;
                    double Or, Og, Ob;
                    double ri;
                    double ka, kd, ks, kr, kt;
                    double p;

                    std::cin >> px >> py >> pz
                             >> vx >> vy >> vz
                             >> Or >> Og >> Ob
                             >> ri
                             >> ka >> kd >> ks >> kr >> kt
                             >> p;

                    Material mat{std::make_shared<Matte>(Color{Or, Og, Ob}), ri, ka, kd, ks, kr, kt, p};

                    scene.add_entity(std::make_shared<Plane>(Point{px, py, pz}, Vector<3>{vx, vy, vz}, mat));
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

                    double Or, Og, Ob;
                    double ri;
                    double ka, kd, ks, kr, kt;
                    double p;

                    std::cin >> Or >> Og >> Ob
                             >> ri
                             >> ka >> kd >> ks >> kr >> kt
                             >> p;

                    Material mat{std::make_shared<Matte>(Color{Or, Og, Ob}), ri, ka, kd, ks, kr, kt, p};

                    scene.add_entity(std::make_shared<Mesh>(vertices, indices, mat));
                } else if (id == 'c') {
                    size_t hres, vres;
                    double vfov;
                    double upx, upy, upz;
                    double Cx,  Cy,  Cz;
                    double Mx,  My,  Mz;

                    std::cin >> hres >> vres
                             >> vfov
                             >> upx >> upy >> upz
                             >> Cx  >> Cy  >> Cz
                             >> Mx  >> My  >> Mz;

                    img_width  = hres;
                    img_height = vres;

                    Vector<3> up{upx, upy, upz};

                    look_from = {Cx, Cy, Cz};
                    look_at   = {Mx, My, Mz};

                    camera = {look_from, look_at, up, vfov, (static_cast<double>(img_width) / img_height)};
                } else if (id == 'l') {
                    double lx, ly, lz;
                    double Ir, Ig, Ib;

                    std::cin >> lx >> ly >> lz
                             >> Ir >> Ig >> Ib;

                    scene.add_light({Point{lx, ly, lz}, Color{Ir, Ig, Ib}});
                } else if (id == 'a') {
                    double Ir, Ig, Ib;

                    std::cin >> Ir >> Ig >> Ib;

                    background = {Ir, Ig, Ib};
                } else
                    exit(1);
            }

            break;
        }
    default:
        exit(1);
    }

    // Visão do lado esquerdo 1
    //camera.move(-4.0, 0.0, -3.0);
    //camera.h_tilt(-60);

    // Visão do lado esquerdo 2
    //camera.move(-4.0, 0.0, -5.0);
    //camera.h_tilt(-90);

    // Visão do lado esquerdo 3
    //camera.move(-4.0, 0.0, -7.0);
    //camera.h_tilt(-120);

    // Visão do lado direito 1
    //camera.move(4.0, 0.0, -3.0);
    //camera.h_tilt(60);

    // Visão do lado direito 2
    //camera.move(4.0, 0.0, -5.0);
    //camera.h_tilt(90);

    // Visão do lado direito 3
    //camera.move(4.0, 0.0, -7.0);
    //camera.h_tilt(120);

    // Visão de cima
    //camera.move(0.0, 8.0, -5.0);
    //camera.v_tilt(-90);

    // Visão afastado
    //camera.move(0.0, 0.0, 7.0);

    Renderer renderer{img_width, img_height, samples_per_pixel, max_depth};
    renderer.render(camera, background, scene);
}
