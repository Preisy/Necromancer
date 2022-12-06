#pragma once

#include <memory>
#include <vector>

#include "utils/mvc/IView.h"
#include "LevelController.h"


class LevelView : public IView {
    LevelController levelController;
    std::unique_ptr<IView> field;

public:
    void update(long long time) override;

    void draw() override;
};

