#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "controller.hpp"
#include "shell.hpp"
#include <iostream>

using namespace std;

class Command {
    virtual void execute(Controller& controller) {
        
    }
};

#endif
