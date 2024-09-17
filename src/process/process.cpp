#include <cstdlib>
#include <string>
#include <ctime>
#include <iostream>
#include <thread>
#include <functional>
#include "process.hpp"

Process::Process(int id, std::string name, int num_instructions) {
    this->id = id;
    this->name = name;
    this->num_instructions = num_instructions;
    this->status = QUEUED;
}

void Process::next() {
    if (num_instructions == current_instruction) {
        this->status = DONE;
        return;
    }

    this->status = IN_PROGRESS;
    this->current_instruction++;
}

Core::Core(int id) {
    core_id = id;
}

CPU::CPU(Config config) {
    this->config = config;
    int num_cpu = std::stoi(config.get("num-cpu"));

    for (int i = 0; i < num_cpu; i++) {
        cores.push_back(Core(i));
    }

    srand(time(NULL));
}

void CPU::__main_loop() {
    while (is_running) {

        scheduler.schedule();

        for (Core core: cores) {
            core.execute();
        }

        if (is_batch_spawning) {
            int num_processes = std::stoi(config.get("batch-process-freq"));
            if (cycles % num_processes == 0) {
                std::cout << cycles << "\n";
                std::cout << "PROCESS...\n";
                std::string id(std::to_string(total_processes));
                spawn("p" + id);
            }
        }
        
        cycles++;
        int delay = std::stoi(config.get("delay-per-exec"));
        _sleep(delay);
    }
}

void CPU::start() {
    is_running = true;
    main_thread = std::thread(__main_loop, std::ref(*this));
}

void CPU::stop() {
    is_running = false;
    main_thread.join();
}

void CPU::spawn(std::string name) {
    int num_ins = rand() % stoi(config.get("max-ins")) + stoi(config.get("min-ins"));
    Process process(total_processes, name, num_ins);
    ready_queue.push(process);

    total_processes++;
}


void CPU::spawn_batch() {
    is_batch_spawning = true;
}

void CPU::terminate_batch() {
    is_batch_spawning = false;
}

void CPU::print_process() {
    for (int i = 0; i < total_processes; i++) {
        Process process = ready_queue.front();
        std::cout << "Process " << process.id << ": " << process.name << std::endl;
        ready_queue.pop();
    }
}
