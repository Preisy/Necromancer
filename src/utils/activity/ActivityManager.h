#pragma once

#include <stack>
#include <memory>
#include "Activity.h"

#include "utils/mvc/IController.h"

class ActivityManager {
    std::stack<std::unique_ptr<Activity>> activities;

    bool isPoped = false;
public:
    void push(std::unique_ptr<Activity> && el) {
        if (isPoped) {
            activities.pop();
            isPoped = false;
        }
        activities.push(std::move(el));
    }

    auto top() -> decltype(auto) {
        if (isPoped) {
            activities.pop();
            isPoped = false;
        }
        return activities.top();
    }

    void pop() {
        isPoped = true;
    }

    bool empty() {
        return activities.empty();
    }

};

#include "ActivityManagerDI.h"
