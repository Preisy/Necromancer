#pragma once

#include <memory>

#include <memory>
#include "utils/activity/ActivityManager.h"
//#include "utils/observer/Observer.h"
#include "utils/mvc/IController.h"
//#include "utils/mvc/IView.h"
#include "view/level/FieldView.h"
#include "FieldController.h"

class LevelController {
    Injected<ActivityManager> activityManager;

public:
    void update(float time) {

    }

    void handleEvent(sf::Event & event) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Tab) {
                /* smth idk, maybe show inventory? */
            }
        }
    }
};
