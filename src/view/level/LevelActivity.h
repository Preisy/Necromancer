#pragma once

#include <memory>
#include <vector>
#include "FieldView.h"

#include "utils/activity/Activity.h"
#include "utils/DependencyInjection.h"
#include "controller/LevelController.h"
#include "view/gameInterface/HealthBarView.h"

class LevelActivity : public Activity {
    LevelController levelController;
    Injected<FieldController> fieldController;

    FieldView fieldView;
    HealthBarView healthBarView;
//    SpellView spellView;

public:
    void handleEvent(sf::Event & event) override {
        levelController.handleEvent(event);
        fieldController->handleEvent(event);
    }

    void handleState() override {
        fieldController->handleState();
    }

    void update(float time) override {
        levelController.update(time);
        fieldController->update(time);
    }

    void draw(float time) override {
        const std::shared_ptr<FieldModel> & fieldModel = fieldController->getFieldModel();
        fieldView.draw(fieldModel, time);

        const std::shared_ptr<PlayerModel> & playerModel = fieldController->getPlayerModel();
        /* skills view drawing */

        healthBarView.draw(playerModel, time);
    }

};

