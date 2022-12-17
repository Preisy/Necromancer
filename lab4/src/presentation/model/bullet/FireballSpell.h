#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include "BulletModel.h"

#include "utils/animation/AnimationManager.h"
#include "presentation/model/FieldModel.h"
#include "presentation/model/unit/CharacterFaction.h"


class FireballSpell : public BulletModel, public std::enable_shared_from_this<FireballSpell> {
//    sf::Vector2f coords;
    float damage = 25;
    float speed = 0.1;
    float dx = 0;
    float dy = 0;
    float direction = 0;
    sf::Vector2f offset = {0, 0};
    sf::Vector2f size = {16, 16};
    sf::FloatRect floatRect;

    std::unique_ptr<AnimationManager> animationManager = std::make_unique<AnimationManager>();
    std::shared_ptr<FieldModel> fieldModel = nullptr;
    CharacterFaction senderFaction;
    std::list<std::shared_ptr<BulletModel>>::iterator fieldPos;

public:
    explicit FireballSpell(
            float direction,
            const std::shared_ptr<FieldModel> & fieldModel,
            sf::Vector2f start,
            CharacterFaction senderFaction
    ) : fieldModel(fieldModel), direction(direction), senderFaction(senderFaction) {
        animationManager->loadFromXML(
                R"(D:\C\3sem_cpp\informatics\lab4\resources\spells\fireball.xml)",
                R"(D:\C\3sem_cpp\informatics\lab4\resources\spells\fireball.png)"
        );
        animationManager->rotate(-direction);
        dx = speed * cos(direction);
        dy = -speed * sin(direction);

        floatRect.left = start.x;
        floatRect.top = start.y;
//        floatRect.top -= 40 * sin(direction);
//        floatRect.left += 40 * cos(direction);

        floatRect.left += size.x / 2;

        double r = sqrt(size.x * size.x + size.y * size.y);
        floatRect.width = cos(direction + M_PI_4) * r;
        floatRect.height = -sin(direction + M_PI_4) * r;

        animationManager->setPosition(floatRect.left, floatRect.top);
    }

    void fire() {
        auto p = shared_from_this();
        fieldPos = fieldModel->addBullet(p);
    }

private:
    sf::FloatRect getFloatRect() const {
        return floatRect;
    }

    bool collision(int dir, std::string && objectsName) {
        auto rect = getFloatRect();
        auto objects = fieldModel->getLevel().GetObjects(objectsName);
        for (const auto & object: objects) {
            if (!rect.intersects(object.rect)) continue;

            if (dir == 0 && dx > 0
                && rect.left < object.rect.left
                && rect.left + rect.width > object.rect.left
                    ) {
                return true;
            } else if (dir == 0 && dx < 0
                       && rect.left < object.rect.left + object.rect.width
                       && rect.left + rect.width > object.rect.left
                    ) {
                return true;
            } else if (dir == 1 && dy > 0
                       && rect.top < object.rect.top
                       && rect.top + rect.height > object.rect.top
                    ) {
                return true;
            } else if (dir == 1 && dy < 0
                       && rect.top < object.rect.top + object.rect.height
                       && rect.top + rect.height > object.rect.top
                    ) {
                return true;
            }
        }
        return false;
    }

    bool collisionX() {
        return collision(0, "solid");
    }

    bool collisionY() {
        return collision(1, "solid");
    }

    bool hitIntersectedUnit() {
        for (const auto & unit: fieldModel->getUnitModels()) {
            if (unit == nullptr) continue;
            if (unit->getCharacterFaction() == senderFaction) continue;
            if (unit->getFloatRect().intersects(getFloatRect())) {
                unit->takeDamage(damage);
                return true;
            }
        }
        return false;
    }

public:
    void update(float time) override {
        floatRect.left += dx * time;
        floatRect.top += dy * time;

        if (collisionX() || collisionY()) {
            fieldModel->eraseBullet(fieldPos);
            return;
        }
        if (hitIntersectedUnit()) {
            fieldModel->eraseBullet(fieldPos);
            return;
        }

        /* if collision with units*/
    }


    void setOffset(float x, float y) override {
        offset.x = x;
        offset.y = y;
        animationManager->setPosition(floatRect.left - offset.x, floatRect.top - offset.y);
    }

    const std::unique_ptr<AnimationManager> & getAnimationManager() override {
        return animationManager;
    }
};