#pragma once

#include <SFML/Graphics.hpp>

class Activity {
public:
    virtual void handleState() = 0;

    virtual void handleEvent(sf::Event& event) = 0;

    virtual void update(float time) = 0;

    virtual void draw() = 0;

    virtual ~Activity() = default;
};