#include <memory>
#include <iostream>
#include "cpu.hpp"
#include "process.hpp"

using namespace std;

void Core::assign(shared_ptr<Process> p) {
    
    if (process != nullptr) {
        throw CoreInUseException("Core " + to_string(id) + " is currently in use.");
    }

    process = p;
    
}

void Core::execute() {

    if (process == nullptr) {
        throw EmptyCoreException("Core " + to_string(id) + " is empty; cannot execute.");
    }

    process->execute();

    if (process->get_state() == TERMINATED) {
        release();
    }
}

shared_ptr<Process> Core::release() {

    shared_ptr<Process> p = process;

    if (p == nullptr) {
        throw EmptyCoreException("Core " + to_string(id) + " is already free.");
    }

    process = nullptr;

    return p;

}

void CPU::initialize_cores(int num_cores) {
    for (int i = 0; i < num_cores; i++) {
        shared_ptr<Core> core = make_shared<Core>(i);
        cores.push_back(core);
    }

}

int CPU::get_num_available_cores() const {
    
    int num = 0;
    for (const auto& core: cores) {
        if (core->is_available()) {
            num++;
        }
    }

    return num;
}

shared_ptr<Core> CPU::get_available_core() const {

    for (const auto& core: cores) {
        if (core->is_available()) {
            return core;
        }
    }

    return nullptr;

}
