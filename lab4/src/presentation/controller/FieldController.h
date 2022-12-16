#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
//#include <cmath>

#include "data/Repository.h"
#include "presentation/model/FieldModel.h"
#include "presentation/model/unit/PlayerModel.h"
#include "config.h"


class FieldController {
    std::shared_ptr<FieldModel> fieldModel = nullptr;
    std::shared_ptr<PlayerModel> playerModel = nullptr;
    Repository<FieldModel> fieldRepository;
    Repository<PlayerModel> playerRepository;

public:
    FieldController() {
        std::cout << "crutch" << std::endl;
    }

    explicit FieldController(int fieldId) {
        auto field = fieldRepository.find(fieldId);
        if (field) {
            fieldModel = std::make_unique<FieldModel>(*field);
        } else {
            setNewField(fieldId);
        }
    }

private:
    void setNewField(int fieldId) {
        //            auto buf = playerRepository.find(1);
//            if (!buf) throw std::runtime_error("player does not exist while field controller");
        auto buf = PlayerModel();
        playerModel = std::make_shared<PlayerModel>(std::move(buf));
//            playerModel = std::make_shared<PlayerModel>();

        fieldModel = std::make_shared<FieldModel>(fieldId, playerModel);

        playerModel->setField(fieldModel);

        update(0); // todo зачем то точно нужно было
    }

public:
    void handleEvent(sf::Event & event) {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                playerModel->fire();
            }
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::E) {
                std::string interactiveName = getInteractive();
            }
        }
    }

private:
    std::string getInteractive() {
        return "";
    }

    std::string getIntersectedInteractor() {
        auto playerRect = playerModel->getFloatRect();
        for (const auto & object: fieldModel->getLevel().getObjects()) {
            if (playerRect.intersects(object.rect)) {
                return object.name;
            }
        }
        return "";
    }

public:
    void handleState() {
        float shiftK = 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
            shiftK = 1.5;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            playerModel->setDx(-0.1 * shiftK);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            playerModel->setDx(0.1 * shiftK);
        } else {
            playerModel->setDx(0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            playerModel->setDy(0.1 * shiftK);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            playerModel->setDy(-0.1 * shiftK);
        } else {
            playerModel->setDy(0);
        }
        auto mousePos = sf::Mouse::getPosition(*Injected<sf::RenderWindow>());
        playerModel->setDirection({
            mousePos.x * windowWidth / changedWindowWidth,
            mousePos.y * windowHeight / changedWindowHeight
        });
    }

    void update(float time) {
        fieldModel->update(time);

        auto playerCoords = playerModel->getCoords();
        auto playerSize = playerModel->getSize();
        auto x = playerCoords.x - windowWidth / 2 + playerSize.x / 2;
        auto y = playerCoords.y - windowHeight / 2 + playerSize.y / 2;
        auto tilesetSize = fieldModel->getLevel().getLevelSize();
        if (x < 0) {
            x = 0;
        } else if (x + windowWidth > tilesetSize.x) {
            x = tilesetSize.x - windowWidth;
        }
        if (y < 0) {
            y = 0;
        } else if (y + windowHeight > tilesetSize.y) {
            y = tilesetSize.y - windowHeight;
        }

        fieldModel->setOffset(x, y);

        std::string intersectedInteractiveName = getIntersectedInteractor();
        if (intersectedInteractiveName == "field") {
            int fieldId = fieldModel->getLevel().GetObject(intersectedInteractiveName).GetPropertyInt("fieldId");
            setNewField(fieldId);
        }
    }

    [[nodiscard]]
    const std::shared_ptr<FieldModel> & getFieldModel() const {
        return fieldModel;
    }
};


#include "utils/DependencyInjection.h"

injectAsRuntime(FieldController)