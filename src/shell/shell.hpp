#ifndef SHELL_HPP
#define SHELL_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include "command.hpp"
#include "../config/config.hpp"
#include "../cpu/cpu.hpp" 
#include "ascii.hpp"
#include "controller.hpp"

class Command;

enum ShellState {
    MAIN_MENU, 
    SCREEN_SINGLE,
    SCREEN_MULTIPLE
};

class Shell {
    private:

        const int MAX_WIDTH = 120;
        const int MAX_HEIGHT = 30;
        
        const int HEADER_TOP_PADDING = 2;
        const std::string HEADER[6] = {
            "  ___ _    ___   ___ _  ____      _____  ___ _  __",
            " / __| |  / _ \\ / __| |/ /\\ \\    / / _ \\| _ \\ |/ /",
            "| (__| |_| (_) | (__| ' <  \\ \\/\\/ / (_) |   / ' < ",
            " \\___|____\\___/ \\___|_|\\_\\  \\_/\\_/ \\___/|_|_\\_|\\_\\",
            " a process scheduler emulator by Daniel III Ramos ",
            ""
        };

        CPU cpu;
        Config config;

        std::map<std::string, std::unique_ptr<Command>> commands;
        std::string command_input;
        std::vector<std::string> __args;
        void __print_header();


    public:
        const int MARGIN = 25;
        bool __is_running = false;
        ShellState state = MAIN_MENU;
        
        Shell();
        void start();
        bool is_running();
        std::vector<std::string> args() { return __args; }
        std::vector<std::string> accept();
        void print_process(string name, string timestamp, int current, int total);
        void print_processes();
        void execute();
};

#endif
