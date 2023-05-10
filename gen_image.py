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


def ppm_to_png(input_file, output_file):
    with open(input_file, "rb") as f:
        data = f.read().decode("utf-8")
        data = data.strip().split("\n")

        if data[0] != "P3":
            exit("\033[93mError:\033[0m Input file is not a PPM file.")

        width, height = map(int, data[1].split())
        image = Image.new("RGB", (width, height))

        pixel_data = [int(i) for i in " ".join(data[3:]).split()]
        pixel_tuples = [
            (pixel_data[i], pixel_data[i + 1], pixel_data[i + 2]) for i in range(0, len(pixel_data), 3)
        ]

        image.putdata(pixel_tuples)
        image.save(output_file, "PNG")


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
            "\033[93mNote:\033[0m If you are unsure about the coordinate system, see './img/cam_basis.png'.\n"
        )

    print("Rendering image...")
    system(
        f"./a.out {f'{scene_option} < in.txt' if scene_option == '-c' else scene_option} > ./img/image.ppm"
    )
    print("Done.\n")

    print("Generating PNG file...")
    ppm_to_png("./img/image.ppm", "./img/image.png")
    print("Done.\n")

    print("Cleaning up residual files...")
    system("rm a.out && rm ./img/image.ppm")
    print("Done.\n")

    print("\033[93mNote:\033[0m The generated image is located in the './img' folder.")


if __name__ == "__main__":
    main()
