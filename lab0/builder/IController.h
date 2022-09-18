#pragma once
#include <map>
#include <functional>
#include <unordered_map>

#include "Response.h"

class IController {
public:
    virtual std::unordered_map<std::string, std::function<Response(const std::string &)>> getRequests() = 0;

    virtual ~IController() = default;
};
