#pragma once

#include <vector>
#include <fstream>
#include <memory>
#include "IController.h"
#include <unordered_map>
#include <functional>


class Builder {
    std::vector<std::unique_ptr<IController>> controllers;
    std::unordered_map<std::string, std::function<Response(const std::string &)>> requests;

    std::ofstream out;
    bool logging = false;


public:
    Builder() = default;

    void addController(std::unique_ptr<IController>&& controller);

    void useSessionLogging(std::ofstream && out);

    void build();

    Response routeRequest(const std::string & command, const std::string & args);
};