#include <iostream>
#include <string>
#include <memory>
#include "cpu.hpp"

using namespace std;

void CPU::initialize_kernel() {
    
}

void CPU::spawn_process(string name) {
    process_table[name] = make_shared<Process>(num_process, name);
    num_process++;
}

Process CPU::get_process(string name) {
    cout << process_table.size();
    return *process_table.at(name);
}
