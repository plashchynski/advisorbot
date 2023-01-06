#include <iostream>
#include <vector>

#include <boost/algorithm/string.hpp>

#include "CommandProcessor.h"

/**
 * Constructor
*/
CommandProcessor::CommandProcessor()
{
    orderBook.loadBook("20200601.csv");
    currentTime = orderBook.getEarliestTime();
}

/**
  * Prints the help message.
  */
void CommandProcessor::help()
{
    std::cout << "advisorbot> The available commands are: help, prod, min, max, avg, predict, time, step, exit." << std::endl;
    std::cout << "advisorbot> Use help <cmd> for the specified command's usage." << std::endl;
}

/**
 * Print the usage information for a specific command
*/
void CommandProcessor::help(const std::vector<std::string>& args)
{
    if (args.size() == 0)
    {
        help();
        return;
    }

    std::string command = args[0];

    // TODO: This is a bit of a hack. We should probably have a map of commands to help messages.
    if (command == "help")
        std::cout << "advisorbot> help: Prints this help message." << std::endl;
    else if (command == "prod")
        std::cout << "advisorbot> prod: Prints the products that are currently being traded." << std::endl;
    else if (command == "min")
    {
        std::cout << "advisorbot> min <product> {ask bid}: Find minimum bid or ask for product in current time step." << std::endl;
        std::cout << "advisorbot> min ETH/BTC ask -> The min ask for ETH/BTC is 1.0" << std::endl;
    }
    else if (command == "max")
    {
        std::cout << "advisorbot> max <product> {ask bid}: Find maximum bid or ask for product in current time step." << std::endl;
        std::cout << "advisorbot> max ETH/BTC ask -> The max ask for ETH/BTC is 1.0" << std::endl;
    }
    else if (command == "avg")
    {
        std::cout << "advisorbot> avg <product> {ask bid} <timesteps>: Compute average ask or bid price for the product over the specified number of time steps." << std::endl;
        std::cout << "advisorbot> avg ETH/BTC bid 10 -> average ETH/BTC bid over last 10 time steps." << std::endl;
    }
    else if (command == "predict")
    {
        std::cout << "advisorbot> predict {max min} <product> {ask bid} : Predict max or min ask or bid price for the specified product for the next time step." << std::endl;
        std::cout << "advisorbot> predict max ETH/BTC bid -> predicted max bid price for ETH/BTC for the next time step." << std::endl;
    }
    else if (command == "time")
        std::cout << "advisorbot> time: Prints the current time." << std::endl;
    else if (command == "step")
        std::cout << "advisorbot> step: Move to the next time step." << std::endl;
    else if (command == "exit")
        std::cout << "advisorbot> exit: Exit from the chat." << std::endl;
    else
        std::cout << "advisorbot> Unknown command: " << command << std::endl;
}

void CommandProcessor::terminate()
{
    std::cout << "advisorbot> Bye!" << std::endl;
    exit(0);
}

/**
 * Parse user input and execute a command if it is valid.
*/
void CommandProcessor::execute(std::string userInput)
{
    boost::algorithm::trim(userInput);

    // empty user input
    if (userInput.empty())
        return;

    std::vector<std::string> tokens;
    boost::split(tokens, userInput, [](char c){return c == ' ';});

    // empty command
    if (tokens.size() == 0)
        return;

    std::string command = tokens[0];
    std::vector<std::string> args = std::vector<std::string>(tokens.begin() + 1, tokens.end());

    if (command == "help")
        help(args);
    else if (command == "exit")
        terminate();
    else if (command == "prod")
        prod();
    else if (command == "min")
        min(args);
    else if (command == "max")
        max(args);
    else if (command == "predict")
        predict(args);
    else if (command == "avg")
        avg(args);
    else if (command == "step")
        step();
    else if (command == "time")
        time();
    else
        std::cout << "advisorbot> Unknown command: " << command << std::endl;
}

/**
 * Print the products that are currently being traded.
 */
void CommandProcessor::prod()
{
    std::vector<std::string> products = orderBook.getKnownProducts();
    std::cout << "advisorbot> " << boost::join(products, ",") << std::endl;
}

/**
 * Find minimum bid or ask for product in current time step.
*/
void CommandProcessor::min(const std::vector<std::string>& args)
{
    if (args.size() != 2)
    {
        std::cout << "advisorbot> Invalid number of arguments for min." << std::endl;
        return;
    }

    std::string product = args[0];
    std::string orderBookTypeString = args[1];
    OrderBookType orderBookType = OrderBookEntry::stringToOrderBookType(orderBookTypeString);
    if (orderBookType == OrderBookType::unknown)
    {
        std::cout << "advisorbot> Invalid order book type: " << orderBookTypeString << std::endl;
        return;
    }

    std::vector<OrderBookEntry> entries = orderBook.getOrders(orderBookType, product, currentTime);
    std::cout << "advisorbot> The min " << orderBookTypeString << " for " << product << " is " << OrderBook::getLowPrice(entries) << std::endl;
}

/**
 * Find maximum bid or ask for product in current time step.
*/
void CommandProcessor::max(const std::vector<std::string>& args)
{
    if (args.size() != 2)
    {
        std::cout << "advisorbot> Invalid number of arguments for max." << std::endl;
        return;
    }

    std::string product = args[0];
    std::string orderBookTypeString = args[1];
    OrderBookType orderBookType = OrderBookEntry::stringToOrderBookType(orderBookTypeString);
    if (orderBookType == OrderBookType::unknown)
    {
        std::cout << "advisorbot> Invalid order book type: " << orderBookTypeString << std::endl;
        return;
    }

    std::vector<OrderBookEntry> entries = orderBook.getOrders(orderBookType, product, currentTime);
    std::cout << "advisorbot> The max " << orderBookTypeString << " for " << product << " is " << OrderBook::getHighPrice(entries) << std::endl;
}

/**
 * Predict max or min ask or bid price for the specified product for the next time step.
*/
void CommandProcessor::predict(const std::vector<std::string>& args)
{
    if (args.size() != 3)
    {
        std::cout << "advisorbot> Invalid number of arguments for predict." << std::endl;
        return;
    }

    std::string maxMin = args[0];
    std::string product = args[1];
    std::string orderBookTypeString = args[2];

    if (maxMin != "min" && maxMin != "max")
    {
        std::cout << "advisorbot> Invalid max/min: " << maxMin << std::endl;
        return;
    }

    OrderBookType orderBookType = OrderBookEntry::stringToOrderBookType(orderBookTypeString);
    if (orderBookType == OrderBookType::unknown)
    {
        std::cout << "advisorbot> Invalid order book type: " << orderBookTypeString << std::endl;
        return;
    }

    double prediction = orderBook.predict(maxMin, product, orderBookType, currentTime);
    std::cout << "advisorbot> The predicted " + maxMin + " " + orderBookTypeString + " price for " << product << " is " << prediction << std::endl;
}

/**
 * Compute average ask or bid price for the product over the specified number of time steps.
*/
void CommandProcessor::avg(const std::vector<std::string>& args)
{
    if (args.size() != 3)
    {
        std::cout << "advisorbot> Invalid number of arguments for avg." << std::endl;
        return;
    }

    std::string product = args[0];
    std::string orderBookTypeString = args[1];
    std::string timestepsString = args[2];
    int timesteps;
    try
    {
        timesteps = std::stoi(timestepsString);
    }
    catch (std::invalid_argument const &e)
    {
        std::cout << "advisorbot> Invalid number of timesteps: " << timestepsString << std::endl;
        return;
    }

    if (timesteps <= 0)
    {
        std::cout << "advisorbot> Invalid number of timesteps: " << timestepsString << std::endl;
        return;
    }

    OrderBookType orderBookType;
    if (orderBookTypeString == "ask")
        orderBookType = OrderBookType::ask;
    else if (orderBookTypeString == "bid")
        orderBookType = OrderBookType::bid;
    else
    {
        std::cout << "advisorbot> Invalid order book type: " << orderBookTypeString << std::endl;
        return;
    }

    std::vector<std::string> timestamps = orderBook.getLastTimestamps(currentTime, timesteps);
    std::vector<OrderBookEntry> entries = orderBook.getOrders(orderBookType, product, timestamps);
    double average = OrderBook::getAveragePrice(entries);
    std::cout << "advisorbot> The average " << product << " " << orderBookTypeString << " price over the last " << timesteps << " was " << average << std::endl;
}

/**
 * Move to the next time step.
*/
void CommandProcessor::step()
{
    currentTime = orderBook.getNextTime(currentTime);
    std::cout << "advisorbot> now at " << currentTime << std::endl;
}

/**
 * Print the current time.
*/
void CommandProcessor::time()
{
    currentTime = orderBook.getNextTime(currentTime);
    std::cout << "advisorbot> now at " << currentTime << std::endl;
}
