#pragma once

#include <memory>
#include <vector>
#include "FieldView.h"

#include "utils/activity/Activity.h"
#include "utils/DependencyInjection.h"
#include "presentation/model/LevelModel.h"
#include "presentation/controller/LevelController.h"


class LevelActivity : public Activity {
    LevelController levelController;
    /* spellsController */
    FieldView fieldView;
    /* there will be spells view */

public:
    void handleEvent(sf::Event & event) override {
        /* ui event handler (specifically about skills view) */

        /* spellsController.handleEvent(event); */
        levelController.handleEvent(event);
        fieldView.handleEvent(event);
    }

    void handleState() override {
        fieldView.handleState();
    }

    void update(float time) override {
        levelController.update(time);
        fieldView.update(time);
    }

    void draw() override {
        /* skills view drawing */
        fieldView.draw();
    }

};

