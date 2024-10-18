#include <memory>
#include <queue>
#include <iostream>
#include "scheduling_policy.hpp"
#include "process_manager.hpp"
#include "process.hpp"

using namespace std;

shared_ptr<Process> FCFS::next(shared_ptr<CPU> cpu, queue<shared_ptr<Process>>& ready_queue) const {
    
    if (ready_queue.empty()) {
        return nullptr;
    }
    
    shared_ptr<Process> p = ready_queue.front();
    ready_queue.pop();

    return p;
    
}


RoundRobinPolicy::RoundRobinPolicy(int quantum_slice) {
    this->quantum_slice = quantum_slice;
}

void RoundRobinPolicy::preempt(shared_ptr<CPU> cpu, queue<shared_ptr<Process>>& ready_queue, std::shared_ptr<Dispatcher> dispatcher) {    
    
    auto cores = cpu->get_cores();
    for (auto const& core : cores) {

        auto process = core->get_process();
        if (process && (process->get_program_counter() % quantum_slice) == 0) {
            dispatcher->preempt(core);
            ready_queue.push(process);
        }

    }

}

shared_ptr<Process> RoundRobinPolicy::next(shared_ptr<CPU> cpu, queue<shared_ptr<Process>>& ready_queue) const {
    
    if (ready_queue.empty()) {
        return nullptr;
    }
    
    shared_ptr<Process> p = ready_queue.front();
    ready_queue.pop();

    return p;
    
}
