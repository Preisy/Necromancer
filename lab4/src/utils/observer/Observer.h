#pragma once

#include <memory>

class Subject;

class Observer {
public:
    std::weak_ptr<Subject> observerSubject;

//    explicit Observer();

    explicit Observer(const std::weak_ptr<Subject> & subject);

    void reattach(const std::weak_ptr<Subject> & subject);

    virtual void update() = 0;

    virtual ~Observer();
};
