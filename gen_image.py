from sys import argv, exit
from os import system
from PIL import Image

CC = "g++"
s_CFLAGS = "-std=c++17 -Wall -Wextra -Wshadow -fsanitize=address,undefined"
f_CFLAGS = "-std=c++17 -Ofast"
TARGET = "./src/main.cpp"

def wrong_usage():
    exit(
        "\033[93mUsage:\033[0m\n"
        "\033[95m[SAFE]\033[0m python3 gen_image.py -s\n"
        "\033[95m[FAST]\033[0m python3 gen_image.py -f\n"
    )

def main():
    if len(argv) != 2:
        wrong_usage()

    compilation_mode = argv[1]

    if compilation_mode != "-s" and compilation_mode != "-f":
        wrong_usage()

    print(f"Compiling '{TARGET}' with C++17...")
    system(f"{CC} {s_CFLAGS if compilation_mode == '-s' else f_CFLAGS} {TARGET}")
    print("Done.\n")

    print("Rendering image...")
    system("./a.out > image.ppm")
    print("Done.\n")

    print("Generating PNG file...")
    img = Image.open("./image.ppm")
    img.save("./image.png")
    print("Done.\n")

    print("Cleaning up residual files...")
    system("rm a.out && rm image.ppm")
    print("Done.")


if __name__ == "__main__":
    main()
