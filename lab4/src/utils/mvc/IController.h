#pragma once

#include <SFML/Graphics.hpp>

class IController {
public:
    virtual void update(float time) = 0;

    virtual void handleEvent(sf::Event&) = 0;

//    virtual std::unique_ptr<IView> getFieldView() = 0;

    virtual ~IController() = default;
};
