#pragma once

#include <fstream>
#include <memory>
#include <vector>
#include "UnitModel.h"

#include "utils/observer/Subject.h"
#include "utils/level/Level.h"


class FieldModel {
    std::vector<std::shared_ptr<UnitModel>> unitModels;
    sf::Vector2f offset = {0, 0};
    Level lvl;
    std::vector<std::vector<sf::Vector2f>> tileCoords;
    std::vector<sf::Rect<float>> objectsCoords;

public:
    explicit FieldModel(int modelId, const std::shared_ptr<UnitModel> & playerModel) {
        lvl.LoadFromFile(
                R"(D:\C\3sem_cpp\informatics\lab4\resources\levels\maps\field)" + std::to_string(modelId) + ".xml"
        );
        for (auto & item: lvl.getLayers()) {
            tileCoords.emplace_back();
            for (auto & tile: item.getTiles()) {
                (tileCoords.end() - 1)->push_back(tile.getPosition());
            }
        }


        auto coords = lvl.GetObject("player").rect;
        offset.x = coords.left;
        offset.y = coords.top;

        unitModels.push_back(playerModel);
    }


    void update(float time) {
        for (const auto & unitModel: unitModels) {
            unitModel->update(time);
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
    }

    sf::Vector2f getPlayerCoords() {
        auto rect = lvl.GetObject("player").getRect();
        return {rect.left, rect.top};
    }

    const sf::Vector2f & getOffset() const {
        return offset;
    }

    Level & getLevel() {
        return lvl;
    }

    [[nodiscard]]
    const std::vector<std::shared_ptr<UnitModel>> & getUnitModels() const {
        return unitModels;
    }
};