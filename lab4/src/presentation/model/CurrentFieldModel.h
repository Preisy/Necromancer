#pragma once

#include <memory>

#include "utils/observer/Subject.h"
#include "domain/entity/FieldEntity.h"

class CurrentFieldModel : public Subject {
    std::shared_ptr<FieldEntity> currentModel;

public:
    [[nodiscard]]
    const std::shared_ptr<FieldEntity> & getCurrentModel() const {
        return currentModel;
    }

    void setCurrentModel(const std::shared_ptr<FieldEntity> & currentModel) {
        CurrentFieldModel::currentModel = currentModel;
        notify();
    }
};