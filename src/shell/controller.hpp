#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

// #include "shell.hpp"
#include "../process/process.hpp"

class Shell;

class Controller {
    public:
        Controller() {};
        void clear(Shell&, CPU);
        void initialize(Shell&, CPU);
        void add_process(Shell&, CPU);
        void get_process(Shell&, CPU);
        void list_processes(Shell&, CPU);
        void start_scheduler(Shell&, CPU);
        void stop_scheduler(Shell&, CPU);
        void exit(Shell&, CPU);
};

#endif
