#include "AppMain.h"
#include <iostream>
#include <vector>
#include <numeric>

#include "CommandProcessor.h"

AppMain::AppMain()
{
}

/**
 * Starts the application
 */
void AppMain::start()
{
    std::cout.precision(floatPrecision);

    std::string input;

    CommandProcessor commandProcessor{};
    commandProcessor.help();
    commandProcessor.load({"20200601.csv"});

    while(true)
    {
        input = readUserInput();

        // Ctrl+D pressed
        if (std::cin.eof())
        {
            std::cout << "exit" << std::endl;
            CommandProcessor::terminate();
        }

        commandProcessor.execute(input);
    }
}

/** 
 * Reads user input from the console
 * @return The user input
 */
std::string AppMain::readUserInput()
{
    std::string line;
    std::cout << "user> ";
    std::getline(std::cin, line);

    return line;
}
