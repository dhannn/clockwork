#include "process.hpp"
#include <cstdlib>
#include <string>
#include <ctime>
#include <iostream>

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

ProcessManager::ProcessManager(Config config) {
    this->config = config;
    srand(time(NULL));
}

void ProcessManager::add(std::string name) {
    int num_ins = rand() % stoi(config.get("max-ins")) + stoi(config.get("min-ins"));
    processes[count] = Process(count, name, num_ins);
    count++;
}

void ProcessManager::batch(int num_processes) {
    for (int i = 0; i < num_processes; i++) {
        std::string id(std::to_string(i));
        add("p" + id);
    }
}

Process ProcessManager::next() {
    if (iter_count == count) {
        return NullProcess();
    }

    Process process = processes.at(iter_count);
    iter_count++;
    return process;
}
