#pragma once

#include "IView.h"

class IController {
public:
    virtual void updateAndHandleEvents(long long time, int primaryKey) = 0;

    virtual ~IController() = default;
};
