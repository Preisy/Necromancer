#pragma once

#include <SFML/Graphics.hpp>
#include "NpcModel.h"

#include "utils/StaticDots.h"
#include "model/bullet/FireballSpell.h"

class HumanModel : public NpcModel {
    float damagedTime = 0;
    bool isDamaged = false;

    float health = 100;
    float speed = 0.02;
    float fireInterval = 2000;
    float timeToShot = fireInterval;

public:
    HumanModel(
            sf::Vector2f start,
            const std::shared_ptr<FieldModel> & field
    ) : NpcModel("human", field, CharacterFaction::Human) {
        fieldModel = field;
        size = {32, 50};
        sizeReduction = {0, 20};
        coords = start;
    }

    void wither() override {
        NpcModel::wither(
                {HealthPotion::Level::Junior, HealthPotion::Level::Junior},
                {ManaPotion::Level::Junior, ManaPotion::Level::Junior}
        );
    }

    void revive(CharacterFaction characterFaction) override {
        NpcModel::revive(characterFaction);
        health = 100;
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


        auto isCurrentAnimIsFire = animationManager->currentAnim.substr(0, animationManager->currentAnim.size() - 1) == "fire_";
        auto isFireAnimationPlay =
                animationManager->isPlaying() && isCurrentAnimIsFire;
        if (isCurrentAnimIsFire && !animationManager->isPlaying()) {
            animationManager->set("stay_s");
            return;
        }

        auto [unitCoords, r] = getNearestUnitCoords([this](CharacterFaction unitFaction){
            return unitFaction != faction;
        });


        if (unitCoords == sf::FloatRect() || r >= 400) {
            animationManager->set("stay_s");

            if (faction == CharacterFaction::Player) {
                auto playerCoords = getPlayerCoords();
                float pR = sqrt(
                        pow(playerCoords.left + playerCoords.width / 2 - (coords.x + size.x / 2), 2) +
                        pow(playerCoords.top + playerCoords.height / 2 - (coords.y + size.y / 2), 2)
                );
                if (pR >= 200) {
                    move(time, playerCoords, speed);
                    animationManager->set("walk_" + chooseDirection(playerCoords));
                }
            }

            return;
        }

        interactWithUnit(unitCoords, r, time);
    }

    void interactWithUnit(sf::FloatRect unitCoords, float r, float time) {
        fire(time, unitCoords);

        auto isFireAnimationPlay =
                animationManager->isPlaying() &&
                animationManager->currentAnim.substr(0, animationManager->currentAnim.size() - 1) == "fire_";

        if (r <= 200) {
            if (!isFireAnimationPlay)
                animationManager->set("stay_" + chooseDirection(unitCoords));
            return;
        }

        move(time, unitCoords, speed);


        if (!isFireAnimationPlay) {
            animationManager->set("walk_" + chooseDirection(unitCoords));
            animationManager->play();
        }
    }

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

public:
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

            if (revivesCount >= 1) {
                NpcModel::wither({}, {});
                return;
            }
        } else {
            isDamaged = true;
            damagedTime = 500;
            animationManager->animList[animationManager->currentAnim].sprite.setColor(sf::Color(0xff3c3cff));
        }
    }


    sf::FloatRect getFloatRect() override {
        return {coords.x, coords.y, size.x, size.y};
    }
};