#pragma once

#include <SFML/Graphics.hpp>
#include "RenderWindowDI.h"
#include "model/ObjectModel.h"
#include "model/interactiveGameObject/InteractiveGameObject.h"

class ObjectView {
    Injected<sf::RenderWindow> window;

public:
    void draw(const std::shared_ptr<ObjectModel> & unitEntity, float time) {
        unitEntity->getAnimationManager()->tick(time);
        unitEntity->getAnimationManager()->draw(*window);
    }

    void draw(const std::shared_ptr<InteractiveGameObject> & interactiveGameObject, float time) {
        window->draw(*interactiveGameObject->getSprite());
    }
};

