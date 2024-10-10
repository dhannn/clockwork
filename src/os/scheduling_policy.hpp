#include <memory>
#include <queue>

class Process;

class SchedulingPolicy {
    public:
        virtual std::shared_ptr<Process> next(std::queue<std::shared_ptr<Process>>& ready_queue) const = 0;
        virtual ~SchedulingPolicy() = default;
};

class FCFS: SchedulingPolicy {
    public:
        std::shared_ptr<Process> next(std::queue<std::shared_ptr<Process>>& ready_queue) const override;
};