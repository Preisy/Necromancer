#pragma once

#include <SFML/Graphics.hpp>
#include "UnitModel.h"
#include "FieldModel.h"

#include "utils/animation/AnimationManager.h"

class PlayerModel : public UnitModel {
    float dx = 0;
    float dy = 0;
    sf::Vector2f size = {64, 32};
    sf::Vector2f coords = {0, 0};
    sf::Vector2f offset = {0, 0};
    std::shared_ptr<FieldModel> fieldModel = nullptr;
//    sf::Texture texture;
    AnimationManager animationManager;

public:
    explicit PlayerModel() {
//        texture.loadFromFile(R"(D:\C\3sem_cpp\informatics\lab4\resources\units\player_walking.png)");

        animationManager.loadFromXML(R"(D:\C\3sem_cpp\informatics\lab4\resources\units\player_walking.xml)",
                                     R"(D:\C\3sem_cpp\informatics\lab4\resources\units\player_walking.png)");
        animationManager.set("walk_s");
    }

    void addField(const std::shared_ptr<FieldModel> & fieldModel) {
        coords = fieldModel->getPlayerCoords();
        this->fieldModel = fieldModel;
        animationManager.setPosition(coords.x, coords.y);
//        offset = fieldModel->getOffset();
//        animationManager.setPosition(coords.x - offset.x - size.x / 2, coords.y - offset.y - size.y / 2);
//        animationManager.setPosition(coords.x - offset.x - size.x / 2, coords.y - offset.y - size.y / 2);
    }

    void collisionX() {
//        const auto & paths = fieldModel->getLevel().GetObjects("path");
//        for (const auto & path: paths) {
//            if (path.rect.intersects(sprite.getGlobalBounds())) {
//                std::cout << "intersects!!" << std::endl;
//            }
//            int a = 0;
//        }
    }

    float curTime;
    void update(float time) override {
        coords.x += dx * time;
        collisionX();
        coords.y += dy * time;

//        animationManager.setPosition(coords.x - offset.x - size.x / 2, coords.y - offset.y - size.y / 2);
//        animationManager.setPosition(coords.x + offset.x, coords.y - offset.y);

//        animationManager.tick(time);
        curTime = time;
    }

    void setOffset(float x, float y) override {
        this->offset.x = x;
        this->offset.y = y;
//        animationManager.setPosition(coords.x - this->offset.x - size.x / 2, coords.y - this->offset.y - size.y / 2);
        animationManager.setPosition(coords.x - offset.x, coords.y - offset.y);
//        animationManager.tick(curTime);
    }

    void fire() {

    }

    void takeDamage(float damage) override {

    }


    const sf::Vector2f & getSize() const {
        return size;
    }

    AnimationManager & getAnimationManager() override {
        return animationManager;
    }

    [[nodiscard]]
    float getDx() const {
        return dx;
    }

    void setDx(float dx) {
        PlayerModel::dx = dx;
    }

    [[nodiscard]]
    float getDy() const {
        return dy;
    }

    void setDy(float dy) {
        PlayerModel::dy = dy;
    }

    [[nodiscard]]
    const sf::Vector2f & getCoords() const {
        return coords;
    }

    void setCoords(const sf::Vector2f & coords) {
        PlayerModel::coords = coords;
    }
};
