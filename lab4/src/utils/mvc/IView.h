#pragma once

class IView {
public:
    virtual void draw() = 0;

    virtual ~IView() = default;
};
