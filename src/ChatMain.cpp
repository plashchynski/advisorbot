#include "ChatMain.h"
#include <iostream>
#include <vector>
#include <numeric>
#include "OrderBookEntry.h"
#include "CSVReader.h"

ChatMain::ChatMain()
{

}

void ChatMain::start()
{
    std::string input;
    currentTime = orderBook.getEarliestTime();

    help();

    while(true)
    {
        input = readUserInput();
        processUserInput(input);
    }
}

void ChatMain::help()
{
    std::cout << "advisorbot> The available commands are: help, prod, min, max, avg, predict, time, step, exit." << std::endl;
    std::cout << "advisorbot> Use help <cmd> for the specified command's usage." << std::endl;
}

void ChatMain::help(std::vector<std::string> args)
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
        std::cout << "advisorbot> min <product>: Prints the minimum price of the specified product." << std::endl;
    else if (command == "max")
        std::cout << "advisorbot> max <product>: Prints the maximum price of the specified product." << std::endl;
    else if (command == "avg")
        std::cout << "advisorbot> avg <product>: Prints the average price of the specified product." << std::endl;
    else if (command == "predict")
        std::cout << "advisorbot> predict <product>: Prints the predicted price of the specified product." << std::endl;
    else if (command == "time")
        std::cout << "advisorbot> time: Prints the current time." << std::endl;
    else if (command == "step")
        std::cout << "advisorbot> step: Steps the simulation forward by one time unit." << std::endl;
    else if (command == "exit")
        std::cout << "advisorbot> exit: Exit from the chat." << std::endl;
    else
        std::cout << "advisorbot> Unknown command: " << command << std::endl;
}

void ChatMain::printMarketStats()
{
    for (std::string const& p : orderBook.getKnownProducts())
    {
        std::cout << "Product: " << p << std::endl;
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, 
                                                                p, currentTime);
        std::cout << "Asks seen: " << entries.size() << std::endl;
        std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
        std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << std::endl;
    }
}
        
void ChatMain::gotoNextTimeframe()
{
    std::cout << "Going to next time frame. " << std::endl;
    currentTime = orderBook.getNextTime(currentTime);
}
 
std::string ChatMain::readUserInput()
{
    std::string line;
    std::cout << "user> ";
    std::getline(std::cin, line);

    return line;
}

void ChatMain::processUserInput(std::string userInput)
{
    std::vector<std::string> tokens = CSVReader::tokenise(userInput, ' ');
    std::string command = tokens[0];
    std::vector<std::string> args = std::vector<std::string>(tokens.begin() + 1, tokens.end());

    if (command == "help")
    {
        help(args);
    }

    if (command == "exit")
    {
        exit(0);
    }

    if (command == "prod")
    {
        std::string delim = ",";
        std::vector<std::string> products = orderBook.getKnownProducts();

        std::cout << "advisorbot> " << join(products, delim) << std::endl;
    }

    if (command == "min")
    {
        if (args.size() != 2)
        {
            std::cout << "advisorbot> Invalid number of arguments for min." << std::endl;
            return;
        }

        std::string product = args[0];
        std::string orderBookTypeString = args[1];
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
        
        std::vector<OrderBookEntry> entries = orderBook.getOrders(orderBookType, product, currentTime);
        std::cout << "advisorbot> The min " << orderBookTypeString << " for " << product << " is " << OrderBook::getLowPrice(entries) << std::endl;
    }

    if (command == "max")
    {
        if (args.size() != 2)
        {
            std::cout << "advisorbot> Invalid number of arguments for max." << std::endl;
            return;
        }

        std::string product = args[0];
        std::string orderBookTypeString = args[1];
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

        std::vector<OrderBookEntry> entries = orderBook.getOrders(orderBookType, product, currentTime);
        std::cout << "advisorbot> The max " << orderBookTypeString << " for " << product << " is " << OrderBook::getHighPrice(entries) << std::endl;
    }
}

std::string ChatMain::join(std::vector<std::string> const &strings, std::string delim)
{
    if (strings.empty()) {
        return std::string();
    }
 
    return std::accumulate(strings.begin() + 1, strings.end(), strings[0],
        [&delim](std::string x, std::string y) {
            return x + delim + y;
        }
    );
}
