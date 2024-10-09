#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <memory>
#include "shell.hpp"
#include "ascii.hpp"

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
    std::vector<std::string> tokens;
    std::string current_word;
    bool has_command = false;
    __args.clear();

    char c;
    while (std::cin.get(c)) {
        if (c == '\n') {
            // Process the last word if it's not empty
            if (!current_word.empty()) {
                if (!has_command) {
                    command_input = current_word;
                    has_command = true;
                } else {
                    __args.push_back(current_word);
                }
                tokens.push_back(current_word);
            }
            break;  // Exit the loop when newline is encountered
        } else if (std::isspace(c)) {
            // Process the current word when a space is encountered
            if (!current_word.empty()) {
                if (!has_command) {
                    command_input = current_word;
                    has_command = true;
                } else {
                    __args.push_back(current_word);
                }
                tokens.push_back(current_word);
                current_word.clear();
            }
        } else {
            // Add the character to the current word
            current_word += c;
            
            // Here you can add any per-character processing logic
            // For example:
            // processCharacter(c);
        }
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

void Shell::print_process(string name, string timestamp, int current, int total) {
    CLEAR();
    MOVE(0, 0);
    std::cout << ">> ";
    std::cout << command_input << " " << __args[0] << " " << __args[1] << std::endl;

    std::cout << "\t" << name << "\t\t(" << timestamp << ")" <<"\t\t" << current << " / " << total << std::endl << std::endl;
}

void Shell::execute() {
    try {
        commands.at(command_input)->execute(*this, cpu);
    } catch(const std::exception& e) {
        std::cerr << "Command " << command_input << " not found" << '\n';
    }
    

    return;
}
