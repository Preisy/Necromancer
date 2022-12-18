#include <iostream>

int main() {
    for (int i = 0; i < 100; ++i) {
        float angle = float(std::rand() % int(3.14 * 100)) / 100;
        std::cout << angle << std::endl;
    }


    return 0;
}