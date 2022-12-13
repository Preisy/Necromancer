#pragma once

#include <SFML/Graphics.hpp>

#include "data/Repository.h"

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
            auto buf = playerRepository.find(1);
            if (!buf) throw std::runtime_error("player does not exist while field controller");
            playerModel = std::make_shared<PlayerModel>(*buf);

            fieldModel = std::make_shared<FieldModel>(fieldId, playerModel);

            playerModel->addField(fieldModel);

            update(0); // todo зачем то точно нужно было
        }
    }

    void handleEvent(sf::Event & event) {

    }


    void handleState() {
        float shiftK = 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
            shiftK = 2;
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
    }

    void update(float time) {
        fieldModel->update(time);

        auto playerCoords = playerModel->getCoords();
//        auto x = playerCoords.x - windowWidth / 2;
        auto x = playerCoords.x - windowWidth / 2 - playerModel->getSize().x / 2;
//        auto y = playerCoords.y - windowHeight / 2;
        auto y = playerCoords.y - windowHeight / 2 - playerModel->getSize().y / 2;
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
//        playerModel->setOffset(x, tilesetSize.y - windowHeight);
    }

    [[nodiscard]]
    const std::shared_ptr<FieldModel> & getFieldModel() const {
        return fieldModel;
    }
};


#include "utils/DependencyInjection.h"

injectAsRuntime(FieldController)