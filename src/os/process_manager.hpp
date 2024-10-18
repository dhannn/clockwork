#include <memory>
#include <queue>
#include <set>
#include <stdexcept>
#include <thread>

#include "scheduling_policy.hpp"
#include "process.hpp"
#include "cpu.hpp"


class InvalidCoreProcessException: std::runtime_error {
    public:
        InvalidCoreProcessException(const std::string& message): 
            std::runtime_error(message) {};
};

class Scheduler {
    private:
        std::queue<std::shared_ptr<Process>> ready_queue;
        std::shared_ptr<SchedulingPolicy> policy;
        std::shared_ptr<CPU> cpu;
        std::set<std::shared_ptr<Process>> done;

        void finish_process(std::shared_ptr<Process>);
        std::mutex mtx;
    
    public:
        Scheduler(std::shared_ptr<CPU> c, std::shared_ptr<SchedulingPolicy> p): cpu(c), policy(p) {
        };

        void add_process(std::shared_ptr<Process>);
        std::shared_ptr<Process> next();
};

class Dispatcher {
    public:
        void preempt(std::shared_ptr<Core>);
        void dispatch(std::shared_ptr<Core>, std::shared_ptr<Process>);
};
