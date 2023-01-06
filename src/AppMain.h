#pragma once

#include <string>

class AppMain
{
    public:
        AppMain();
        void start();

    private:
        std::string readUserInput();
};
