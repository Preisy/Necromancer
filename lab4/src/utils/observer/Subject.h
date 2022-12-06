#pragma once

#include <list>
//#include "Observer.h"

class Observer;

class Subject {
    std::list<Observer*> observers;
public:
    Subject() = default;

    void attach(Observer* observer);

    void detach(Observer* observer);

    void notify();

    virtual ~Subject() = default;
};
