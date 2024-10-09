#ifndef CPU_HPP
#define CPU_HPP

#include <map>
#include <string>
#include <ctime>

#include "process.hpp"
#include <vector>
#include <memory>

using namespace std;

class CPU {
    private:
        map<string, shared_ptr<Process>> process_table;
        int num_process = 0;

    public:
        void initialize_kernel();
        void spawn_process(string name);
        Process* get_process(string name);
        vector<Process> get_processes();
};

#endif