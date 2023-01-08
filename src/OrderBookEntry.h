/**
 * This class represents an entry in the order book
*/
#pragma once

#include <string>

enum class OrderBookType{bid, ask, unknown};

struct OrderBookEntry {
    double price;
    double amount;
    std::string timestamp;
    std::string product;
    OrderBookType orderType;

    /**
     * Converts a string to an OrderBookType
    */
    static OrderBookType stringToOrderBookType(std::string string)
    {
        if (string == "ask")
            return OrderBookType::ask;

        if (string == "bid")
            return OrderBookType::bid;

        return OrderBookType::unknown;
    }
};
