#include <iostream>
#include <SFML/Graphics.hpp>
//#include "utils/DependencyInjection.h"
//#include "game/RenderWindowDI.h"
#include <memory>

#include "presentation/model/bullet/BulletModel.h"

#include "utils/animation/AnimationManager.h"
#include "presentation/model/FieldModel.h"

class FireballSpell : public BulletModel, public std::enable_shared_from_this<FireballSpell> {
//    sf::Vector2f coords;
//    float dx = 0.1;
//    float dy = 0.1;
//    sf::Vector2f offset = {0, 0};
//    sf::Vector2f size = {15, 15};
//
//    std::unique_ptr<AnimationManager> animationManager = std::make_unique<AnimationManager>();
//    std::shared_ptr<FieldModel> fieldModel = nullptr;
//    std::list<std::shared_ptr<BulletModel>>::iterator fieldPos;

public:
//    explicit FireballSpell(
//            float direction,
//            const std::shared_ptr<FieldModel> & fieldModel
//    ) : fieldModel(fieldModel) {
////        animationManager->loadFromXML(
////                R"(D:\C\3sem_cpp\informatics\lab4\resources\spells\fireball.xml)",
////                R"(D:\C\3sem_cpp\informatics\lab4\resources\spells\fireball.png)"
////        );
////        animationManager->rotate(direction);
//    }

    void fire() {
        auto p = shared_from_this();
//        fieldPos = fieldModel->addBullet(p);
    }


    bool collisionX() {
        return false;
    }

    bool collisionY() {
        return false;
    }

public:
    void update(float time) override {
        /* if collision with units*/
    }


    void setOffset(float x, float y) override {}

    const std::unique_ptr<AnimationManager> & getAnimationManager() override {
        return std::make_unique<AnimationManager>();
    }
};

int main() {
    auto a = std::make_shared<FireballSpell>();
    a->fire();

    return 0;
}