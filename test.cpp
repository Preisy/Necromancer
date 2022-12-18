#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

#include "model/interactiveGameObject/HealthPotion.h"

int main() {
    RenderWindow window(VideoMode(640, 480), "Lesson 22. kychka-pc.ru");

    auto healthPotion = HealthPotion({10, 10}, HealthPotion::Level::Junior);
    Texture t;
    t.loadFromFile(R"(D:\C\3sem_cpp\Necromancer\resources\interactiveGameObjects\healthPotion\health_potion_junior.png)");
    Sprite sprite;
    sprite.setTexture(t);
    sprite.setPosition(50, 50);



    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                }
            }
        }
        window.clear();

        window.draw(*healthPotion.getSprite());
        window.draw(sprite);

        window.display();
    }

    return 0;
}