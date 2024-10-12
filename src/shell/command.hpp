#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "shell.hpp"
#include "../os/os.hpp"
#include <iostream>

class Shell;

using namespace std;

class Command {
    public:
        Command() {};
        virtual void execute(Shell&, OperatingSystem&) = 0;
};

class ClearCommand:public Command {
    public:
        void execute (Shell&, OperatingSystem&);
};

class InitializeCommand:public Command {
    public:
        void execute (Shell&, OperatingSystem&);
};

class ScreenCommand:public Command {
    public:
        void execute (Shell&, OperatingSystem&);
};

class ExitCommand:public Command {
    public:
        void execute(Shell&, OperatingSystem&);
};

#endif
