#ifndef SCHEDULE_HPP
#define SCHEDULE_HPP
#include <string>
#include <queue>
#include <vector>
#include <map>
#include "../config/config.hpp"
#include "process.hpp"

class Process;

class ScheduleStrategy {
    public:
        ScheduleStrategy(Config);
        virtual void schedule(std::queue<Process>);
};

class FirstComeFirstServeStrategy: public ScheduleStrategy {};
class RoundRobinStrategy: public ScheduleStrategy {};

class Scheduler {
    private:
        Config config;
        std::map<std::string, ScheduleStrategy> schedulers;
        std::queue<Process> ready_queue;
        std::map<int, Core> cores;
        int num_cores;

    public:
        Scheduler();
        Scheduler(Config);
        void add_process(Process&);
        void schedule();
};
#endif
