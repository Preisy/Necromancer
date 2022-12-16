#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "UnitModel.h"
#include "presentation/model/bullet/FireballSpell.h"
#include "presentation/model/FieldModel.h"
#include "utils/animation/AnimationManager.h"
#include "utils/StaticDots.h"

class PlayerModel : public UnitModel {
    float dx = 0;
    float dy = 0;
    sf::Vector2f size = {32, 64};
    sf::Vector2f coords = {0, 0};
    sf::Vector2f offset = {0, 0};
    std::shared_ptr<FieldModel> fieldModel = nullptr;
    float direction = -M_PI_2;
    std::unique_ptr<AnimationManager> animationManager = std::make_unique<AnimationManager>();

public:
    explicit PlayerModel() {
        animationManager->loadFromXML(R"(D:\C\3sem_cpp\informatics\lab4\resources\units\player_walking.xml)",
                                     R"(D:\C\3sem_cpp\informatics\lab4\resources\units\player_walking.png)");
        animationManager->set("walk_w");
        animationManager->play();
    }

    void setField(const std::shared_ptr<FieldModel> & fieldModel) {
        coords = fieldModel->getPlayerCoords();
        this->fieldModel = fieldModel;
        animationManager->setPosition(coords.x, coords.y + size.y);
    }

    sf::Vector2f sizeReduction = {5, 48};
    sf::FloatRect getFloatRect() {
        return {coords.x + sizeReduction.x, coords.y + sizeReduction.y, size.x - sizeReduction.x, size.y - sizeReduction.y};
    }

public:
    void collision(int dir, std::string && objectsName) {
        auto rect = getFloatRect();
        auto objects = fieldModel->getLevel().GetObjects(objectsName);
        for (const auto & object: objects) {
            if (!rect.intersects(object.rect)) continue;

            if (dy < 0) {
                int a = 0;
            }
            if (dir == 0 && dx > 0
                && rect.left < object.rect.left
                && rect.left + rect.width > object.rect.left
            ) {
                coords.x = object.rect.left - size.x;
                break;
            } else if (dir == 0 && dx < 0
               && rect.left < object.rect.left + object.rect.width
               && rect.left + rect.width > object.rect.left
            ) {
                coords.x = object.rect.left + object.rect.width - 5;
                break;
            } else if (dir == 1 && dy > 0
                && rect.top < object.rect.top
                && rect.top + rect.height > object.rect.top
                    ) {
                coords.y = object.rect.top - size.y;
                break;
            } else if (dir == 1 && dy < 0
                       && rect.top < object.rect.top + object.rect.height
                       && rect.top + rect.height > object.rect.top
                    ) {
                coords.y = object.rect.top + object.rect.height - sizeReduction.y;
                break;
            }
        }
    }
    void collisionX() {
        collision(0, "solid");
        collision(0, "sea");
    }

    void collisionY() {
        collision(1, "solid");
        collision(1, "sea");
    }

    void update(float time) override {
        coords.x += dx * time;
        collisionX();
        coords.y += dy * time;
        collisionY();
        if (dx > 0) {
            animationManager->set("walk_d");
        } else if (dx < 0) {
            animationManager->set("walk_a");
        } else if (dy > 0) {
            animationManager->set("walk_s");
        } else if (dy < 0) {
            animationManager->set("walk_w");
        } else {
            if (direction > -M_PI_4 && direction < M_PI_4) {
                animationManager->set("stay_d");
            } else if (direction < -M_PI_4 && direction > -3*M_PI_4 ) {
                animationManager->set("stay_s");
            } else if (direction > M_PI_4 && direction < 3*M_PI_4 ) {
                animationManager->set("stay_w");
            } else if (direction > 3*M_PI_4 || direction < -3*M_PI_4 ) {
                animationManager->set("stay_a");
            }
        }
    }

    void setOffset(float x, float y) override {
        this->offset.x = x;
        this->offset.y = y;
        animationManager->setPosition(coords.x - offset.x, coords.y - offset.y + size.y);
    }

    void fire() {
        auto fireball = std::make_shared<FireballSpell>(
                direction,
                fieldModel,
                sf::Vector2f(coords.x, coords.y + size.y / 2)
        );
        fireball->fire();
    }

    void takeDamage(float damage) override {

    }

    void setDirection(sf::Vector2i mousePos) {
        auto relativePlayerCoords = animationManager->getPosition();
        direction = 0 - (float) atan2((mousePos.y - relativePlayerCoords.y + size.y / 2), (mousePos.x - relativePlayerCoords.x - size.x / 2));
        StaticDots::setPos("mouse", mousePos.x, mousePos.y);
    }



    [[nodiscard]]
    const sf::Vector2f & getSize() const {
        return size;
    }

    const std::unique_ptr<AnimationManager> & getAnimationManager() override {
        return animationManager;
    }

    [[nodiscard]]
    float getDx() const {
        return dx;
    }

    void setDx(float dx) {
        PlayerModel::dx = dx;
    }

    [[nodiscard]]
    float getDy() const {
        return dy;
    }

    void setDy(float dy) {
        PlayerModel::dy = dy;
    }

    [[nodiscard]]
    const sf::Vector2f & getCoords() const {
        return coords;
    }

    void setCoords(const sf::Vector2f & coords) {
        PlayerModel::coords = coords;
    }
};
