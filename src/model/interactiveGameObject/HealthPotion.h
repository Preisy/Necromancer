#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include <memory>
#include "InteractiveGameObject.h"
#include "model/FieldModel.h"


class HealthPotion : public InteractiveGameObject, public std::enable_shared_from_this<HealthPotion> {
    sf::Vector2f coords;
    sf::Texture t;
    std::unique_ptr<sf::Sprite> sprite = std::make_unique<sf::Sprite>();
    std::list<std::shared_ptr<InteractiveGameObject>>::iterator fieldPos;
    float health = 0;

public:
    enum Level {
        Junior = 1,
        Middle = 2,
        Senior = 3
    };


    HealthPotion(const sf::Vector2f & coords, HealthPotion::Level healthLevel) : coords(coords) {
        if (healthLevel == Junior) {
            t.loadFromFile(R"(D:\C\3sem_cpp\Necromancer\resources\interactiveGameObjects\potion\health\health_potion_junior.png)");
            health = 25;
        } else if (healthLevel == Middle) {
            t.loadFromFile(R"(D:\C\3sem_cpp\Necromancer\resources\interactiveGameObjects\potion\health\health_potion_middle.png)");
            health = 50;
        } else if (healthLevel == Senior) {
            t.loadFromFile(R"(D:\C\3sem_cpp\Necromancer\resources\interactiveGameObjects\potion\health\health_potion_senior.png)");
            health = 70;
        }
        sprite->setTexture(t);
        sprite->setPosition(coords.x, coords.y);
    }

    float extract() const {
        *fieldPos = nullptr;
        return health;
    }

    void addToField(const std::shared_ptr<FieldModel> & fieldModel) {
        fieldPos = fieldModel->addInteractiveGameObject(shared_from_this());
    }

    sf::FloatRect getFloatRect() override {
        return {coords.x, coords.y, 0, 0};
    }

    void setOffset(float x, float y) override {
        sprite->setPosition(coords.x - x, coords.y - y);
    }

    const std::unique_ptr<sf::Sprite> & getSprite() override {
        return sprite;
    }

};