#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "RenderWindowDI.h"

#include "utils/DependencyInjection.h"
#include "utils/activity/ActivityManager.h"
#include "presentation/view/LevelActivity.h"

class Game {
    Injected<sf::RenderWindow> window;
    Injected<ActivityManager> activityManager;

public:
    Game() {
//        configureInjecting<LevelController>(1);
//        LevelController().getView(1);
        activityManager->push(std::make_unique<LevelActivity>());
//        view = activityManager->top()->getView(1);
    }

    void handleEvent(sf::Event& event) {
        activityManager->top()->handleEvent(event);
    }

    void update(float time) {
        activityManager->top()->update(time);
    }

    void draw(float time) {
        activityManager->top()->draw(time);
    }

    void run() {
        sf::Clock clock;
        while(window->isOpen()) {
            float time = clock.getElapsedTime().asMicroseconds();
            time = time / 700;

            sf::Event event;
            while(window->pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window->close();

                handleEvent(event);
            }

            update(time);

            window->clear();

            draw(time);

            window->display();
        }
    }
};