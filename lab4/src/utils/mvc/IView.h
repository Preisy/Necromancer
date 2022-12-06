#pragma once

class IView {
public:
    virtual void update(long long time) = 0;

    virtual void draw() = 0;

    virtual ~IView() = default;
};
