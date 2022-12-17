#pragma once

#include "utils/animation/AnimationManager.h"

struct ObjectModel {
    [[nodiscard]]
    virtual const std::unique_ptr<AnimationManager> & getAnimationManager() = 0;

    ~ObjectModel() = default;
};