#pragma once

#include <fstream>
#include <memory>
#include <list>
#include "unit/UnitModel.h"

#include "utils/observer/Subject.h"
#include "utils/level/Level.h"
#include "model/bullet/BulletModel.h"
#include "model/interactiveGameObject/InteractiveGameObject.h"

class FieldModel {
    std::vector<std::vector<sf::Vector2f>> tileCoords;
    std::list<std::shared_ptr<UnitModel>> unitModels;
    std::list<std::shared_ptr<UnitModel>> deadUnitModels;
    std::list<std::shared_ptr<BulletModel>> bulletModels;
    std::list<std::shared_ptr<InteractiveGameObject>> interactiveGameObjects;

    Level lvl;
    sf::Vector2f offset = {0, 0};
    int fieldId;

    sf::Vector2f playerCoords = {-1, -1};

public:
    explicit FieldModel(
            int modelId
    ) : fieldId(modelId) {
        lvl.LoadFromFile(
                R"(D:\C\3sem_cpp\Necromancer\resources\levels\maps\field)" + std::to_string(modelId) + ".xml"
        );
        for (auto & item: lvl.getLayers()) {
            tileCoords.emplace_back();
            for (auto & tile: item.getTiles()) {
                (tileCoords.end() - 1)->push_back(tile.getPosition());
            }
        }

    }


    void update(float time) {
        for (const auto & unitModel: unitModels) {
            if (unitModel != nullptr)
                unitModel->update(time);
        }
        for (auto & bulletModel: bulletModels) {
            if (bulletModel != nullptr)
                bulletModel->update(time);
        }
        for (auto it = bulletModels.begin(); it != bulletModels.end(); ++it) {
            if (*it == nullptr) {
                it = bulletModels.erase(it);
                --it;
            }
        }
        for (auto it = unitModels.begin(); it != unitModels.end(); ++it) {
            if (*it == nullptr) {
                it = unitModels.erase(it);
                --it;
            }
        }
        for (auto it = deadUnitModels.begin(); it != deadUnitModels.end(); ++it) {
            if (*it == nullptr) {
                it = deadUnitModels.erase(it);
                --it;
            }
        }
        for (auto it = interactiveGameObjects.begin(); it != interactiveGameObjects.end(); ++it) {
            if (*it == nullptr) {
                it = interactiveGameObjects.erase(it);
                --it;
            }
        }
    }




    void setOffset(float x, float y) {
        offset.x = x;
        offset.y = y;
        auto & layers = lvl.getLayers();
        for (int i = 0; i < layers.size(); ++i) {
            auto & tiles = layers[i].getTiles();
            for (int j = 0; j < tiles.size(); ++j) {
                tiles[j].setPosition(tileCoords[i][j].x - offset.x, tileCoords[i][j].y - offset.y);
            }
        }


        for (const auto & unitModel: unitModels) {
            unitModel->setOffset(offset.x, offset.y);
        }
        for (const auto & bulletModel: bulletModels) {
            bulletModel->setOffset(offset.x, offset.y);
        }
        for (const auto & deadUnitModel: deadUnitModels) {
            deadUnitModel->setOffset(offset.x, offset.y);
        }

        for (const auto & interactiveGameObject: interactiveGameObjects) {
            interactiveGameObject->setOffset(offset.x, offset.y);
        }
    }

    sf::Vector2f getPlayerCoords(int fromField) {
        for (auto & player : lvl.GetObjects("player")) {
            if (player.properties["fromField"] == std::to_string(fromField)) {
                return {player.rect.left, player.rect.top};
            }
        }
        throw std::runtime_error("player coords not found");
    }

    auto addUnit(const std::shared_ptr<UnitModel> & unitModel) {
        return unitModels.insert(unitModels.end(), unitModel);
    }

    auto eraseUnit(std::list<std::shared_ptr<UnitModel>>::iterator iter) {
        *iter = nullptr;
        return 1;
    }

    auto addDeadUnit(const std::shared_ptr<UnitModel> & deadUnitModel) {
        return deadUnitModels.insert(deadUnitModels.end(), deadUnitModel);
    }

    auto eraseDeadUnit(std::list<std::shared_ptr<UnitModel>>::iterator iter) {
        *iter = nullptr;
        return 1;
    }

    auto addBullet(const std::shared_ptr<BulletModel> & bulletModel) {
        return bulletModels.insert(bulletModels.end(), bulletModel);
    }

    void eraseBullet(std::list<std::shared_ptr<BulletModel>>::iterator iter) {
        *iter = nullptr;
    }

    auto addInteractiveGameObject(const std::shared_ptr<InteractiveGameObject> & obj) {
        return interactiveGameObjects.insert(interactiveGameObjects.end(), obj);
    }

    void eraseInteractiveGameObject(std::list<std::shared_ptr<InteractiveGameObject>>::iterator iter) {
        *iter = nullptr;
    }

    const sf::Vector2f & getOffset() const {
        return offset;
    }

    Level & getLevel() {
        return lvl;
    }

    [[nodiscard]]
    const std::list<std::shared_ptr<BulletModel>> & getBulletModels() const {
        return bulletModels;
    }

    [[nodiscard]]
    const std::list<std::shared_ptr<UnitModel>> & getUnitModels() const {
        return unitModels;
    }

    [[nodiscard]]
    const std::list<std::shared_ptr<UnitModel>> & getDeadUnitModels() const {
        return deadUnitModels;
    }

    [[nodiscard]]
    const std::list<std::shared_ptr<InteractiveGameObject>> & getInteractiveGameObjects() const {
        return interactiveGameObjects;
    }

    int getFieldId() const {
        return fieldId;
    }
};