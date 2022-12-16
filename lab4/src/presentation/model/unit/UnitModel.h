#pragma once

#include <SFML/Graphics.hpp>
#include "utils/animation/AnimationManager.h"
#include "presentation/model/ObjectModel.h"


class UnitModel : public ObjectModel {
public:
    virtual void update(float time) = 0;

    virtual void setOffset(float x, float y) = 0;

    virtual void takeDamage(float damage) = 0;

    virtual ~UnitModel() = default;
};