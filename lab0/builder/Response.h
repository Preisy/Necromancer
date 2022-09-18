#pragma once
#include "ResponseCode.h"
#include <utility>

class Response {
    std::string response;
    ResponseCode responseCode;
public:
    Response(const std::string & response, ResponseCode responseCode) : response(response), responseCode(responseCode) {}
    Response(std::string && response, ResponseCode responseCode) : response(std::move(response)), responseCode(responseCode) {}

public:
    const std::string & getResponse() {
        return response;
    }

    ResponseCode getResponseCode() {
        return responseCode;
    };

    void setResponse(const std::string & response) {
        Response::response = response;
    }

    void setResponseCode(ResponseCode responseCode) {
        Response::responseCode = responseCode;
    }
};
