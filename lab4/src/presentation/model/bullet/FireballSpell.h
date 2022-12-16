#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include "BulletModel.h"

#include "utils/animation/AnimationManager.h"
#include "presentation/model/FieldModel.h"


class FireballSpell : public BulletModel, public std::enable_shared_from_this<FireballSpell> {
    sf::Vector2f coords;
    float speed = 0.1;
    float dx = 0;
    float dy = 0;
    sf::Vector2f offset = {0, 0};
    sf::Vector2f size = {15, 15};

    std::unique_ptr<AnimationManager> animationManager = std::make_unique<AnimationManager>();
    std::shared_ptr<FieldModel> fieldModel = nullptr;
    std::list<std::shared_ptr<BulletModel>>::iterator fieldPos;

public:
    explicit FireballSpell(
            float direction,
            const std::shared_ptr<FieldModel> & fieldModel,
            sf::Vector2f start
    ) : fieldModel(fieldModel), coords(start) {
        animationManager->loadFromXML(
                R"(D:\C\3sem_cpp\informatics\lab4\resources\spells\fireball.xml)",
                R"(D:\C\3sem_cpp\informatics\lab4\resources\spells\fireball.png)"
        );
        animationManager->rotate(-direction);
        dx = speed * cos(direction);
        dy = -speed * sin(direction);

        animationManager->setPosition(coords.x, coords.y);
//        animationManager->set("fireball_spell");
    }

    void fire() {
        auto p = shared_from_this();
        fieldPos = fieldModel->addBullet(p);
    }

private:
    sf::FloatRect getFloatRect() {
        return {coords.x, coords.y, size.x, size.y};
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

public:
    void update(float time) override {
        coords.x += dx * time;
        coords.y += dy * time;
        if (collisionX() || collisionY()) {
            fieldModel->eraseBullet(fieldPos);
        }

        /* if collision with units*/
    }


    void setOffset(float x, float y) override {
        offset.x = x;
        offset.y = y;
        animationManager->setPosition(coords.x - offset.x, coords.y - offset.y);
    }

    const std::unique_ptr<AnimationManager> & getAnimationManager() override {
        return animationManager;
    }
};