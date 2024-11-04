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
    cout << endl << " >> ";
    flush(cout);
    FMT(BOLD);
    COLOR(DEFAULT_BG, BLUE_FG);
    getline(cin, input);
    COLOR(DEFAULT_BG, DEFAULT_FG);
    FMT(0);
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
    FMT(DIM);
    cout << "    " << message << endl;
    FMT(0);
}


void Shell::display_process(const std::string& name, int id, long long int current_line, long long int max_lines) {
    cout << "    "; 
    COLOR(YELLOW_BG, WHITE_FG);
    cout << "Process";
    COLOR(RESET_COLOR, RESET_COLOR);
    COLOR(YELLOW_FG, DEFAULT_BG);
    cout << " " << name << endl;
    COLOR(RESET_COLOR, RESET_COLOR);
    cout << "    "; 
    COLOR(YELLOW_BG, WHITE_FG);
    cout << "ID";
    COLOR(RESET_COLOR, RESET_COLOR);
    COLOR(YELLOW_FG, DEFAULT_BG);
    cout << " " << id << endl << endl;
    COLOR(RESET_COLOR, RESET_COLOR);
    if (current_line < max_lines) {
        cout << "    Current instruction line: "; 

        double completion_rate = double(current_line) / max_lines ;
        if (completion_rate <= 0.2) {
            COLOR(RED_FG, DEFAULT_BG);
        } else if (completion_rate <= 0.6) {
            COLOR(YELLOW_FG, DEFAULT_BG);
        } else if (completion_rate <= 0.8) {
            COLOR(BLUE_FG, DEFAULT_BG);
        } else {
            COLOR(GREEN_FG, DEFAULT_BG);
        }
        cout << current_line << endl;
        COLOR(RESET_COLOR, RESET_COLOR);
        cout << "    Lines of code: " << max_lines << endl;
    } else {
        cout << "    ";
        COLOR(GREEN_FG, GREEN_BG);
        FMT(BOLD);
        cout <<"Finished!";
        FMT(0);
        cout << endl;
    }
}

struct PCB {
    string name;
    string time_created;
    long long int num_ins;
    long long int max_ins;
};

void Shell::display_processes(
    int used_cores,
    int num_cores,
    vector<string> name, 
    vector<string> time_created,
    vector<int> core_id,
    vector<long long int> num_ins, 
    vector<long long int> max_ins) {
        vector<struct PCB> finished;
    
    cout << endl << "    CPU utilization: " << ((used_cores * 1.0) / num_cores) * 100 << "%" << endl;
    cout << "    Cores Used: " << used_cores << endl;
    cout << "    Cores Available: " << num_cores - used_cores << endl;
    cout << endl << "    --------------------------------------------------------------------------------" << endl;
    cout << "    Running processes:" << endl;


    for (int i = 0; i < name.size(); i++) {

        if (core_id[i] != -1) {
            string _n = name[i];

            if (_n.length() > 15) {
                _n = _n.substr(0, 12).append("...");
            }

            printf("    %-15s  (%s)  Core: %d  %11lld / %-11lld\n", 
                _n.c_str(), time_created[i].c_str(), core_id[i], num_ins[i], max_ins[i]);
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

    cout << endl << "    Finished processes:" << endl;
    for (PCB pcb: finished) {
        
        string _n = pcb.name;

        if (_n.length() > 15) {
            _n = _n.substr(0, 12).append("...");
        }
            printf("    %-15s (%s)  Finished  %11ld / %-11lld\n", 
                _n.c_str(), pcb.time_created.c_str(), pcb.num_ins, pcb.max_ins);
    }

    cout << endl << "    --------------------------------------------------------------------------------" << endl;
}

void Shell::display_error(const std::string& error) {
    cout << "    ";
    COLOR(RED_BG, WHITE_FG);
    cout << "ERROR";
    COLOR(RESET_COLOR, RESET_COLOR);
    cout << "  " << error << endl;
}

void Shell::clear_screen() {
    CLEAR();
    MOVE(0, 0);
}
