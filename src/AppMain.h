#pragma once

#include <string>

class AppMain
{
    public:
        AppMain();

        /**
         * Starts the application
         */
        void start();

    private:
        /** 
         * Reads user input from the console
         * @return The user input
         */
        std::string readUserInput();
};
