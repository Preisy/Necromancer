#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "RenderWindowDI.h"

#include "utils/DependencyInjection.h"
#include "utils/activity/ActivityManager.h"
#include "config.h"
#include "presentation/view/LevelActivity.h"
#include "data/Repository.h"

class Game {
    Injected<sf::RenderWindow> window;
    Injected<ActivityManager> activityManager;
    Repository<PlayerModel> playerRepository;

public:
    Game() {
        window->setSize(sf::Vector2u(30*fieldCellSize, 25*fieldCellSize));
        window->setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - 30*32 / 2,
                                        sf::VideoMode::getDesktopMode().height / 2 - 25*32 / 2));

        playerRepository.insert(1, PlayerModel());

        configureInjecting<FieldController>(1);

        activityManager->push(std::make_unique<LevelActivity>());
    }

    void handleEvent(sf::Event& event) {
        activityManager->top()->handleEvent(event);
    }

    void handleState() {
        activityManager->top()->handleState();
    }

    void update(float time) {
        activityManager->top()->update(time);
    }

    void draw() {
        activityManager->top()->draw();
    }

    void run() {
        sf::Clock clock;
        while(window->isOpen()) {
            float time = clock.getElapsedTime().asMicroseconds();
            clock.restart();
            time = time / 500;

            sf::Event event;
            while(window->pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window->close();

                handleEvent(event);
            }

            handleState();

            update(time);

            window->clear();

            draw();

            window->display();
        }
    }
};