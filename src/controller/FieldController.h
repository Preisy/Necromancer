#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
//#include <cmath>

#include "utils/activity/ActivityManager.h"
#include "view/menu/GameOverActivity.h"
#include "data/Repository.h"
#include "model/FieldModel.h"
#include "model/unit/PlayerModel.h"
#include "config.h"
#include "model/unit/HumanModel.h"
#include "model/unit/GolemModel.h"


class FieldController {
    Injected<ActivityManager> activityManager;
    std::shared_ptr<FieldModel> fieldModel = nullptr;
    std::shared_ptr<PlayerModel> playerModel = nullptr;
    Repository<FieldModel> fieldRepository;
    Repository<PlayerModel> playerRepository;

public:
    FieldController() {
        std::cout << "crutch" << std::endl;
    }

    explicit FieldController(int fieldId) {
        playerModel = playerRepository.find(1);
        if (playerModel == nullptr)
            throw std::runtime_error("player does not exist while field controller");

        setNewField(fieldId, 0);
    }

    void resetGame() {
        playerModel->setField(nullptr);
        fieldModel = nullptr;
        fieldRepository.eraseAll();
        playerRepository.erase(1);
        playerRepository.insert(1, std::make_shared<PlayerModel>());
//        activityManager->pop();
    }

private:
    void saveField(int fieldId) {
        fieldRepository.insertOrAssign(fieldId, fieldModel);
    }

    void setNewField(int fieldId, int prevField) {
        fieldModel = fieldRepository.find(fieldId);
        if (fieldModel != nullptr) {
//            playerModel->setField(fieldModel);
            auto playerCoords = fieldModel->getPlayerCoords(prevField);
            playerModel->setCoords(playerCoords);
            playerModel->setField(fieldModel);
//            playerModel->addToField();

        } else {
            fieldModel = std::make_shared<FieldModel>(fieldId);
            auto playerCoords = fieldModel->getPlayerCoords(prevField);
            playerModel->setCoords(playerCoords);
            playerModel->setField(fieldModel);
            playerModel->addToField();

            for (const auto & object: fieldModel->getLevel().GetObjects("human")) {
                std::make_shared<HumanModel>(
                        sf::Vector2f(object.rect.left, object.rect.top),
                        fieldModel
                )->addToField();
            }
            for (const auto & object: fieldModel->getLevel().GetObjects("golem")) {
                std::make_shared<GolemModel>(
                        sf::Vector2f(object.rect.left, object.rect.top),
                        fieldModel
                )->addToField();
            }
        }


        update(0); // todo ?????????? ???? ?????????? ?????????? ????????
    }

public:
    void handleEvent(sf::Event & event) {
        if (!playerModel->isAlive()) {
            if (event.type == sf::Event::KeyPressed ||
                event.type == sf::Event::MouseButtonPressed) {
                activityManager->push(std::make_unique<GameOverActivity>());
            }
            return;
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                playerModel->fire();
            }
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Space) {
                playerModel->fire();
            }
            if (event.key.code == sf::Keyboard::F) {
                auto interactive = getNearestInteractive<UnitModel>(fieldModel->getDeadUnitModels());
                if (interactive.first <= 100) {
                    if (interactive.second != nullptr)
                        interactive.second->wither();
                }
            }
            if (event.key.code == sf::Keyboard::R) {
                auto interactive = getNearestInteractive<UnitModel>(fieldModel->getDeadUnitModels());
                if (interactive.first <= 100) {
                    if (interactive.second != nullptr)
                        interactive.second->revive(CharacterFaction::Player);
                }
            }
            if (event.key.code == sf::Keyboard::E) {
                auto interactive = getNearestInteractive<InteractiveGameObject>(fieldModel->getInteractiveGameObjects());
                if (interactive.first <= 100) {
                    if (std::dynamic_pointer_cast<HealthPotion>(interactive.second) != nullptr) {
                        auto p = std::dynamic_pointer_cast<HealthPotion>(interactive.second);
                        playerModel->addHealth(p->extract());
                    } else if (std::dynamic_pointer_cast<ManaPotion>(interactive.second) != nullptr) {
                        auto p = std::dynamic_pointer_cast<ManaPotion>(interactive.second);
                        playerModel->addMana(p->extract());
                    }
                }
            }
        }
    }

private:
    template<class Object, class Container>
    std::pair<int, std::shared_ptr<Object>> getNearestInteractive(const Container & objects) {
        auto playerRect = playerModel->getFloatRect();
        float minR = std::numeric_limits<float>::max();
        std::shared_ptr<Object> nearestObject = nullptr;
        for (const auto & object: objects) {
            auto objectRect = object->getFloatRect();
            float r = sqrt(
                    pow(objectRect.left - (playerRect.left + playerRect.width / 2), 2) +
                    pow(objectRect.top - (playerRect.top + playerRect.height / 2), 2)
            );
            if (minR > r) {
                minR = r;
                nearestObject = object;
            }
        }
        return {minR, nearestObject};
    }

    Object isIntersectedWithInteractive(const std::string & interactiveName) {
        auto playerRect = playerModel->getFloatRect();
        for (const auto & object: fieldModel->getLevel().GetObjects(interactiveName)) {
            if (playerRect.intersects(object.rect)) {
                return object;
            }
        }
        return {};
    }

public:
    void handleState() {
        float shiftK = 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
            shiftK = 1.4;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            playerModel->setDx(-0.04 * shiftK);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            playerModel->setDx(0.04 * shiftK);
        } else {
            playerModel->setDx(0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            playerModel->setDy(0.04 * shiftK);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            playerModel->setDy(-0.04 * shiftK);
        } else {
            playerModel->setDy(0);
        }
        auto mousePos = sf::Mouse::getPosition(*Injected<sf::RenderWindow>());
        playerModel->setDirection(
                {mousePos.x * windowWidth / changedWindowWidth, mousePos.y * windowHeight / changedWindowHeight}
        );
    }

    void update(float time) {
        if (!playerModel->isAlive()) {
            for (auto & unit: fieldModel->getUnitModels()) {
                if (std::dynamic_pointer_cast<PlayerModel>(unit) == nullptr) {
                    unit->getAnimationManager()->pause();
                }
            }
            return;
        }

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

        if (Object obj = isIntersectedWithInteractive("field"); !obj.name.empty()) {
            int fieldId = obj.GetPropertyInt("fieldId");
            saveField(fieldModel->getFieldId());
            setNewField(fieldId, fieldModel->getFieldId());
        }

        bool isAnyEnemyAlive = false;
        for (const auto & unitModel: fieldModel->getUnitModels()) {
            if (unitModel->getCharacterFaction() != CharacterFaction::Player) {
                isAnyEnemyAlive = true;
                break;
            }
        }
        if (fieldModel->getFieldId() == 3 && !isAnyEnemyAlive) {
            respawnUnits();
        }
    }

    void respawnUnits() {
        for (const auto & object: fieldModel->getLevel().GetObjects("human")) {
            std::make_shared<HumanModel>(
                    sf::Vector2f(object.rect.left, object.rect.top),
                    fieldModel
            )->addToField();
        }
        for (const auto & object: fieldModel->getLevel().GetObjects("golem")) {
            std::make_shared<GolemModel>(
                    sf::Vector2f(object.rect.left, object.rect.top),
                    fieldModel
            )->addToField();
        }
    }

    [[nodiscard]]
    const std::shared_ptr<FieldModel> & getFieldModel() const {
        return fieldModel;
    }

    [[nodiscard]]
    const std::shared_ptr<PlayerModel> & getPlayerModel() const {
        return playerModel;
    }
};


#include "utils/DependencyInjection.h"

injectAsRuntime(FieldController)