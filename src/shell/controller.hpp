#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "command.hpp"
#include <memory>
#include <map>
#include <vector>

using namespace std;

class Shell;
class Command;

class Controller {
    public:
        Controller(OperatingSystem& os, Shell& shell);
        void execute_command(const std::string& command_input, const std::vector<std::string>& args);
        void run();

    private:
        OperatingSystem& os;
        Shell& shell;
        std::map<std::string, std::unique_ptr<Command>> commands;
};

#endif
