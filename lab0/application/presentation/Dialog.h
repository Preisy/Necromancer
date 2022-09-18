#pragma once

#include "Builder.h"

class Dialog {
    Builder* api = nullptr;
    std::istream & in;
    std::ostream & out;
public:
    Dialog(std::istream & in, std::ostream & out);

    int run();

    void help();

    void connectToApi(Builder* builder);
};
