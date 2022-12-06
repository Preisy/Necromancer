#include <memory>
#include "Observer.h"
#include "Subject.h"


Observer::Observer(std::weak_ptr<Subject> && subject) : observerSubject(subject) {
    if (auto p = observerSubject.lock())
        p->attach(this);
}

Observer::~Observer() {
    if (auto p = observerSubject.lock())
        p->detach(this);
}


