#pragma once

#include <fstream>
#include <memory>

#include "utils/observer/Subject.h"
//#include "utils/Repository.h"
#include "FieldModel.h"

class LevelModel {
    std::vector<std::shared_ptr<FieldModel>> fields;

public:
    // todo в interactor
//    explicit LevelEntity(int modelId) {
//        // todo написать с помощью парсинга xml
//        std::ifstream fin(R"(D:\C\3sem_cpp\informatics\lab4\resources\levels\)" + std::to_string(modelId) + ".txt");
//        if (!fin.is_open()) throw std::runtime_error("Field " + std::to_string(modelId) + " not found");
//
//        std::string line;
//        while (std::getline(fin, line)) {
//            int fieldId = std::atoi(line.c_str());
//            if (fieldId == 0)
//                throw std::runtime_error("Don't correct map name in level " + std::to_string(modelId));
//
//            fields.push_back(std::make_shared<FieldEntity>(fieldId));
//        }
//    }

    [[nodiscard]]
    const std::vector<std::shared_ptr<FieldModel>> & getFields() const {
        return fields;
    }
};