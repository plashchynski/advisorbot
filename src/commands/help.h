#pragma once

#include <vector>
#include <string>
#include <map>

namespace Commands {
    class Help;
}

class Commands::Help
{
    public:
        Help();
        void execute();
        void execute(std::vector<std::string> args);
};
