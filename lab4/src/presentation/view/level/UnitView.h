#pragma once

#include <SFML/Graphics.hpp>
#include "presentation/RenderWindowDI.h"
#include "presentation/model/PlayerModel.h"

class UnitView {
    Injected<sf::RenderWindow> window;

public:
    void draw(const std::shared_ptr<UnitModel> & unitEntity, float time) {
//        std::cout << unitEntity->getAnimationManager().animList[unitEntity->getAnimationManager().currentAnim].currentFrame << std::endl;
//        unitEntity->getAnimationManager().animList[unitEntity->getAnimationManager().currentAnim].sprite.setPosition(200,200);
        unitEntity->getAnimationManager()->tick(time);

        unitEntity->getAnimationManager()->draw(*window);
    }
};

