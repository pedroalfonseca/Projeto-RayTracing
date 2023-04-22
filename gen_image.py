from sys import argv, exit
from os import system
from PIL import Image

CC = "g++"
s_CFLAGS = "-std=c++17 -Wall -Wextra -Wshadow -fsanitize=address,undefined"
f_CFLAGS = "-std=c++17 -Ofast"
TARGET = "./src/main.cpp"


def wrong_usage():
    exit(
        "\033[93mUsage:\033[0m python3 gen_image.py <compilation option> <scene option>\n\n"
        "\033[93mCompilation option:\033[0m\n"
        "\033[95m[SAFE]\033[0m -s\n"
        "\033[95m[FAST]\033[0m -f\n\n"
        "\033[93mScene option:\033[0m\n"
        "\033[95m[SAMPLE]\033[0m -s\n"
        "\033[95m[DREAMY]\033[0m -d\n"
        "\033[95m[CUSTOM]\033[0m -c\n"
    )


def main():
    if len(argv) != 3:
        wrong_usage()

    compilation_option = argv[1]
    if compilation_option != "-s" and compilation_option != "-f":
        wrong_usage()

    scene_option = argv[2]
    if scene_option != "-s" and scene_option != "-d" and scene_option != "-c":
        wrong_usage()

    print(f"Compiling '{TARGET}' with C++17...")
    system(f"{CC} {s_CFLAGS if compilation_option == '-s' else f_CFLAGS} {TARGET}")
    print("Done.\n")

    if scene_option == "-c":
        print(
            "\033[93mNote:\033[0m The camera is initially positioned at (0.0, 0.0, 4.0) and points at (0.0, 0.0, -1.0)."
            "\n      If you are unsure about the coordinate system, see './img/cam_basis'.\n"
        )

    print("Rendering image...")
    system(
        f"./a.out {f'{scene_option} < in.txt' if scene_option == '-c' else scene_option} > ./img/image.ppm"
    )
    print("Done.\n")

    print("Generating PNG file...")
    image = Image.open("./img/image.ppm")
    image.save("./img/image.png")
    print("Done.\n")

    print("Cleaning up residual files...")
    system("rm a.out && rm ./img/image.ppm")
    print("Done.")


if __name__ == "__main__":
    main()
