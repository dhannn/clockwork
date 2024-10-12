#include <string>
#include <iostream>
#include <thread>

#include "cpu.hpp"
#include "scheduling_policy.hpp"
#include "process_manager.hpp"
#include "process.hpp"

using namespace std;

void Scheduler::add_process(shared_ptr<Process> process) {
    ready_queue.push(process);
}

shared_ptr<Process> Scheduler::next() {
    
    if (!ready_queue.empty()) {
        shared_ptr<Process> next_process = ready_queue.front();
        ready_queue.pop();
        
        return next_process;
    }

    return nullptr;

}

void Dispatcher::dispatch(shared_ptr<Core> core, shared_ptr<Process> process) {
    
    if (!core || !process) {
        throw InvalidCoreProcessException("Core or Process is null.");
    }

    if (!core->is_available() && core->get_process() != process) {
        throw InvalidCoreProcessException("Core " + to_string(core->get_id()) + " is busy.");
    }

    core->assign(process);

}

void Dispatcher::preempt(shared_ptr<Core> core) {

    if (core->is_available()) {
        throw InvalidCoreProcessException("Core " + to_string(core->get_id()) + " has no process to preempt.");
    }

    core->release();

}

