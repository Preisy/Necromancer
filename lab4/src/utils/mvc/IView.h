#pragma once

class IView {
public:
    virtual void draw(float time) = 0;

    virtual ~IView() = default;
};
