#include "Observer.h"
#include "Subject.h"

void Subject::attach(Observer* observer) {
    observers.push_back(observer);
}

void Subject::detach(Observer* observer) {
    observers.remove(observer);
}

void Subject::notify() {
    for (auto & it: observers) {
        it->update();
    }
}

Subject::~Subject() = default;
