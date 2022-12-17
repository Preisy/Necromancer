#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "UnitModel.h"

#include "utils/animation/AnimationManager.h"
#include "utils/StaticDots.h"
#include "presentation/model/FieldModel.h"
#include "presentation/model/bullet/FireballSpell.h"

class HumanModel : public UnitModel, public std::enable_shared_from_this<HumanModel> {
    std::unique_ptr<AnimationManager> animationManager = std::make_unique<AnimationManager>();
    std::unique_ptr<AnimationManager> fallAnimationManager = std::make_unique<AnimationManager>();
    std::shared_ptr<FieldModel> fieldModel;
    std::list<std::shared_ptr<UnitModel>>::iterator fieldPos;

    float health = 100;
    CharacterFaction faction = CharacterFaction::Human;
    float damagedTime = 0;
    bool isDamaged = false;
    float speed = 0.02;
    float fireInterval = 2000;
    float timeToShot = fireInterval;

public:
    HumanModel(
            sf::Vector2f start,
            const std::shared_ptr<FieldModel> & fieldModel
    ) : fieldModel(fieldModel) {
        size = {32, 50};
        sizeReduction = {5, 20};
        coords = start;

        animationManager->loadFromXML(R"(D:\C\3sem_cpp\informatics\lab4\resources\units\human.xml)",
                                      R"(D:\C\3sem_cpp\informatics\lab4\resources\units\human.png)");
        animationManager->set("stay_s");
        animationManager->play();
    }

    void addToField() override {
        fieldPos = fieldModel->addUnit(shared_from_this());
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

        auto playerCoords = getPlayerCoords();
        float r = sqrt(
                pow(playerCoords.left + playerCoords.width / 2 - coords.x, 2) +
                pow(playerCoords.top + playerCoords.height / 2 - coords.y, 2)
        );

        if (r >= 400) {
            animationManager->set("stay_s");
            return;
        }

        fire(time, playerCoords);

        if (r <= 200) {
            animationManager->set("stay_s");
            return;
        }

        move(time, playerCoords);
    }

    sf::FloatRect getPlayerCoords() {
        for (const auto & unit: fieldModel->getUnitModels()) {
            if (std::dynamic_pointer_cast<PlayerModel>(unit) != nullptr) {
                return unit->getFloatRect();
            }
        }
        throw std::runtime_error("player not found while HumanModel::update()");
    };

private:
    void fire(float time, sf::FloatRect playerCoords) {
        timeToShot -= time;
        if (timeToShot > 0) return;
        timeToShot = fireInterval;

        auto fireball = std::make_shared<FireballSpell>(
                -atan2((playerCoords.top - coords.y), (playerCoords.left - coords.x)),
                fieldModel,
                sf::Vector2f(coords.x, coords.y + size.y / 2),
                faction
        );
        fireball->fire();
    }

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

    void move(float time, const sf::FloatRect & playerCoords) {
        float angleCos;
        float angleSin;
        if (playerCoords.left - coords.x == 0) {
            angleCos = abs(playerCoords.top - coords.y) / (playerCoords.top - coords.y) * M_PI_2;
            angleSin = 1;
        } else {
            float atan = -atan2((playerCoords.top - coords.y), (playerCoords.left - coords.x));
            if (atan > 0) {
                angleCos = cos(atan);
                angleSin = -sqrt(1 - angleCos * angleCos);
            } else {
                angleCos = cos(atan);
                angleSin = sqrt(1 - angleCos * angleCos);
            }
        }
        dx = speed * angleCos;
        dy = speed * angleSin;
        coords.x += dx * time;
        collisionX();
        coords.y += dy * time;
        collisionY();

        if (abs(dx) > abs(dy)) {
            if (dx < 0) {
                animationManager->set("walk_a");
            } else {
                animationManager->set("walk_d");
            }
        } else {
            if (dy < 0) {
                animationManager->set("walk_w");
            } else {
                animationManager->set("walk_s");
            }
        }

    }

public:

    void setOffset(float x, float y) override {
        this->offset.x = x;
        this->offset.y = y;
        animationManager->setPosition(coords.x - offset.x, coords.y - offset.y + size.y);
    }

    void takeDamage(float damage) override {
        health -= damage;
        if (health <= 0) {
            fieldModel->addDeadUnit(shared_from_this());
            fieldModel->eraseUnit(fieldPos);
            animationManager->set("fall_down");
            animationManager->play();
            animationManager->loop(false);
            animationManager->setPosition(
                    animationManager->getPosition().x,
                    animationManager->getPosition().y
            );
        } else {
            isDamaged = true;
            damagedTime = 500;
            animationManager->animList[animationManager->currentAnim].sprite.setColor(sf::Color(0xff3c3cff));
        }
    }

    const std::unique_ptr<AnimationManager> & getAnimationManager() override {
        return animationManager;
    }

    sf::FloatRect getFloatRect() override {
        return {coords.x, coords.y, size.x, size.y};
    }

    CharacterFaction getCharacterFaction() override {
        return faction;
    }
};