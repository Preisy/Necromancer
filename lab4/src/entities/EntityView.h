#pragma once

class EntityView {

public:
    virtual void draw() = 0;

    virtual ~EntityView() = default;
};
