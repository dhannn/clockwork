#ifndef SHELL_HPP
#define SHELL_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include "command.hpp"
#include "../config/config.hpp"
#include "../os/os.hpp" 
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

        void __print_header();
        bool __is_running = true;

    public:
        const int MARGIN = 25;
        ShellState state = MAIN_MENU;
        std::string current_process = "";
        
        Shell();
        void start();
        bool is_running() { return __is_running; };
        std::pair<std::string, std::vector<std::string>> accept();
        void display(const std::string& message);
        void display_process(const std::string& name, int id, long long int current_line, long long int max_lines);
        void display_processes(
            int used_cores,
            int num_cores,
            std::vector<string> name, 
            std::vector<string> time_created,
            std::vector<int> core_id,
            std::vector<long long int> num_ins, 
            std::vector<long long int> max_ins);
        void display_error(const std::string& error);
        void clear_screen();
        void stop();
};

#endif
