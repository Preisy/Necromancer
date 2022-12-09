#pragma once

#include <SFML/Graphics.hpp>
#include "domain/entity/FieldEntity.h"

#include "utils/mvc/IView.h"
#include "utils/observer/Observer.h"
#include "presentation/RenderWindowDI.h"
#include "config.h"
#include "presentation/model/CurrentFieldModel.h"

class CurrentFieldView : public IView, public Observer {
    Injected<sf::RenderWindow> window;

public:
    /* from observer */
    void update() override {

    }

public:
    explicit CurrentFieldView(const std::shared_ptr<CurrentFieldModel> & fieldModel) : Observer(fieldModel) {}

    void draw(float time) override {
        auto p = std::dynamic_pointer_cast<CurrentFieldModel>(observerSubject.lock());
        if (!p) throw std::runtime_error("Field view is not observes for any Field model");

        sf::RectangleShape rectangle = sf::RectangleShape(sf::Vector2f(fieldCellSize, fieldCellSize));
        auto & tileMap = p->getCurrentModel()->getTileMap();
        for (int i = 0; i < tileMap.size(); ++i) {
            for (int j = 0; j < tileMap[i].size(); ++j) {
                if (tileMap[i][j] == ' ')
                    rectangle.setFillColor(sf::Color(0x898989ff));
                else if (tileMap[i][j] == '1')
                    rectangle.setFillColor(sf::Color(0x404040ff));
                else if (tileMap[i][j] == 's')
                    rectangle.setFillColor(sf::Color(0x32a92eff));
                else rectangle.setFillColor(sf::Color(0xe8e8eff));

                rectangle.setPosition((float) j*fieldCellSize, (float) i*fieldCellSize);
                window->draw(rectangle);
            }
        }
    }
};