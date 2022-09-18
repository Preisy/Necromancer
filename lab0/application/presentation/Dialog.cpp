#include "Dialog.h"
#include <iostream>
#include "string"

Dialog::Dialog(std::istream & in, std::ostream & out) : in(in), out(out) {}

void Dialog::connectToApi(Builder* builder) {
    api = builder;
}

int Dialog::run() {
    if (api == nullptr) return 1;
    std::cout << "Type your command or type help" << std::endl;

    while (true) {
        std::cout << "\033[34m>>> \033[36m";

        std::string command;
        std::cin >> command;
        std::string args;
        std::getline(std::cin, args, '\n');

        std::cout << "\033[0m";

        if (command == "exit") return 0;
        if (command == "help") {
            help();
            continue;
        }

        Response response = api->routeRequest(command, args);
        if (response.getResponseCode() == Ok) {
            if (!response.getResponse().empty())
                std::cout << response.getResponse() << std::endl;
        } else {
            std::cout << "Bad Request" << std::endl;
        }
    }

}

void Dialog::help() {
    std::cout << "Examples of commands:" << std::endl;
    std::cout << "0. help" << std::endl;
    std::cout << "0. exit" << std::endl;
    std::cout << "1. add i j value" << std::endl;
    std::cout << "   adding value by index" << std::endl;
    std::cout << "2. mk" << std::endl;
    std::cout << "   make vector" << std::endl;
    std::cout << "3. print" << std::endl;
    std::cout << std::endl;
}


