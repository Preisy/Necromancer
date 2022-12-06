#pragma once

#include <memory>

class Subject;

class Observer {
public:
    std::weak_ptr<Subject> observerSubject;

    explicit Observer(std::weak_ptr<Subject> && subject);

    virtual void update() = 0;

    virtual ~Observer();
};
