#include <iostream>
#include <SFML/Graphics.hpp>
//#include "utils/DependencyInjection.h"
//#include "game/RenderWindowDI.h"

using namespace sf;

int main() {
    for (int direction = 16; direction >= 5; --direction) {
        std::cout << '\r' << direction << " " << direction * 50;
    }

    return 0;
}