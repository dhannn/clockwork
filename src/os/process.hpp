#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <iostream>
#include <thread>
#include <string>
#include <stdexcept>
#include <ctime>
#include <memory>

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
        long long int program_counter;
        long long int num_instructions;
        ProcessState state;
        std::time_t created_at;

    public:
        Process() {};
        Process(const int id, const std::string& n, const long long int num_ins):
            pid(id),
            name(n),
            program_counter(0),
            num_instructions(num_ins),
            state(READY) {
                created_at = std::time(0);
            };

        int get_id() { return pid; };
        ProcessState get_state() { return state; }
        std::string get_name() { return name; };
        long long int get_program_counter() { return program_counter; };
        long long int get_num_instruction() { return num_instructions; };
        std::string get_created_at() { 
            struct tm* timeinfo = std::localtime(&created_at);
            char buffer[50];
            strftime(buffer, 50, "%m/%d/%Y %I:%M:%S%p", timeinfo);
            return std::string(buffer);
        };
        void execute();
        void preempt();
};

#endif
