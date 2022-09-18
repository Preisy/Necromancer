#include "Builder.h"
#include <iostream>
#include <sstream>
#include <algorithm>


void Builder::addController(std::unique_ptr<IController>&& controller) {
    controllers.push_back(std::move(controller));
}

void Builder::useSessionLogging(std::ofstream && out) {
    if (out.is_open()) {
//        out << "Welcome to CPP" << std::endl;
//        std::cout << "Welcome to CPP" << std::endl;
    }
    out.close();
}

Response Builder::routeRequest(const std::string & command, const std::string & args) {
    for (auto & it : requests) {
        if (it.first == command) {
            return it.second(args);
        }
    }
    return {"", BadRequest};
}


void Builder::build() {
    for (auto & it : controllers) {
        requests.merge(it->getRequests());
    }
}
