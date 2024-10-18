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

void Scheduler::schedule() {
    policy->preempt(cpu, ready_queue, dispatcher);

    while (auto available_core = cpu->get_available_core()) {
        auto next_process = policy->next(cpu, ready_queue);
        
        if (!next_process) {
            break;  // No more processes to assign
        }
        
        dispatcher->dispatch(available_core, next_process);
    }
}

shared_ptr<Process> Scheduler::next() {
    return policy->next(cpu, ready_queue);
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

    core->get_process()->preempt();
    core->release();
}

