#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "shell.hpp"
#include "../os/os.hpp"
#include <iostream>

class Shell;

using namespace std;

class Command {
    public:
        virtual ~Command() = default;
        virtual void execute(Shell& shell, OperatingSystem& os, const std::vector<std::string>& args) = 0;
};

class ClearCommand:public Command {
    public:
        void execute(Shell& shell, OperatingSystem& os, const std::vector<std::string>& args) override;
};

class ProcessSMICommand:public Command {
    public:
        void execute(Shell& shell, OperatingSystem& os, const std::vector<std::string>& args) override;
};

class InitializeCommand:public Command {
    public:
        void execute(Shell& shell, OperatingSystem& os, const std::vector<std::string>& args) override;
};

class ScreenCommand:public Command {
    public:
        void execute(Shell& shell, OperatingSystem& os, const std::vector<std::string>& args) override;
};

class ExitCommand:public Command {
    public:
        void execute(Shell& shell, OperatingSystem& os, const std::vector<std::string>& args) override;
};

#endif
