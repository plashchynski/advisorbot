#include "ApplicationMain.h"
#include <iostream>
#include <vector>
#include <numeric>
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include "commands/help.h"

ApplicationMain::ApplicationMain()
{

}

void ApplicationMain::init()
{
    std::string input;
    currentTime = orderBook.getEarliestTime();

    printHelp();

    while(true)
    {
        input = readUserInput();
        processUserInput(input);
    }
}

void ApplicationMain::printHelp()
{
    Commands::Help help;
    help.execute();
}

void ApplicationMain::printMarketStats()
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
        
void ApplicationMain::gotoNextTimeframe()
{
    std::cout << "Going to next time frame. " << std::endl;
    currentTime = orderBook.getNextTime(currentTime);
}
 
std::string ApplicationMain::readUserInput()
{
    std::string line;
    std::cout << "user> ";
    std::getline(std::cin, line);

    return line;
}

void ApplicationMain::processUserInput(std::string userInput)
{
    std::vector<std::string> tokens = CSVReader::tokenise(userInput, ' ');
    std::string command = tokens[0];
    std::vector<std::string> args = std::vector<std::string>(tokens.begin() + 1, tokens.end());

    if (command == "help")
    {
        Commands::Help help{};
        help.execute(args);
    }

    if (command == "exit")
    {
        exit(0);
    }

    if (command == "prod")
    {
        std::string delim = ",";
        std::vector<std::string> products = orderBook.getKnownProducts();

        std::cout << join(products, delim) << std::endl;
    }
}

std::string ApplicationMain::join(std::vector<std::string> const &strings, std::string delim)
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
