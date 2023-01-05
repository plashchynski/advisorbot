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
    {
        std::cout << "advisorbot> min <product> <ask|bid>: Find minimum bid or ask for product in current time step." << std::endl;
        std::cout << "advisorbot> min ETH/BTC ask -> The min ask for ETH/BTC is 1.0" << std::endl;
    }
    else if (command == "max")
    {
        std::cout << "advisorbot> max <product> <ask|bid>: Find maximum bid or ask for product in current time step." << std::endl;
        std::cout << "advisorbot> max ETH/BTC ask -> The max ask for ETH/BTC is 1.0" << std::endl;
    }
    else if (command == "avg")
    {
        std::cout << "advisorbot> avg <product> <ask|bid> <timesteps>: Compute average ask or bid for the sent product over the sent number of time steps." << std::endl;
        std::cout << "advisorbot> avg ETH/BTC bid 10 -> average ETH/BTC bid over last 10 time steps." << std::endl;
    }
    else if (command == "predict")
    {
        std::cout << "advisorbot> predict <max|min> <product> <ask|bid> : Predict max or min ask or bid for the sent product for the next time step." << std::endl;
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
        OrderBookType orderBookType = OrderBookEntry::stringToOrderBookType(orderBookTypeString);
        if (orderBookType == OrderBookType::unknown)
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
        OrderBookType orderBookType = OrderBookEntry::stringToOrderBookType(orderBookTypeString);
        if (orderBookType == OrderBookType::unknown)
        {
            std::cout << "advisorbot> Invalid order book type: " << orderBookTypeString << std::endl;
            return;
        }

        std::vector<OrderBookEntry> entries = orderBook.getOrders(orderBookType, product, currentTime);
        std::cout << "advisorbot> The max " << orderBookTypeString << " for " << product << " is " << OrderBook::getHighPrice(entries) << std::endl;
    }

    if (command == "predict")
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

    if (command == "avg")
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

    if (command == "step")
    {
        currentTime = orderBook.getNextTime(currentTime);
        std::cout << "advisorbot> now at " << currentTime << std::endl;
    }

    if (command == "time")
    {
        std::cout << "advisorbot> " << currentTime << std::endl;
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
