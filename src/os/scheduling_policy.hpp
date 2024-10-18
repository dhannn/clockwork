#ifndef POLICY_HPP
#define POLICY_HPP

#include <memory>
#include <queue>
#include "cpu.hpp"

class Process;
class Dispatcher;

class SchedulingPolicy {
    public:
        virtual std::shared_ptr<Process> next(std::shared_ptr<CPU> cpu, std::queue<std::shared_ptr<Process>>& ready_queue) const = 0;
        virtual void preempt(std::shared_ptr<CPU> cpu, std::queue<std::shared_ptr<Process>>& ready_queue, std::shared_ptr<Dispatcher> dispatcher) {};
        virtual ~SchedulingPolicy() = default;
};

class FCFS: public SchedulingPolicy {
    public:
        std::shared_ptr<Process> next(std::shared_ptr<CPU> cpu, std::queue<std::shared_ptr<Process>>& ready_queue) const override;
};

class RoundRobinPolicy: public SchedulingPolicy {
    private:
        int quantum_slice;

    public:
        RoundRobinPolicy(int quantum_slice);
        virtual void preempt(std::shared_ptr<CPU> cpu, std::queue<std::shared_ptr<Process>>& ready_queue, std::shared_ptr<Dispatcher> dispatcher) override;
        virtual std::shared_ptr<Process> next(std::shared_ptr<CPU>, std::queue<std::shared_ptr<Process>>& ready_queue) const override;
};

#endif
