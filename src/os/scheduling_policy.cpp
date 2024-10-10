#include <memory>
#include <queue>
#include "scheduling_policy.hpp"
#include "process.hpp"

using namespace std;

shared_ptr<Process> FCFS::next(std::queue<std::shared_ptr<Process>>& ready_queue) const {
    
    if (ready_queue.empty()) {
        return nullptr;
    }
    
    shared_ptr<Process> p = ready_queue.front();
    ready_queue.pop();

    return p;
    
}
