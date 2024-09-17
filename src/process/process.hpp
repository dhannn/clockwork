#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <string>
#include <vector>
#include <set>
#include <memory>
#include <thread>
#include <queue>
#include "../config/config.hpp"
#include "schedule.hpp"

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

class Core {
    private:
        int core_id;
        Process& current_process = NullProcess();

    public:
        Core(int);
        bool is_busy(Process&);
        void assign_process(Process&);
        void execute();
};

class CPU {
    private:
        Config config;
        int total_processes = 0;
        bool is_running = false;
        bool is_batch_spawning = false;
        std::thread main_thread;
        std::vector<Core> cores;
        std::set<Process> finished_processes;
        Scheduler scheduler;
        
        
        int cycles = 0;
        std::queue<Process> ready_queue;
        void __main_loop();
        void __spawn_batch();

    public:
        CPU() {};
        CPU(Config);
        void start();
        void stop();
        
        void spawn(std::string);
        void spawn_batch();
        void terminate_batch();

        void print_process();
};

#endif
