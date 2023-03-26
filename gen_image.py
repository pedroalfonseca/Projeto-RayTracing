from os import system
from PIL import Image

CC = "g++"
CFLAGS = "-std=c++17 -Wall -Wextra -Wshadow -fsanitize=address,undefined -O2"
TARGET = "./src/main.cpp"


def main():
    print(f"Compiling '{TARGET}' with C++17...")
    system(f"{CC} {CFLAGS} {TARGET}")
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
