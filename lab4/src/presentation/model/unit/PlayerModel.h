#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "UnitModel.h"
#include "presentation/model/bullet/FireballSpell.h"
#include "presentation/model/FieldModel.h"
#include "utils/animation/AnimationManager.h"
#include "utils/StaticDots.h"

class PlayerModel : public UnitModel, public std::enable_shared_from_this<PlayerModel> {
    std::shared_ptr<FieldModel> fieldModel = nullptr;
    float direction = -M_PI_2;
    std::unique_ptr<AnimationManager> animationManager = nullptr;

    float health = 1500;
    CharacterFaction faction = CharacterFaction::Player;
    float damagedTime = 0;
    bool isDamaged = false;

public:
    explicit PlayerModel() {
        size = {32, 64};
        sizeReduction = {5, 48};

        animationManager = std::make_unique<AnimationManager>();
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

    sf::FloatRect getFloatRect() override {
        return {coords.x, coords.y, size.x, size.y};
//        return {coords.x + sizeReduction.x, coords.y + sizeReduction.y, size.x - sizeReduction.x, size.y - sizeReduction.y};
    }

public:

    void collisionX() {
        collision(0, fieldModel->getLevel().GetObjects("solid"));
        collision(0, fieldModel->getLevel().GetObjects("sea"));
        collision(0, fieldModel->getUnitModels());
    }

    void collisionY() {
        collision(1, fieldModel->getLevel().GetObjects("solid"));
        collision(1, fieldModel->getLevel().GetObjects("sea"));
        collision(1, fieldModel->getUnitModels());
    }
    float ifOnPath() {
        auto unitRect = getFloatRect();
        auto rect = sf::FloatRect(
                unitRect.left + sizeReduction.x,
                unitRect.top + sizeReduction.y,
                unitRect.width - sizeReduction.x,
                unitRect.height - sizeReduction.y
        );
        for (const auto & path: fieldModel->getLevel().GetObjects("path")) {
            if (path.rect.intersects(rect)) {
                animationManager->speedK = 1.35;
                return 1.35;
            }
        }
        animationManager->speedK = 1;
        return 1;
    }

    void update(float time) override {
        if (isDamaged) {
            damagedTime -= time;
            if (damagedTime < 0) {
                animationManager->animList[animationManager->currentAnim].sprite.setColor(sf::Color::White);
                isDamaged = false;
            }
        } else {
            animationManager->animList[animationManager->currentAnim].sprite.setColor(sf::Color::White);
        }

        float k = ifOnPath();
        coords.x += dx * time * k;
        collisionX();
        coords.y += dy * time * k;
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
                sf::Vector2f(coords.x, coords.y + size.y / 2),
                faction
        );
        fireball->fire();
    }

    void takeDamage(float damage) override {
        health -= damage;
        if (health < 0) {

        } else {
            isDamaged = true;
            damagedTime = 500;
            animationManager->animList[animationManager->currentAnim].sprite.setColor(sf::Color(0xff3c3cff));
        }
    }

    void addToField() override {

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

    CharacterFaction getCharacterFaction() override {
        return faction;
    }
};
