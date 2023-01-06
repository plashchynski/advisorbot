#pragma once

#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"


class AppMain
{
    public:
        AppMain();
        void start();

    private:
        /**
         * Terminate the program.
        */
        void terminate();

        /**
         * Print the usage information
        */
        void help();

        /**
         * Print the usage information for a specific command
        */
        void help(std::vector<std::string> args);

        std::string readUserInput();
        void processUserInput(std::string input);

        /** join a vector of strings using a delimiter */
        std::string join(std::vector<std::string> const &strings, std::string delim);

        std::string currentTime;
	    OrderBook orderBook;
};