#include "ApplicationMain.h"
#include <iostream>
#include <vector>
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

    wallet.insertCurrency("BTC", 10);

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
    help.execute(std::vector<std::string>());
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
    // std::cout << "OrderBook contains :  " << orders.size() << " entries" << std::endl;
    // unsigned int bids = 0;
    // unsigned int asks = 0;
    // for (OrderBookEntry& e : orders)
    // {
    //     if (e.orderType == OrderBookType::ask)
    //     {
    //         asks ++;
    //     }
    //     if (e.orderType == OrderBookType::bid)
    //     {
    //         bids ++;
    //     }  
    // }    
    // std::cout << "OrderBook asks:  " << asks << " bids:" << bids << std::endl;

}

void ApplicationMain::enterAsk()
{
    std::cout << "Make an ask - enter the amount: product,price, amount, eg  ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "ApplicationMain::enterAsk Bad input! " << input << std::endl;
    }
    else {
        try {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2], 
                currentTime, 
                tokens[0], 
                OrderBookType::ask 
            );
            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "Wallet looks good. " << std::endl;
                orderBook.insertOrder(obe);
            }
            else {
                std::cout << "Wallet has insufficient funds . " << std::endl;
            }
        }catch (const std::exception& e)
        {
            std::cout << " ApplicationMain::enterAsk Bad input " << std::endl;
        }   
    }
}

void ApplicationMain::enterBid()
{
    std::cout << "Make an bid - enter the amount: product,price, amount, eg  ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "ApplicationMain::enterBid Bad input! " << input << std::endl;
    }
    else {
        try {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2], 
                currentTime, 
                tokens[0], 
                OrderBookType::bid 
            );
            obe.username = "simuser";

            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "Wallet looks good. " << std::endl;
                orderBook.insertOrder(obe);
            }
            else {
                std::cout << "Wallet has insufficient funds . " << std::endl;
            }
        }catch (const std::exception& e)
        {
            std::cout << " ApplicationMain::enterBid Bad input " << std::endl;
        }   
    }
}

void ApplicationMain::printWallet()
{
    std::cout << wallet.toString() << std::endl;
}
        
void ApplicationMain::gotoNextTimeframe()
{
    std::cout << "Going to next time frame. " << std::endl;
    for (std::string p : orderBook.getKnownProducts())
    {
        std::cout << "matching " << p << std::endl;
        std::vector<OrderBookEntry> sales =  orderBook.matchAsksToBids(p, currentTime);
        std::cout << "Sales: " << sales.size() << std::endl;
        for (OrderBookEntry& sale : sales)
        {
            std::cout << "Sale price: " << sale.price << " amount " << sale.amount << std::endl; 
            if (sale.username == "simuser")
            {
                // update the wallet
                wallet.processSale(sale);
            }
        }
        
    }

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

    // if (userOption == 0) // bad input
    // {
    //     std::cout << "Invalid choice. Choose 1-6" << std::endl;
    // }
    if (command == "help")
    {
        Commands::Help help{};
        help.execute(args);
    }

    if (command == "exit")
    {
        exit(0);
    }

    // if (userOption == 2) 
    // {
    //     printMarketStats();
    // }
    // if (userOption == 3) 
    // {
    //     enterAsk();
    // }
    // if (userOption == 4) 
    // {
    //     enterBid();
    // }
    // if (userOption == 5) 
    // {
    //     printWallet();
    // }
    // if (userOption == 6) 
    // {
    //     gotoNextTimeframe();
    // }       
}
