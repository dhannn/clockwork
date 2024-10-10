#include <memory>
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

}

shared_ptr<Process> Core::release() {

    shared_ptr<Process> p = process;

    if (p == nullptr) {
        throw EmptyCoreException("Core " + to_string(id) + " is already free.");
    }

    process->preempt();

    return p;

}

void CPU::initialize_cores(int num_cores) {

    for (int i = 0; i < num_cores; i++) {
        cores.push_back(make_shared<Core>(i));
    }

}

shared_ptr<Core> CPU::get_available_core() const {

    for (const auto& core: cores) {
        if (core->is_available()) {
            return core;
        }
    }

    return nullptr;

}
