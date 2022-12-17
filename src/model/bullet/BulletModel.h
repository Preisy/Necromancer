#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "utils/animation/AnimationManager.h"
#include "/model/ObjectModel.h"


class BulletModel : public ObjectModel {
public:
    virtual void update(float time) = 0;

    virtual void setOffset(float x, float y) = 0;

    [[nodiscard]]
    const std::unique_ptr<AnimationManager> & getAnimationManager() override = 0;

    virtual ~BulletModel() = default;
};