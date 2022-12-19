#pragma once

#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"


class ApplicationMain
{
    public:
        ApplicationMain();
        /** Call this to start the sim */
        void init();
    private: 
        void printHelp();
        void printMarketStats();
        void gotoNextTimeframe();
        std::string readUserInput();
        void processUserInput(std::string input);

        /** join a vector of strings using a delimiter */
        std::string join(std::vector<std::string> const &strings, std::string delim);

        std::string currentTime;

	    OrderBook orderBook{"20200601.csv"};
};
