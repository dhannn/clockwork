#include <atomic>
#include <random>
#include <iostream>
#include "os.hpp"
#include "cpu.hpp"
#include "process_manager.hpp"
#include "scheduling_policy.hpp"
#include "process.hpp"

atomic<int> OperatingSystem::pid_counter;
atomic<bool> OperatingSystem::run_stress_test;

void OperatingSystem::bootstrap(shared_ptr<Config> c) {

    config = c;
    num_cores = stoi(config->get("num-cpu"));
    batch_process_frequency = stoll(config->get("batch-process-freq"));
    max_ins = stoll(config->get("max-ins"));
    min_ins = stoll(config->get("min-ins"));
    delay_per_exec = stoll(config->get("delay-per-exec"));
    scheduler_type = config->get("scheduler");
    quantum_cycles = stoll(config->get("quantum-cycles"));

    initialize_kernel();

}

void OperatingSystem::initialize_scheduler(string scheduler) {
    map<string, shared_ptr<SchedulingPolicy>> scheduling_policies;
    scheduling_policies["\"fcfs\""] = make_shared<FCFS>();
    scheduling_policies["\"rr\""] = make_shared<RoundRobinPolicy>(quantum_cycles);

    policy = scheduling_policies[scheduler];
}

void OperatingSystem::initialize_kernel() {

    cpu = make_shared<CPU>();
    cpu->initialize_cores(num_cores);
    dist = uniform_int_distribution<long long>(min_ins, max_ins);

    pid_counter = 0;
    run_stress_test = false;

    initialize_scheduler(scheduler_type);
    dispatcher = make_shared<Dispatcher>();
    scheduler = make_shared<Scheduler>(cpu, policy, dispatcher);

}

void OperatingSystem::start(){
    running = true;
    main_thread = thread(&OperatingSystem::run, this);
}

void OperatingSystem::run() {
    while (running) {
        
        // Handle stress test if enabled
        if (run_stress_test && ticks % batch_process_frequency == 0) {
            spawn_process("p" + to_string(pid_counter + 1));
        }

        // First, execute all currently running processes
        cpu->do_work();
        scheduler->schedule();
        
        ticks = cpu->tick();
        this_thread::sleep_for(chrono::milliseconds(delay_per_exec));
    }
}

void OperatingSystem::shutdown() {

    running = false;

    if (main_thread.joinable()) {
        main_thread.join();
    }
    
}

void OperatingSystem::start_stress_test() {

    lock_guard<mutex> guard(mtx);
    run_stress_test = true;

}

void OperatingSystem::stop_stress_test() {

    lock_guard<mutex> guard(mtx);
    run_stress_test = false;

}

void OperatingSystem::spawn_process(const string& name) {
    if (!scheduler) {
        throw std::runtime_error("Scheduler not initialized");
    }
    
    lock_guard<mutex> guard(mtx);
    
    pid_counter++;

    long long int instruction_count = dist(gen);
    shared_ptr<Process> process = make_shared<Process>(pid_counter, name, instruction_count);
    process_table[name] = process;
    scheduler->add_process(process);

}

vector<shared_ptr<Process>> OperatingSystem::get_processes() const {

    vector<shared_ptr<Process>> v;

    for (auto const& p: process_table) {
        v.push_back(p.second);
    }

    return v;
}


vector<shared_ptr<Process>> OperatingSystem::get_finished_processes() const {

    vector<shared_ptr<Process>> processes;

    for (auto const& process: process_table) {
        if (process.second->get_state() == TERMINATED) {
            processes.push_back(process.second);
        }
    }

    return processes;

}

vector<shared_ptr<Process>> OperatingSystem::get_running_processes() const {
    vector<shared_ptr<Process>> processes;

    for (auto const& core: cpu->get_cores()) {
        auto process = core->get_process();
        processes.push_back(process);
    }

    return processes;
}
