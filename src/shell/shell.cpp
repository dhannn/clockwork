#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include "shell.hpp"

Shell::Shell() {
    __is_running = true;
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

    while (ss >> word) {
        
        if (!has_command) {
            command = word;
        } else {
            args.push_back(word);
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

void Shell::main() {
    CLEAR();
    __print_header();

    while (__is_running) {
        accept();
        execute();
    }
}

void Shell::execute() {
    if (command == "clear") {
        controller.clear(*this, CPU());
        return;
    }

    if (command == "exit") {
        controller.exit(*this, CPU());
        return;
    }

    std::set<std::string> valid_commands({
        "initialize",
        "screen",
        "scheduler-test",
        "scheduler-stop",
        "report-util",
    });

    if (valid_commands.find(command) == valid_commands.end()) {
        FMT(BOLD);
        std::cout << "   ";
        COLOR(YELLOW_BG, WHITE_FG);
        std::cout << command;
        FMT(0);
        COLOR(RESET_COLOR, RESET_COLOR);
        std::cout << " command is" ;
        COLOR(DEFAULT_BG, RED_FG);
        FMT(BOLD);
        std::cout << " NOT ";
        FMT(0);
        COLOR(RESET_COLOR, RESET_COLOR);
        std::cout << "recognized. Doing something." << std::endl << std::endl;

        return;
    }

    FMT(BOLD);
    std::cout << "   ";
    COLOR(YELLOW_BG, WHITE_FG);
    std::cout << command;
    FMT(0);
    COLOR(RESET_COLOR, RESET_COLOR);
    std::cout << " command is recognized. Doing something." << std::endl << std::endl;

    if (args.size() != 0) {

        FMT(DIM);

        std::cout << "   Arguments recognized: " << std::endl;
        for (std::string arg: args) {
            std::cout << "   " << arg << std::endl;
        }
        
        FMT(0);
        std::cout << std::endl;
        args = std::vector<std::string>();
    }
}
