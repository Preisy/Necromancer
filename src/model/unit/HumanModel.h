#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "UnitModel.h"

#include "utils/animation/AnimationManager.h"
#include "utils/StaticDots.h"
#include "model/FieldModel.h"
#include "model/bullet/FireballSpell.h"
#include "model/interactiveGameObject/HealthPotion.h"
#include "model/interactiveGameObject/ManaPotion.h"

class HumanModel : public UnitModel, public std::enable_shared_from_this<HumanModel> {
    std::unique_ptr<AnimationManager> animationManager = std::make_unique<AnimationManager>();
    std::unique_ptr<AnimationManager> fallAnimationManager = std::make_unique<AnimationManager>();
    std::shared_ptr<FieldModel> fieldModel;
    std::list<std::shared_ptr<UnitModel>>::iterator fieldPos;

    float damagedTime = 0;
    bool isDamaged = false;

    float health = 100;
    CharacterFaction faction = CharacterFaction::Human;
    float speed = 0.02;
    float fireInterval = 2000;
    float timeToShot = fireInterval;

public:
    HumanModel(
            sf::Vector2f start,
            const std::shared_ptr<FieldModel> & fieldModel
    ) : fieldModel(fieldModel) {
        size = {32, 50};
        sizeReduction = {0, 20};
        coords = start;

        animationManager->loadFromXML(R"(D:\C\3sem_cpp\Necromancer\resources\units\human.xml)",
                                      R"(D:\C\3sem_cpp\Necromancer\resources\units\human.png)");
        animationManager->set("stay_s");
        animationManager->play();
    }

    void addToField() override {
        fieldPos = fieldModel->addUnit(shared_from_this());
    }

    void wither() override {
        for (int i = 0; i < 2; ++i) {
            float angle = float(std::rand() % int(3.14 * 100)) / 100;
            std::cout << angle << " a" << std::endl;
            float x = coords.x + 16 * cos(angle);
            float y = coords.y + 16 * sin(angle);
            auto healthPotion = std::make_shared<HealthPotion>(
                    sf::Vector2f(x, y),
                    HealthPotion::Level::Junior
            );
            healthPotion->addToField(fieldModel);
        }

        for (int i = 0; i < 2; ++i) {
            float angle = std::rand() % int(3.14 * 100) / 100;
            std::cout << angle << " a" << std::endl;
            float x = coords.x + 16 * cos(angle);
            float y = coords.y + 16 * sin(angle);
            auto manaPotion = std::make_shared<ManaPotion>(
                    sf::Vector2f(x, y),
                    ManaPotion::Level::Junior
            );
            manaPotion->addToField(fieldModel);
        }
        fieldModel->eraseUnit(fieldPos);
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


        auto isFireAnimationPlay =
                animationManager->isPlaying() &&
                animationManager->currentAnim.substr(0, animationManager->currentAnim.size() - 1) == "fire_";

        if (r >= 400) {
            if (!isFireAnimationPlay)
                animationManager->set("stay_s");
            return;
        }

        fire(time, playerCoords);

        isFireAnimationPlay =
                animationManager->isPlaying() &&
                animationManager->currentAnim.substr(0, animationManager->currentAnim.size() - 1) == "fire_";

        if (r <= 200) {
            if (!isFireAnimationPlay)
                animationManager->set("stay_" + chooseDirection(playerCoords));
            return;
        }

        move(time, playerCoords);


        if (!isFireAnimationPlay) {
            animationManager->set("walk_" + chooseDirection(playerCoords));
            animationManager->play();
        }
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
    void fire(float time, const sf::FloatRect & playerCoords) {
        timeToShot -= time;
        if (timeToShot > 0) return;

        timeToShot = fireInterval;
        animationManager->set("fire_" + chooseDirection(playerCoords));
        animationManager->loop(false);
        animationManager->play();

        auto fireball = std::make_shared<FireballSpell>(
                -atan2((playerCoords.top - coords.y), (playerCoords.left - coords.x)),
                fieldModel,
                sf::Vector2f(coords.x, coords.y + size.y / 2),
                faction,
                900
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

    }

    std::string chooseDirection(const sf::FloatRect & playerCoords) {
        float direction = -atan2((playerCoords.top - coords.y), (playerCoords.left - coords.x));
        if (direction > -M_PI_4 && direction < M_PI_4) {
            return "d";
        } else if (direction <= -M_PI_4 && direction >= -3 * M_PI_4) {
            return "s";
        } else if (direction >= M_PI_4 && direction <= 3 * M_PI_4) {
            return "w";
        } else if (direction > 3 * M_PI_4 || direction < -3 * M_PI_4) {
            return "a";
        }
        return "";
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
            std::list<std::shared_ptr<UnitModel>>::iterator it;
            it = fieldModel->addDeadUnit(shared_from_this());
            fieldModel->eraseUnit(fieldPos);
            fieldPos = it;
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