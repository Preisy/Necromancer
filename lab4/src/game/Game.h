#pragma once

#include "RenderWindowDI.h"

#include "utils/DependencyInjection.h"
#include "utils/ActivityManager.h"

class Game {
    Injected<ActivityManager> activityManager;

public:
    void run() {

    }
};