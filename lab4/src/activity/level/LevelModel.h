#pragma once

#include "utils/observer/Subject.h"
#include "activity/field/FieldModel.h"

class LevelModel : Subject {
    std::vector<std::unique_ptr<FieldModel>> fields;

public:

};