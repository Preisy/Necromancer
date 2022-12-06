#pragma once

#include <stack>
#include <memory>
#include "utils/mvc/IView.h"

class ActivityManager {
    std::stack<std::shared_ptr<IView>> activities;

public:
    void push(const std::shared_ptr<IView> & el) {
        activities.push(el);
    }

    void push(std::shared_ptr<IView> && el) {
        activities.push(el);
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
