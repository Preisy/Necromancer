#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "utils/animation/AnimationManager.h"
#include "presentation/model/ObjectModel.h"


class BulletModel : public ObjectModel {
public:
    virtual void update(float time) = 0;

    virtual void setOffset(float x, float y) = 0;

    [[nodiscard]]
    virtual const std::unique_ptr<AnimationManager> & getAnimationManager() = 0;

    virtual ~BulletModel() = default;
};