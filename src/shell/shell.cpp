#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <memory>
#include "shell.hpp"

Shell::Shell() {
    commands["clear"] = std::make_unique<ClearCommand>();
    commands["screen"] = std::make_unique<ScreenCommand>();
    commands["exit"] = std::make_unique<ExitCommand>();


    state = MAIN_MENU;    
}

bool Shell::is_running() {
    return __is_running;
}

std::vector<std::string> Shell::accept() {

    std::cout << ">> ";

    std::string in;
    std::vector<std::string> tokens;

    std::getline(std::cin, in);
    std::stringstream ss(in);

    bool has_command = false;
    std::string word;

    __args = std::vector<std::string>();

    while (ss >> word) {
        
        if (!has_command) {
            command_input = word;
        } else {
            __args.push_back(word);
        }

        tokens.push_back(word);

        has_command = true;
    }
    
    return tokens;
}

void Shell::__print_header() {
    int offset = 0;
    COLOR(YELLOW_FG, DEFAULT_BG);
    
    for (std::string line: HEADER) {
        MOVE(2 + offset, MARGIN);
        std::cout << line;
        offset++;
    }

    std::cout << std::endl;
    COLOR(RESET_COLOR, RESET_COLOR);
}

void Shell::start() {
    __is_running = true;

    CLEAR();
    __print_header();

    while (__is_running) {
        accept();
        execute();
    }
}

void Shell::print_process(string name, int current, int total) {
    CLEAR();
    MOVE(0, 0);
    std::cout << ">> ";
    std::cout << command_input << " " << __args[0] << " " << __args[1] << std::endl << std::endl;

    std::cout << "\t" << name << "\t\t" << current << " / " << total << std::endl << std::endl;
}

void Shell::execute() {
    try {
        commands.at(command_input)->execute(*this, cpu);
    } catch(const std::exception& e) {
        std::cerr << "Command " << command_input << " not found" << '\n';
    }
    

    return;

    if (command_input == "clear") {
        start();
        return;
    }

    if (command_input == "exit") {
        __is_running = false;
        return;
    }

    std::set<std::string> valid_commands({
        "initialize",
        "screen",
        "scheduler-test",
        "scheduler-stop",
        "report-util",
    });

    if (valid_commands.find(command_input) == valid_commands.end()) {
        FMT(BOLD);
        std::cout << "   ";
        COLOR(YELLOW_BG, WHITE_FG);
        std::cout << command_input;
        FMT(0);
        COLOR(RESET_COLOR, RESET_COLOR);
        std::cout << " command is" ;
        FMT(BOLD);
        COLOR(DEFAULT_BG, RED_FG);
        std::cout << " NOT ";
        FMT(0);
        COLOR(RESET_COLOR, RESET_COLOR);
        std::cout << "recognized. Please try again." << std::endl << std::endl;

        return;
    }

    FMT(BOLD);
    std::cout << "   ";
    COLOR(YELLOW_BG, WHITE_FG);
    std::cout << command_input;
    FMT(0);
    COLOR(RESET_COLOR, RESET_COLOR);
    std::cout << " command is recognized. Doing something." << std::endl << std::endl;

    if (__args.size() != 0) {

        FMT(DIM);

        std::cout << "   Arguments recognized: " << std::endl;
        for (std::string arg: __args) {
            std::cout << "   " << arg << std::endl;
        }
        
        FMT(0);
        std::cout << std::endl;
        __args = std::vector<std::string>();
    }
}
