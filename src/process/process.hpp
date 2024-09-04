#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <string>
#include <map>
#include <memory>
#include "../config/config.hpp"

enum Status {
    QUEUED,
    IN_PROGRESS,
    DONE
};

class Process {
    private:
        Status status;
    
    public:
        std::string name;
        int id;
        int current_instruction = 0;
        int num_instructions;
        Process() {};
        Process(int, std::string, int);
        void next();
};

class NullProcess: public Process {
    public:
        NullProcess() {
            id = -1;
        }
};

class ProcessManager {
    private:
        Config config;
        std::map<int, Process> processes;
        int iter_count = 0;
        int count = 0;

    public:
        // ProcessManager();
        ProcessManager(Config);
        void add(std::string);
        void batch(int);
        void print();

        Process get(int);
        Process get(std::string);
        Process next();
};

#endif
