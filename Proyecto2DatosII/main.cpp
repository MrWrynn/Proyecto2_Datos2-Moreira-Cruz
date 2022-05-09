#include <iostream>
#include "image.hpp"
int main() {
    image image;
    image.read("snail.bmp");
    image.negative();
    image.write("copia.bmp");
    image.clear();
    return 0;
}
