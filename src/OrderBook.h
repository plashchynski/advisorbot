#pragma once
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>

class OrderBook
{
    public:
        /** construct, reading a csv data file */
        OrderBook();

        /** load a csv data file */
        void loadBook(std::string filename);

        /** return vector of all know products in the dataset*/
        std::vector<std::string> getKnownProducts();

        /** return vector of Orders according to the sent filters*/
        std::vector<OrderBookEntry> getOrders(OrderBookType type,
                                              std::string product,
                                              std::string timestamp);
        std::vector<OrderBookEntry> getOrders(OrderBookType type,
                                              std::string product,
                                              std::vector<std::string> timestamps);

        /** returns the earliest time in the orderbook*/
        std::string getEarliestTime();

        /** returns the next time after the
         * sent time in the orderbook
         * If there is no next timestamp, wraps around to the start
         * */
        std::string getNextTime(std::string timestamp);
        std::vector<std::string> getLastTimestamps(std::string tillTimestamp, int number);
        double predict(std::string maxMin, std::string product, OrderBookType orderBookType, std::string currentTime);

        static double getHighPrice(std::vector<OrderBookEntry>& orders);
        static double getLowPrice(std::vector<OrderBookEntry>& orders);
        static double getAveragePrice(std::vector<OrderBookEntry>& orders);

    private:
        std::vector<OrderBookEntry> orders;
};
