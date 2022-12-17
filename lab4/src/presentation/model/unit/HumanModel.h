#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "UnitModel.h"

#include "utils/animation/AnimationManager.h"
#include "utils/StaticDots.h"
#include "presentation/model/FieldModel.h"

class HumanModel : public UnitModel, public std::enable_shared_from_this<HumanModel> {
    std::unique_ptr<AnimationManager> animationManager = std::make_unique<AnimationManager>();
    std::unique_ptr<AnimationManager> fallAnimationManager = std::make_unique<AnimationManager>();
    sf::Vector2f coords = {0, 0};
    sf::Vector2f offset = {0, 0};
    sf::Vector2f size = {32, 50};
    std::shared_ptr<FieldModel> fieldModel;
    float health = 100;
    std::list<std::shared_ptr<UnitModel>>::iterator fieldPos;
    float damagedTime = 0;
    bool isDamaged = false;

public:
    HumanModel(
            sf::Vector2f coords,
            const std::shared_ptr<FieldModel> & fieldModel
    ) : fieldModel(fieldModel), coords(coords) {
        animationManager->loadFromXML(R"(D:\C\3sem_cpp\informatics\lab4\resources\units\human.xml)",
                                      R"(D:\C\3sem_cpp\informatics\lab4\resources\units\human.png)");
        animationManager->set("stay_s");
        animationManager->play();


//        animationManager->loadFromXML(R"(D:\C\3sem_cpp\informatics\lab4\resources\units\human_fall_down.xml)",
//                                      R"(D:\C\3sem_cpp\informatics\lab4\resources\units\human_fall_down.png)");
//        animationManager->flip()
    }

    void addToField() override {
        fieldPos = fieldModel->addUnit(shared_from_this());
    }

    void update(float time) override {
        if (isDamaged) {
            damagedTime -= time;
            if (damagedTime < 0) {
                animationManager->animList[animationManager->currentAnim].sprite.setColor(sf::Color::White);
                isDamaged = false;
            }
        }
    }

    void setOffset(float x, float y) override {
        this->offset.x = x;
        this->offset.y = y;
        animationManager->setPosition(coords.x - offset.x, coords.y - offset.y + size.y);
    }

    void takeDamage(float damage) override {
        health -= damage;
        if (health <= 0) {
            fieldModel->addDeadUnit(shared_from_this());
            fieldModel->eraseUnit(fieldPos);
            animationManager->set("fall_down");
            animationManager->play();
            animationManager->loop(false);
            animationManager->setPosition(
                animationManager->getPosition().x,
                animationManager->getPosition().y
            );
        } else {
            isDamaged = true;
            damagedTime = 500;
            animationManager->animList[animationManager->currentAnim].sprite.setColor(sf::Color(0xff3c3cff));
        }
    }

    const std::unique_ptr<AnimationManager> & getAnimationManager() override {
        return animationManager;
    }

    sf::FloatRect getFloatRect() override {
        return {coords.x, coords.y, size.x, size.y};
    }
};