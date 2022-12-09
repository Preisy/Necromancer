#pragma once

class UnitEntity {
public:
    virtual void update() = 0;

    virtual void fire() = 0;

    virtual void takeDamage(float damage) = 0;

    virtual ~UnitEntity() = default;
};