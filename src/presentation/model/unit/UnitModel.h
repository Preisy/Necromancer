#pragma once

#include <SFML/Graphics.hpp>
#include "utils/animation/AnimationManager.h"
#include "presentation/model/ObjectModel.h"
#include "utils/level/Object.h"
#include "CharacterFaction.h"

class UnitModel : public ObjectModel {
protected:
    sf::Vector2f coords = {0, 0};
    sf::Vector2f sizeReduction = {0, 0};
    sf::Vector2f size = {0, 0};
    sf::Vector2f offset = {0, 0};

    float dx = 0;
    float dy = 0;
public:
    virtual void update(float time) = 0;

    virtual void setOffset(float x, float y) = 0;

    virtual void takeDamage(float damage) = 0;

    virtual void addToField() = 0;

    virtual sf::FloatRect getFloatRect() = 0;

    virtual CharacterFaction getCharacterFaction() = 0;

    virtual ~UnitModel() = default;

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
};