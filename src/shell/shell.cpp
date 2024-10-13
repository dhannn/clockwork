#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <memory>
#include "shell.hpp"
#include "ascii.hpp"

using namespace std;

Shell::Shell() {
    state = MAIN_MENU;    
}

pair<string, vector<string>> Shell::accept() {

    string input;
    cout << " >> ";
    getline(cin, input);
    istringstream iss(input);

    vector<string> tokens;
    string token;

    while (iss >> token) {
        tokens.push_back(token);
    }

    if (tokens.empty()) {
        return {"", {}};
    }

    string command = tokens[0];
    tokens.erase(tokens.begin());

    return { command, tokens };
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
}

void Shell::stop() {
    __is_running = false;
}

void Shell::display(const std::string& message) {
    cout << "    " << message << endl;
}


void Shell::display_process(const std::string& name, int id, int current_line, int max_lines) {
    cout << endl << "    Process: " << name << endl;
    cout << "    ID: " << id << endl << endl;
    if (current_line < max_lines) {
        cout << "    Current instruction line: " << current_line << endl;
        cout << "    Lines of code: " << max_lines << endl << endl;
    } else {
        cout << "    Finished!" << endl << endl;
    }
}

struct PCB {
    string name;
    string time_created;
    int num_ins;
    int max_ins;
};

void Shell::display_processes(
    int used_cores,
    int num_cores,
    vector<string> name, 
    vector<string> time_created,
    vector<int> core_id,
    vector<int> num_ins, 
    vector<int> max_ins) {
        vector<struct PCB> finished;

    cout << endl << "    CPU utilization: " << ((used_cores * 1.0) / num_cores) * 100 << "%" << endl;
    cout << "    Cores Used: " << used_cores << endl;
    cout << "    Cores Available: " << num_cores - used_cores << endl;
    cout << endl << "    Running processes:" << endl;
    for (int i = 0; i < name.size(); i++) {

        if (core_id[i] != -1) {
            cout << "    " <<
                name[i] << "\t(" << 
                time_created[i] << ")\t" 
                << "Core: " << core_id[i] << "\t" 
                << num_ins[i] << " / " << max_ins[i] << endl;
        } else {
            struct PCB pcb {
                .name = name[i],
                .time_created = time_created[i],
                .num_ins = num_ins[i],
                .max_ins = max_ins[i]
            };

            finished.push_back(pcb);
        }
    }

    cout << "    Terminated processes:" << endl;
    for (PCB pcb: finished) {
        cout << "    " <<
            pcb.name << "\t(" << 
            pcb.time_created << ")\t" 
            << "Finished\t" 
            << pcb.num_ins << " / " << pcb.max_ins << endl;
    }
    
    cout << endl;
}

void Shell::display_error(const std::string& error) {
    cout << "    ";
    COLOR(RED_BG, WHITE_FG);
    cout << "ERROR";
    COLOR(RESET_COLOR, RESET_COLOR);
    cout << "    " << error << endl << endl;
}

void Shell::clear_screen() {
    CLEAR();
    MOVE(0, 0);
}
