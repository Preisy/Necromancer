#pragma once

#include <SFML/Graphics.hpp>

class InteractiveGameObject {
public:
    virtual sf::FloatRect getFloatRect() = 0;

    virtual void setOffset(float x, float y) = 0;

    virtual const std::unique_ptr<sf::Sprite> & getSprite() = 0;

    virtual ~InteractiveGameObject() = default;
};
