#pragma once

#include <SFML/Graphics.hpp>
#include "NpcModel.h"

#include "utils/StaticDots.h"
#include "model/interactiveGameObject/HealthPotion.h"
#include "model/interactiveGameObject/ManaPotion.h"
#include "utils/StaticDots.h"

class GolemModel : public NpcModel {
    float damagedTime = 0;
    bool isDamaged = false;

    float health = 300;
    CharacterFaction faction = CharacterFaction::Human;
    float speed = 0.02;

    bool didHit = false;
    float smashRadius = 110;
    float damage = 40;

public:
    GolemModel(
            sf::Vector2f start,
            const std::shared_ptr<FieldModel> & fieldModel
    ) : NpcModel("golem", fieldModel) {
        size = {70, 95};
        sizeReduction = {0, 20};
        coords = start;


        for (auto & item: animationManager->animList) {
            item.second.sprite.scale(1.6, 1.6);
        }
    }

    void wither() override {
        NpcModel::wither(
                {HealthPotion::Level::Senior, HealthPotion::Level::Senior},
                {ManaPotion::Level::Senior, ManaPotion::Level::Senior}
        );
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
        auto r = sqrt(
                pow((playerCoords.left + playerCoords.width / 2) - (coords.x + size.x / 2), 2) +
                pow((playerCoords.top + playerCoords.height / 2) - (coords.y + size.y / 2), 2)
        );

        bool didStartHitting =
                animationManager->currentAnim.substr(0, animationManager->currentAnim.size() - 1) == "hit_";
        bool didEndHitting = !animationManager->animList[animationManager->currentAnim].isPlaying;
        if (didStartHitting && !didEndHitting) {
            auto anim = animationManager->animList[animationManager->currentAnim];
            int i = float(anim.currentFrame + anim.speed * animationManager->speedK * time);
            if (!didHit && i == 4) {
                didHit = true;
                hit();
            }

            return;
        } else if (didStartHitting && didEndHitting) {
            didHit = true;
            animationManager->play();
        }

        if (r >= 400) {
            animationManager->set("stay_s");
            return;
        }

        if (r <= 93) {
            animationManager->set("hit_" + chooseDirection(playerCoords));
            animationManager->loop(false);
            didHit = false;
            return;
        }

        move(time, playerCoords, speed);


        animationManager->set("walk_" + chooseDirection(playerCoords));
    }

private:
    void hit() {
        for (auto & unitModel: fieldModel->getUnitModels()) {
            auto unitCoords = unitModel->getFloatRect();
            auto r = sqrt(
                    pow((unitCoords.left + unitCoords.width / 2) - (coords.x + size.x / 2), 2) +
                    pow((unitCoords.top + unitCoords.height / 2) - (coords.y + size.y / 2), 2)
            );
            if (r > smashRadius && (
                    std::dynamic_pointer_cast<PlayerModel>(unitModel) == nullptr ||
                    r > smashRadius + 10
            )) {
                continue;
            }
            if (unitModel->getCharacterFaction() != faction)
                unitModel->takeDamage(damage);
        }
    }

public:
    void takeDamage(float _damage) override {
        health -= _damage;
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


    sf::FloatRect getFloatRect() override {
        return {coords.x, coords.y, size.x, size.y};
    }

    CharacterFaction getCharacterFaction() override {
        return CharacterFaction::Human;
    }

    const std::unique_ptr<AnimationManager> & getAnimationManager() override {
        return animationManager;
    }

};