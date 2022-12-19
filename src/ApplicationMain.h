#pragma once

#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"


class ApplicationMain
{
    public:
        ApplicationMain();
        /** Call this to start the sim */
        void init();
    private: 
        void printHelp();
        void printMarketStats();
        void enterAsk();
        void enterBid();
        void printWallet();
        void gotoNextTimeframe();
        std::string readUserInput();
        void processUserInput(std::string input);

        std::string currentTime;

//        OrderBook orderBook{"20200317.csv"};
	OrderBook orderBook{"20200601.csv"};
        Wallet wallet;

};
