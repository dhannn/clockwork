#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "shell.hpp"
#include "../cpu/cpu.hpp"
#include <iostream>

class Shell;

using namespace std;

class Command {
    public:
        Command() {};
        virtual void execute(Shell&, CPU&) = 0;
};

class ClearCommand:public Command {
    public:
        void execute (Shell&, CPU&);
};


class ScreenCommand:public Command {
    public:
        void execute (Shell&, CPU&);
};

class ExitCommand:public Command {
    public:
        void execute(Shell&, CPU&);
};

#endif
