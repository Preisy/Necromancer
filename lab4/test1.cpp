#include <iostream>
#include <SFML/Graphics.hpp>
//#include "utils/DependencyInjection.h"
//#include "game/RenderWindowDI.h"

using namespace sf;

#include "utils/animation/AnimationManager.h"
#include "presentation/model/PlayerModel.h"
#include "presentation/view/UnitView.h"
#include "presentation/RenderWindowDI.h"

int main() {
    Injected<sf::RenderWindow> window;
//    RenderWindow window(VideoMode(640, 480), "Lesson 22. kychka-pc.ru");
    window->setSize(sf::Vector2u(30*32, 25*32));
    window->setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - 30*32 / 2,
                                    sf::VideoMode::getDesktopMode().height / 2 - 25*32 / 2));


    Clock clock;

    auto playerModel = std::make_shared<PlayerModel>();
    playerModel->setCoords({200, 200});
    UnitView unitView;

    while (window->isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 700;

        sf::Event event;
        while(window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                }
            }
        }

        playerModel->update(time);
//        anim.tick(time);

        window->clear();

        unitView.draw(playerModel);
//        anim.draw(window);


        window->display();
    }

    return 0;
}