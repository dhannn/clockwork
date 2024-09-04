#ifndef SCHEDULE_HPP
#include <map>
#include <string>
#include "process.hpp"
#include "config/config.hpp"

class ScheduleStrategy {
    public:
        virtual ~ScheduleStrategy() = default;
        virtual void schedule(std::map<int, Process>);
};

class FirstComeFirstServeStrategy: public ScheduleStrategy {};
class RoundRobinStrategy: public ScheduleStrategy {};

class Scheduler {
    private:
        Config config;
        std::map<std::string, ScheduleStrategy> schedules;

    public:
        void add_schedule(std::string, ScheduleStrategy);
        void schedule(std::string);
};
#endif
