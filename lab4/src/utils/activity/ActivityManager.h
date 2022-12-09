#pragma once

#include <stack>
#include <memory>
#include "Activity.h"

#include "utils/mvc/IController.h"

class ActivityManager {
    std::stack<std::unique_ptr<Activity>> activities;

public:
    void push(std::unique_ptr<Activity> && el) {
        activities.push(std::move(el));
    }

    auto top() -> decltype(auto) {
        return activities.top();
    }

    auto pop() -> decltype(auto) {
        return activities.pop();
    }

    auto empty() {
        return activities.empty();
    }

};

#include "ActivityManagerDI.h"
