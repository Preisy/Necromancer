#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

#include "utils/animation/AnimationManager.h"
#include "model/ObjectModel.h"
#include "utils/level/Object.h"
#include "CharacterFaction.h"


class UnitModel : public ObjectModel {
protected:
    std::unique_ptr<AnimationManager> animationManager = std::make_unique<AnimationManager>();;

    sf::Vector2f coords = {0, 0};
    sf::Vector2f sizeReduction = {0, 0};
    sf::Vector2f size = {0, 0};
    sf::Vector2f offset = {0, 0};

    float dx = 0;
    float dy = 0;

    explicit UnitModel(const std::string & spriteListName) {
        animationManager->loadFromXML(R"(D:\C\3sem_cpp\Necromancer\resources\units\)" + spriteListName + ".xml",
                                      R"(D:\C\3sem_cpp\Necromancer\resources\units\)" + spriteListName + ".png");
        animationManager->set("stay_s");
        animationManager->play();
    }

public:
    virtual void addToField() = 0;

    virtual void update(float time) = 0;

    virtual void takeDamage(float damage) = 0;

    virtual void wither() = 0;

    virtual void revive(CharacterFaction characterFaction) = 0;

    virtual sf::FloatRect getFloatRect() = 0;

    virtual CharacterFaction getCharacterFaction() = 0;

    virtual ~UnitModel() = default;

    virtual void setOffset(float x, float y) {
        this->offset.x = x;
        this->offset.y = y;
        animationManager->setPosition(coords.x - offset.x, coords.y - offset.y + size.y);
    }

    void collision(int dir, std::vector<Object> && objects) {
        auto unitRect = getFloatRect();
        auto rect = sf::FloatRect(
                unitRect.left + sizeReduction.x,
                unitRect.top + sizeReduction.y,
                unitRect.width - sizeReduction.x,
                unitRect.height - sizeReduction.y
        );
        for (const auto & object: objects) {
            if (!rect.intersects(object.rect)) continue;

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
                coords.x = object.rect.left + object.rect.width - sizeReduction.x;
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

    void collision(int dir, const std::list<std::shared_ptr<UnitModel>> & objects) {
        auto unitRect = getFloatRect();
        auto rect = sf::FloatRect(
                unitRect.left + sizeReduction.x,
                unitRect.top + sizeReduction.y,
                unitRect.width - sizeReduction.x,
                unitRect.height - sizeReduction.y
        );
        for (const auto & object: objects) {
            if (object.get() == this) continue;
            if (object.get() == nullptr) continue;
            auto objectRect = object->getFloatRect();
            if (!rect.intersects(objectRect)) continue;

            if (dir == 0 && dx > 0
                && rect.left < objectRect.left
                && rect.left + rect.width > objectRect.left
                    ) {
                coords.x = objectRect.left - size.x;
                break;
            } else if (dir == 0 && dx < 0
                       && rect.left < objectRect.left + objectRect.width
                       && rect.left + rect.width > objectRect.left
                    ) {
                coords.x = objectRect.left + objectRect.width - sizeReduction.x;
                break;
            } else if (dir == 1 && dy > 0
                       && rect.top < objectRect.top
                       && rect.top + rect.height > objectRect.top
                    ) {
                coords.y = objectRect.top - size.y;
                break;
            } else if (dir == 1 && dy < 0
                       && rect.top < objectRect.top + objectRect.height
                       && rect.top + rect.height > objectRect.top
                    ) {
                coords.y = objectRect.top + objectRect.height - sizeReduction.y;
                break;
            }
        }
    }

    const std::unique_ptr<AnimationManager> & getAnimationManager() override {
        return animationManager;
    }
};