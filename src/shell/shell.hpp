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

// ansi escape codes
// Repurposed from
// https://github.com/dhannn/PG-Document-Processor/blob/new-main/code_files/.display.c

#define ESC "\x1b"
#define CLEAR() (printf("%s[2J", (ESC)))
#define MOVE(ROW, COL) (printf("%s[%d;%df", (ESC), (ROW), (COL)))
#define DOWN(ROW) (printf("%s[%db", (ESC), (ROW)))

#define FMT(X) (printf("%s[%dm", (ESC), (X)))
#define HIDE_CURS() (printf("%s[?25l", (ESC)))
#define SHOW_CURS() (printf("%s[?25h", (ESC)))
#define COLOR(X, Y) (printf("%s[%d;%dm", (ESC), (X), (Y)))

enum FORMAT {
    BOLD = 1,
    DIM,
    ITALIC,
    UNDERLINE
};

enum COLORS{
    RESET_COLOR = 0,
    BLACK_FG = 30,
    RED_FG,
    GREEN_FG,
    YELLOW_FG,
    BLUE_FG,
    MAGENTA_FG,
    CYAN_FG,
    WHITE_FG,
    DEFAULT_FG = 39,
    BLACK_BG,
    RED_BG,
    GREEN_BG,
    YELLOW_BG,
    BLUE_BG,
    MAGENTA_BG,
    CYAN_BG,
    WHITE_BG,
    DEFAULT_BG
};

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
            "a process scheduler emulator by Daniel III Ramos",
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
        void print_process(string name, int current, int total);
        void print_processes();
        void execute();
};

#endif
