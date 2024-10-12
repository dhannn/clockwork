#include <iostream>
#include "process.hpp"

using namespace std;

void Process::execute() {

    if (state == TERMINATED) {
        throw InvalidProcessStateException(
            "Process " + name + "(" + to_string(pid) + ") has terminated and cannot be executed");
    }

    if (state == READY) {
        state = RUNNING;
    }
    
    if (state == RUNNING) {
        if (program_counter < num_instructions) {
            program_counter++;
        } else {
            state = TERMINATED;
        }

    }

}

void Process::preempt() {
    if (state != RUNNING) {
        throw InvalidProcessStateException(
            "Process " + name + "(" + to_string(pid) + ") should be running to preempt");
    }

    state = READY;
}
