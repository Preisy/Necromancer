#pragma once

#include <memory>
#include "UnitModel.h"

#include "model/interactiveGameObject/HealthPotion.h"
#include "model/interactiveGameObject/ManaPotion.h"
#include "model/FieldModel.h"

class NpcModel : public UnitModel, public std::enable_shared_from_this<NpcModel> {
protected:
    std::shared_ptr<FieldModel> fieldModel;
    std::list<std::shared_ptr<UnitModel>>::iterator fieldPos;

    explicit NpcModel(
            const std::string & spriteListName,
            const std::shared_ptr<FieldModel> & fieldModel
    ) : UnitModel(spriteListName), fieldModel(fieldModel) {}

public:
    void addToField() override {
        fieldPos = fieldModel->addUnit(shared_from_this());
    }

protected:
    void wither(
            const std::vector<HealthPotion::Level> & healthPotions,
            const std::vector<ManaPotion::Level> & manaPotions
    ) {
        for (const auto & level: healthPotions) {
            float angle = float(std::rand() % int(3.14 * 100)) / 100;
            std::cout << angle << " a" << std::endl;
            float x = float(coords.x + size.x / 2) + 16 * cos(angle);
            float y = float(coords.y + size.y / 2) + 16 * sin(angle);
            auto healthPotion = std::make_shared<HealthPotion>(
                    sf::Vector2f(x, y),
                    level
            );
            healthPotion->addToField(fieldModel);
        }
        for (const auto & level: manaPotions) {
            float angle = std::rand() % int(3.14 * 100) / 100;
            std::cout << angle << " a" << std::endl;
            float x = float(coords.x + size.x / 2) + 16 * cos(angle);
            float y = float(coords.y + size.y / 2) + 16 * sin(angle);
            auto manaPotion = std::make_shared<ManaPotion>(
                    sf::Vector2f(x, y),
                    level
            );
            manaPotion->addToField(fieldModel);
        }

        fieldModel->eraseUnit(fieldPos);
    }

private:
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

protected:
    void move(float time, const sf::FloatRect & playerCoords, float speed) {
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

    std::string chooseDirection(const sf::FloatRect & rect) {
        float direction = -atan2((rect.top - coords.y), (rect.left - coords.x));
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

    sf::FloatRect getPlayerCoords() {
        for (const auto & unit: fieldModel->getUnitModels()) {
            if (std::dynamic_pointer_cast<PlayerModel>(unit) != nullptr) {
                return unit->getFloatRect();
            }
        }
        throw std::runtime_error("player not found while HumanModel::update()");
    };
};