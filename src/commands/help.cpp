#include <iostream>
#include <vector>

#include "help.h"

using Commands::Help;

Help::Help()
{

}

void Help::execute()
{
    std::cout << "advisorbot> The available commands are help, prod, min, max, avg, predict, time, step, exit. Use help <cmd> for the specified command's usage." << std::endl;
}

void Help::execute(std::vector<std::string> args)
{
    if (args.size() == 0)
        execute();
    else
    {
        // TODO: This is a bit of a hack. We should probably have a map of commands to help messages.
        std::string command = args[0];
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
}
