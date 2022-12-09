#pragma once

#include <memory>
#include "domain/entity/LevelEntity.h"
//#include "LevelView.h"

#include <memory>
#include "utils/activity/ActivityManager.h"
#include "utils/Repository.h"
//#include "utils/observer/Observer.h"
#include "utils/mvc/IController.h"
//#include "utils/mvc/IView.h"
#include "presentation/view/CurrentFieldView.h"
#include "presentation/model/CurrentFieldModel.h"

class LevelController : public IController {
    Injected<ActivityManager> activityManager;
    Repository<int, LevelEntity> levelRepository;
    Repository<int, FieldEntity> fieldsRepository;
    Repository<int, CurrentFieldModel> currentFieldRepository;

public:
    void update(float time) override {

    }

    void handleEvent(sf::Event& event) override {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Tab) {
                /* smth idk, maybe show inventory? */
            }
        }

    }

    std::unique_ptr<CurrentFieldView> getFieldView() {
        // todo нужно сделать поиск по модели CurrentLayer

        auto it = currentFieldRepository.begin();
        if (it == currentFieldRepository.end()) {
            // getting the current level and take from this the current field
            it = currentFieldRepository.emplace().first;
            it->second->setCurrentModel(std::make_shared<FieldEntity>(1));
        }
        auto fieldModel = it->second;

        return std::make_unique<CurrentFieldView>(fieldModel);

//        int levelId = 1;
//        auto it = levelRepository.find(levelId);
//        if (it == levelRepository.end()) {
//            it = levelRepository.emplace(levelId).first;
//            auto fieldModels = it->second->getFields();
//            for (const auto & jt : fieldModels)
//                fieldsRepository.insert(jt);
//        }
//        auto levelModel = (*it).second;
//
//        auto levelView = new LevelView(levelModel);
//
//        return std::unique_ptr<LevelView>(levelView);
    }
};
