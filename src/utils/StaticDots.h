#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

class StaticDots {
    using map = std::unordered_map<std::string, sf::CircleShape>;
    static inline map* dots = nullptr;

    static map* inst() {
        if (dots == nullptr) dots = new map();
        return dots;
    }

public:
    static void push(const std::string & name, float x, float y) {
        sf::CircleShape circleShape;
        circleShape.setFillColor(sf::Color::Red);
        circleShape.setRadius(2);
        circleShape.setPosition(x, y);
        inst()->insert({name, circleShape});
    }
    static void setPos(const std::string & name, float x, float y) {
        if (inst()->find(name) == inst()->end()) {
            push(name, x, y);
        }
        inst()->operator[](name).setPosition(x, y);
    }

    static void setPos(const std::string & name, float x, float y, sf::Color color) {
        if (inst()->find(name) == inst()->end()) {
            push(name, x, y);
        }
        inst()->operator[](name).setPosition(x, y);
        inst()->operator[](name).setFillColor(color);
    }
    static auto getAll() {
        return *inst();
    }
};