#pragma once

#include "RenderWindowDI.h"
#include <functional>
#include <utility>

class ButtonView {
    Injected<sf::RenderWindow> window;
    sf::RectangleShape background;
    sf::Font font;
    sf::Text text;
    sf::FloatRect rect;
    float k = float(windowHeight) / changedWindowHeight;

    std::function<void()> callback;

public:
    explicit ButtonView(
            const std::string & str,
            std::function<void()> callbackClick,
            float y
    ) : callback(std::move(callbackClick)) {
        font.loadFromFile(R"(D:\C\3sem_cpp\Necromancer\resources\arial.ttf)");
        text = sf::Text(str, font);

        background.setFillColor(sf::Color(0x7b7b7bff));
        background.setOutlineColor(sf::Color(0x010101ff));
        background.setOutlineThickness(3);
        auto r = text.getLocalBounds();
        float textSize = r.width*k + 50;
        background.setSize({textSize, 43});

        float x = (float(windowWidth) - float(textSize)) / 2;
        background.setPosition(x - 10, y);
        text.setPosition(x, y);

        rect = {x-30 - 10, y, textSize, 43};
    };

    void handleEvent(sf::Event& event) {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                auto mouseCoords = sf::Vector2f(event.mouseButton.x*k, event.mouseButton.y*k);
                if (rect.contains(mouseCoords.x, mouseCoords.y)) {
                    callback();
//                    background.setFillColor(sf::Color(0x7b7b7b00));
                } else {
//                    background.setFillColor(sf::Color(0x7b7b7bff));
                }
            }
        }
    }

    void handleState() {
        auto mousePos = sf::Mouse::getPosition(*window);
        auto mouseCoords = sf::Vector2f(float(mousePos.x) * k, float(mousePos.y) * k);
        if (rect.contains(mouseCoords.x, mouseCoords.y)) {
            background.setFillColor(sf::Color(0x7b7b7b00));
        } else {
            background.setFillColor(sf::Color(0x7b7b7bff));
        }
    }

    void draw() {
        window->draw(background);
        window->draw(text);
    }

};