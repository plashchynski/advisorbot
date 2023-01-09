#include <iostream>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/range/adaptor/map.hpp>
#include <boost/range/algorithm/copy.hpp>

#include "CommandProcessor.h"

/**
 * Constructor
*/
CommandProcessor::CommandProcessor()
{
}

/**
  * Prints the help message.
*/
void CommandProcessor::help()
{
    std::vector<std::string> commands;

    /*
        The keys of the helpMessages map serve as the list of available commands.
        Copy the keys from the std::map into the vector:
    */
    boost::copy(helpMessages | boost::adaptors::map_keys, std::back_inserter(commands));

    std::cout << promt << "The available commands are: " << boost::join(commands, ", ") << "." << std::endl;
    std::cout << promt << "Use help <cmd> for the specified command's usage." << std::endl;
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

    // If the command is not found in the helpMessages map, print an error message
    if (helpMessages.find(command) == helpMessages.end())
    {
        std::cout << promt << "Unknown command: " << command << std::endl;
        return;
    }

    std::cout << helpMessages[command] << std::endl;
}

/**
 * Exit the application.
*/
void CommandProcessor::terminate()
{
    std::cout << promt << "Bye!" << std::endl;
    exit(0);
}

/**
 * Parse user input and execute a command if it is valid.
*/
void CommandProcessor::execute(std::string userInput)
{
    // remove leading and trailing whitespace
    boost::algorithm::trim(userInput);

    // empty user input
    if (userInput.empty())
        return;

    // split the user input into tokens
    std::vector<std::string> tokens;
    // The boost::token_compress_on is used to ignore any consecutive whitespaces
    boost::split(tokens, userInput, boost::is_any_of("\t "), boost::token_compress_on);

    // empty command? return
    if (tokens.size() == 0)
        return;

    // The first token is the command, the rest are the arguments
    std::string command = tokens[0];
    std::vector<std::string> args = std::vector<std::string>(tokens.begin() + 1, tokens.end());

    // call the appropriate method for the command
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
    else if (command == "back")
        back();
    else if (command == "time")
        time();
    else if (command == "load")
        load(args);
    else if (command == "volume")
        volume(args);
    else
        std::cout << promt << "Unknown command: " << command << std::endl;
}

/**
 * Print the products that are currently being traded.
 */
void CommandProcessor::prod()
{
    std::vector<std::string> products = orderBook.getKnownProducts();
    std::cout << promt << boost::join(products, ",") << std::endl;
}

/**
 * Find minimum bid or ask for product in current time step.
*/
void CommandProcessor::min(const std::vector<std::string>& args)
{
    if (args.size() != 2)
    {
        std::cout << promt << "Invalid number of arguments for min." << std::endl;
        return;
    }

    std::string product = args[0];
    std::string orderBookTypeString = args[1];
    OrderBookType orderBookType = OrderBookEntry::stringToOrderBookType(orderBookTypeString);
    if (orderBookType == OrderBookType::unknown)
    {
        std::cout << promt << "Invalid order book type: " << orderBookTypeString << std::endl;
        return;
    }

    std::vector<OrderBookEntry> entries = orderBook.getOrders(orderBookType, product, currentTime);
    if (entries.empty())
    {
        std::cout << promt << "No orders found matching the criteria." << std::endl;
        return;
    }
    std::cout << promt << "The min " << orderBookTypeString << " for " << product << " is " << OrderBook::getLowPrice(entries) << std::endl;
}

/**
 * Find maximum bid or ask for product in current time step.
*/
void CommandProcessor::max(const std::vector<std::string>& args)
{
    if (args.size() != 2)
    {
        std::cout << promt << "Invalid number of arguments for max." << std::endl;
        return;
    }

    std::string product = args[0];
    std::string orderBookTypeString = args[1];
    OrderBookType orderBookType = OrderBookEntry::stringToOrderBookType(orderBookTypeString);
    if (orderBookType == OrderBookType::unknown)
    {
        std::cout << promt << "Invalid order book type: " << orderBookTypeString << std::endl;
        return;
    }

    std::vector<OrderBookEntry> entries = orderBook.getOrders(orderBookType, product, currentTime);
    if (entries.empty())
    {
        std::cout << promt << "No orders found matching the criteria." << std::endl;
        return;
    }
    std::cout << promt << "The max " << orderBookTypeString << " for " << product << " is " << OrderBook::getHighPrice(entries) << std::endl;
}

/**
 * Predict max or min ask or bid price for the specified product for the next time step.
*/
void CommandProcessor::predict(const std::vector<std::string>& args)
{
    if (args.size() != 3)
    {
        std::cout << promt << "Invalid number of arguments for predict." << std::endl;
        return;
    }

    std::string maxMin = args[0];
    std::string product = args[1];
    std::string orderBookTypeString = args[2];

    if (maxMin != "min" && maxMin != "max")
    {
        std::cout << promt << "Invalid max/min: " << maxMin << std::endl;
        return;
    }

    OrderBookType orderBookType = OrderBookEntry::stringToOrderBookType(orderBookTypeString);
    if (orderBookType == OrderBookType::unknown)
    {
        std::cout << promt << "Invalid order book type: " << orderBookTypeString << std::endl;
        return;
    }

    double prediction;
    try
    {
        prediction = orderBook.predict(maxMin, product, orderBookType, currentTime);
    } catch (std::runtime_error const &e)
    {
        std::cout << promt << "Prediction error: " << e.what() << std::endl;
        return;
    }
    std::cout << promt << "The predicted " + maxMin + " " + orderBookTypeString + " price for " << product << " is " << prediction << std::endl;
}

/**
 * Compute average ask or bid price for the product over the specified number of time steps.
*/
void CommandProcessor::avg(const std::vector<std::string>& args)
{
    if (args.size() != 3)
    {
        std::cout << promt << "Invalid number of arguments for avg." << std::endl;
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
        std::cout << promt << "Invalid number of timesteps: " << timestepsString << std::endl;
        return;
    }

    if (timesteps <= 0)
    {
        std::cout << promt << "Invalid number of timesteps: " << timestepsString << std::endl;
        return;
    }

    OrderBookType orderBookType = OrderBookEntry::stringToOrderBookType(orderBookTypeString);
    if (orderBookType == OrderBookType::unknown)
    {
        std::cout << promt << "Invalid order book type: " << orderBookTypeString << std::endl;
        return;
    }

    std::vector<std::string> timestamps = orderBook.getLastTimestamps(currentTime, timesteps);
    std::vector<OrderBookEntry> entries = orderBook.getOrders(orderBookType, product, timestamps);
    if (entries.empty())
    {
        std::cout << promt << "No orders found matching the criteria." << std::endl;
        return;
    }
    double average = OrderBook::getAveragePrice(entries);
    std::cout << promt << "The average " << product << " " << orderBookTypeString << " price over the last " << timesteps << " was " << average << std::endl;
}

void CommandProcessor::volume(const std::vector<std::string>& args)
{
    if (args.size() != 3)
    {
        std::cout << promt << "Invalid number of arguments for avg." << std::endl;
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
        std::cout << promt << "Invalid number of timesteps: " << timestepsString << std::endl;
        return;
    }

    if (timesteps <= 0)
    {
        std::cout << promt << "Invalid number of timesteps: " << timestepsString << std::endl;
        return;
    }

    OrderBookType orderBookType = OrderBookEntry::stringToOrderBookType(orderBookTypeString);
    if (orderBookType == OrderBookType::unknown)
    {
        std::cout << promt << "Invalid order book type: " << orderBookTypeString << std::endl;
        return;
    }

    std::vector<std::string> timestamps = orderBook.getLastTimestamps(currentTime, timesteps);
    std::vector<OrderBookEntry> entries = orderBook.getOrders(orderBookType, product, timestamps);
    if (entries.empty())
    {
        std::cout << promt << "No orders found matching the criteria." << std::endl;
        return;
    }
    double average = OrderBook::getTotalVolume(entries);
    std::cout << promt << "The volume of " << product << " " << orderBookTypeString << " over the last " << timesteps << " was " << average << std::endl;
}

/**
 * Move to the next time step.
*/
void CommandProcessor::step()
{
    currentTime = orderBook.getNextTime(currentTime);
    time();
}

/**
 * Move back to the previous time step.
*/
void CommandProcessor::back()
{
    // Get the last two time steps.
    std::vector<std::string> previousTimeStep = orderBook.getLastTimestamps(currentTime, 2);

    if (previousTimeStep.size() < 2)
        std::cout << promt << "This is the first time stemp in the book." << std::endl;
    else
        currentTime = previousTimeStep[0];

    time();
}

/**
 * Print the current time.
*/
void CommandProcessor::time()
{
    std::cout << promt << "now at " << currentTime << std::endl;
}

/**
 * Load the order book from the specified file.
*/
void CommandProcessor::load(const std::vector<std::string>& args)
{
    if (args.size() != 1)
    {
        std::cout << promt << "Invalid number of arguments for load." << std::endl;
        return;
    }

    std::cout << promt << "Loading an order book from " << args[0] << std::endl;
    std::cout << promt << "Please wait... " << std::endl;

    std::string filename = args[0];

    try
    {
        orderBook.loadBook(filename);
    } catch (std::exception& e)
    {
        std::cout << promt << "Error loading the order book: " << e.what() << std::endl;
        return;
    }

    currentTime = orderBook.getEarliestTime();
    std::cout << promt << "Loaded " << orderBook.getNumberOfOrders() << " entries from order book " << filename << std::endl;
}
