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
        static std::string readUserInput();

        // The setting for precision of the float values displayed in the console
        const int floatPrecision = 5;
};
