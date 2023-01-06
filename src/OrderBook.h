/**
 * This class represents an order book
*/

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

        /**
         * Returns the earliest timestamp in the orderbook
        */
        std::string getEarliestTime();

        /**
         * Returns the next time after the specified timestamp
         * If there is no next timestamp, wraps around to the start
         * */
        std::string getNextTime(std::string timestamp);

        /**
         * Return the timestamps from the orderbook that goes before the specified timestamp
         * including the specified timestamp.
         *
         * @param tillTimestamp till which timestamp to return
         * @param number number of timestamps to return
         * @return A vector of found timestamps
         */
        std::vector<std::string> getLastTimestamps(std::string tillTimestamp, int number);

        /**
         * Returns the predicted price for the next timeframe after the specified timestamp
        */
        double predict(std::string maxMin, std::string product, OrderBookType orderBookType, std::string currentTime);

        /**
         * Returns the highest price among provided orders
        */
        static double getHighPrice(std::vector<OrderBookEntry>& orders);

        /**
         * Returns the lowest price among provided orders
        */
        static double getLowPrice(std::vector<OrderBookEntry>& orders);

        /**
         * Returns the average price among provided orders
        */
        static double getAveragePrice(std::vector<OrderBookEntry>& orders);

    private:
        std::vector<OrderBookEntry> orders;
};
