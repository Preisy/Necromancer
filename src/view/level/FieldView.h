#pragma once

#include <SFML/Graphics.hpp>
#include "model/FieldModel.h"

#include "utils/mvc/IView.h"
#include "utils/observer/Observer.h"
#include "RenderWindowDI.h"
#include "config.h"
#include "model/FieldModel.h"
#include "view/ObjectView.h"
#include "controller/FieldController.h"

class FieldView {
    Injected<sf::RenderWindow> window;
    ObjectView objectView;

public:
    void draw(const std::shared_ptr<FieldModel> & fieldModel, float time) {
        fieldModel->getLevel().Draw(*window);

        for (const auto & item: fieldModel->getDeadUnitModels())
            objectView.draw(item, time);

        for (const auto & item: fieldModel->getUnitModels())
            objectView.draw(item, time);

        for (const auto & object: fieldModel->getInteractiveGameObjects())
            objectView.draw(object, time);

        objectView.draw(*fieldModel->getUnitModels().begin(), time);

        for (const auto & item: fieldModel->getBulletModels())
            objectView.draw(item, time);

    }
};