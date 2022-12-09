#pragma once

#include <memory>
#include <vector>
#include "CurrentFieldView.h"

#include "utils/activity/Activity.h"
#include "domain/entity/LevelEntity.h"
#include "presentation/controller/LevelController.h"


class LevelActivity : public Activity {
    LevelController levelController;
    std::unique_ptr<CurrentFieldView> field = nullptr;
    /* there will be spells view */

public:
    LevelActivity() : field(levelController.getFieldView()) {}

    void handleEvent(sf::Event & event) override {
        /* ui event handler (specifically about skills view) */

        levelController.handleEvent(event);
    }

    void update(float time) override {
        levelController.update(time);
    }

    void draw(float time) override {
        /* skills view drawing */

        field->draw(time);
    }

};

