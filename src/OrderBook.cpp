#include <map>
#include <algorithm>
#include <vector>
#include <iostream>
#include <numeric>

#include "OrderBook.h"
#include "CSVReader.h"
#include "LinearRegression.h"

OrderBook::OrderBook()
{
    
}

/** read a csv data file */
void OrderBook::loadBook(std::string filename)
{
    orders = CSVReader::readCSV(filename);
}

/** return a vector of all know products in the dataset */
std::vector<std::string> OrderBook::getKnownProducts()
{
    std::vector<std::string> products;
    std::map<std::string,bool> prodMap;

    for (OrderBookEntry& e : orders)
    {
        prodMap[e.product] = true;
    }

    // now flatten the map to a vector of strings
    for (auto const& e : prodMap)
    {
        products.push_back(e.first);
    }

    return products;
}

/** return a vector of Orders according to the sent filters */
std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type,
                                        std::string product,
                                        std::string timestamp)
{
    std::vector<OrderBookEntry> results;
    for (OrderBookEntry& e : orders)
    {
        if (e.orderType == type && e.product == product && e.timestamp == timestamp)
        {
            results.push_back(e);
        }
    }
    return results;
}

/** return a vector of Orders for the list of timestamps */
std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type,
                                        std::string product,
                                        std::vector<std::string> timestamps)
{
    std::vector<OrderBookEntry> results;
    for (OrderBookEntry& e : orders)
    {
        if (e.orderType == type && e.product == product &&
            std::find(timestamps.begin(), timestamps.end(), e.timestamp) != timestamps.end())
        {
            results.push_back(e);
        }
    }
    return results;
}

double OrderBook::getHighPrice(std::vector<OrderBookEntry>& orders)
{
    double max = orders[0].price;
    for (OrderBookEntry& e : orders)
    {
        if (e.price > max)
            max = e.price;
    }
    return max;
}

double OrderBook::getLowPrice(std::vector<OrderBookEntry>& orders)
{
    double min = orders[0].price;
    for (OrderBookEntry& e : orders)
    {
        if (e.price < min)
            min = e.price;
    }
    return min;
}

double OrderBook::getAveragePrice(std::vector<OrderBookEntry>& orders)
{
    double sum = 0;

    for (OrderBookEntry& e : orders)
    {
        sum += e.price;
    }

    return sum / orders.size();
}

double OrderBook::predict(std::string maxMin, std::string product, OrderBookType orderBookType, std::string currentTime)
{
    std::vector<double> prices;
    std::vector<std::string> timestamps = getLastTimestamps(currentTime, 20);

    for (std::string& timestamp : timestamps)
    {
        std::vector<OrderBookEntry> orders = getOrders(orderBookType, product, timestamp);

        if (maxMin == "min") {
            prices.push_back(getLowPrice(orders));
        } else if (maxMin == "max") {
            prices.push_back(getHighPrice(orders));
        }
    }

    std::vector<double> x(prices.size());
    std::iota(x.begin(), x.end(), 1);

    LinearRegression lr;
    lr.fit(x, prices);
    double prediction = lr.predict(x.size() + 1);

    return prediction;
}

std::string OrderBook::getEarliestTime()
{
    return orders[0].timestamp;
}

std::string OrderBook::getNextTime(std::string timestamp)
{
    std::string next_timestamp = "";

    for (OrderBookEntry& e : orders)
    {
        if (e.timestamp > timestamp)
        {
            next_timestamp = e.timestamp;
            break;
        }
    }

    if (next_timestamp == "")
    {
        next_timestamp = orders[0].timestamp;
    }

    return next_timestamp;
}

/**
 * Return the timestamps from the orderbook that goes before the specified timestamp
 * including the specified timestamp.
 *
 * @param tillTimestamp till which timestamp to return
 * @param number number of timestamps to return
 * @return A vector of found timestamps
 */
std::vector<std::string> OrderBook::getLastTimestamps(std::string tillTimestamp, int number)
{
    std::string prev_timestamp = "";
    std::vector<std::string> timestamps;
    std::vector<std::string> result;

    for (OrderBookEntry& e : orders)
    {
        int size = timestamps.size();
        if (size == 0 || timestamps[size - 1] != e.timestamp)
        {
            timestamps.push_back(e.timestamp);
        }
    }

    auto itr = std::find(timestamps.begin(), timestamps.end(), tillTimestamp);
    if (itr != timestamps.cend()) {
        int tillIndex = std::distance(timestamps.begin(), itr) + 1;
        int fromIndex = std::max(0, tillIndex - number);

        result = std::vector<std::string>(timestamps.begin() + fromIndex, timestamps.begin() + tillIndex);
    }

    return result;
}
