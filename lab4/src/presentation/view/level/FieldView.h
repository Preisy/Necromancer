#pragma once

#include <SFML/Graphics.hpp>
#include "presentation/model/FieldModel.h"

#include "utils/mvc/IView.h"
#include "utils/observer/Observer.h"
#include "presentation/RenderWindowDI.h"
#include "config.h"
#include "presentation/model/FieldModel.h"
#include "ObjectView.h"
#include "presentation/controller/FieldController.h"

class FieldView {
    Injected<sf::RenderWindow> window;
    Injected<FieldController> fieldController;
    ObjectView objectView;

public:
    void handleEvent(sf::Event & event) {
        fieldController->handleEvent(event);
    }

    void handleState() {
        fieldController->handleState();
    }

    void update(float time) {
        fieldController->update(time);
    }



    void draw(float time) {
        const std::shared_ptr<FieldModel> & fieldModel = fieldController->getFieldModel();
        fieldModel->getLevel().Draw(*window);


        for (const auto & item : fieldModel->getDeadUnitModels()) {
            objectView.draw(item, time);
        }
        for (const auto & item : fieldModel->getUnitModels()) {
            objectView.draw(item, time);
        }
        objectView.draw(*fieldModel->getUnitModels().begin(), time);
        for (const auto & item : fieldModel->getBulletModels()) {
            objectView.draw(item, time);
        }
    }
};