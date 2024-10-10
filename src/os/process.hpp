#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <string>
#include <stdexcept>


enum ProcessState {
    READY,
    RUNNING,
    TERMINATED
};

class InvalidProcessStateException: std::runtime_error {
    public:
        InvalidProcessStateException(const std::string& message): 
            std::runtime_error(message) {};
};

class Process {
    private:
        int pid;
        std::string name;
        int program_counter;
        int num_instructions;
        ProcessState state;

    public:
        Process() {};
        Process(const int id, const std::string& n, const int num_ins):
            pid(id),
            name(n),
            program_counter(0),
            num_instructions(num_ins),
            state(READY) {

            };

        void execute();
        void preempt();
};

#endif
