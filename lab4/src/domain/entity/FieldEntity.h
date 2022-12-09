#pragma once

#include <fstream>
#include <memory>
#include <vector>

#include "utils/observer/Subject.h"
#include "domain/entity/UnitEntity.h"

class FieldEntity : public Subject {
    std::vector<std::vector<char>> tileMap;
    std::vector<std::unique_ptr<UnitEntity>> unitModels;

public:
    explicit FieldEntity(int modelId) {
        // todo написать с помощью парсинга xml
        std::ifstream fin(R"(D:\C\3sem_cpp\informatics\lab4\resources\levels\maps\)" + std::to_string(modelId) + ".txt");
        if (!fin.is_open()) throw std::runtime_error("Field " + std::to_string(modelId) + " not found");
        std::string line;
        while(std::getline(fin, line)) {
            std::vector<char> & tileMapLine = tileMap.emplace_back();
            for(auto it : line)
                tileMapLine.push_back(it);
        }
    }

    [[nodiscard]]
    const std::vector<std::vector<char>> & getTileMap() const {
        return tileMap;
    }
};