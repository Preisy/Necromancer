#include <iostream>
#include <SFML/Graphics.hpp>
//#include "utils/DependencyInjection.h"
//#include "game/RenderWindowDI.h"

using namespace sf;

#include "utils/animation/AnimationManager.h"

int main() {
    RenderWindow window(VideoMode(640, 480), "Lesson 22. kychka-pc.ru");
//    RenderWindow window(sf::VideoMode(30*32, 25 * 32), "Necromancer");
//    RenderWindow window(sf::VideoMode::getDesktopMode(), "Necromancer");
//    view.reset(FloatRect(0, 0, 640, 480));
    window.setSize(sf::Vector2u(30*32, 25*32));
    window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - 30*32 / 2,
                                    sf::VideoMode::getDesktopMode().height / 2 - 25*32 / 2));

    AnimationManager anim;
    anim.loadFromXML(R"(D:\C\3sem_cpp\informatics\lab4\resources\units\player_walking.xml)", R"(D:\C\3sem_cpp\informatics\lab4\resources\units\player_walking.png)");

    Clock clock;

    anim.set("walk_s");

//    anim.play();
    anim.setPosition(200, 200);
    sf::RectangleShape r;
    r.setSize({20, 20});
    r.setFillColor(sf::Color::Blue);
    r.setPosition(200, 20);

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 700;

        sf::Event event;
        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                }
            }
        }


        anim.tick(time);

        window.clear();

        anim.draw(window);

        window.draw(r);


        window.display();
    }

    return 0;
}