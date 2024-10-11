#include <atomic>
#include <random>
#include "os.hpp"
#include "cpu.hpp"
#include "process_manager.hpp"
#include "process.hpp"

atomic<int> OperatingSystem::pid_counter;
atomic<bool> OperatingSystem::run_stress_test;

void OperatingSystem::bootstrap(shared_ptr<Config> c) {

    config = c;
    num_cores = stoi(config->get("num-cpu"));
    batch_process_frequency = stoi(config->get("batch-process-freq"));
    max_ins = stoi(config->get("max-ins"));
    min_ins = stoi(config->get("min-ins"));
    
    initialize_kernel();

}

void OperatingSystem::initialize_kernel() {

    cpu->initialize_cores(num_cores);
    dist = uniform_int_distribution<>(min_ins, max_ins);

    pid_counter = 0;
    run_stress_test = false;

    shared_ptr<SchedulingPolicy> policy = (make_shared<FCFS>());
    scheduler = make_shared<Scheduler>(policy);
    dispatcher = make_shared<Dispatcher>();

}

void OperatingSystem::start(){
    running = true;
    main_thread = thread(&OperatingSystem::run, this);
}

void OperatingSystem::run() {

    while (running) {
        lock_guard<mutex> guard(mtx);  // Use lock_guard for automatic unlocking
        
        if (run_stress_test) {
            if (ticks % batch_process_frequency == 0) {
                spawn_processes(10);
            }
        }

        shared_ptr<Core> core = cpu->get_available_core();
        
        if (core == nullptr) {
            ticks = cpu->tick();
            continue;
        }

        shared_ptr<Process> process = scheduler->next();

        if (process == nullptr) {
            ticks = cpu->tick();
            continue;
        }

        dispatcher->dispatch(core, process);
        
        for (shared_ptr<Core> core: cpu->get_cores()) {
            if (!core->is_available()) {
                core->execute();
            }
        }

        ticks = cpu->tick();
    }

}

void OperatingSystem::shutdown() {

    running = false;

    if (main_thread.joinable()) {
        main_thread.join();
    }

}

void OperatingSystem::spawn_processes(int num_processes) {
    
    lock_guard<mutex> guard(mtx);
    
    for (int i = 0; i < num_processes; i++) {
        spawn_process(to_string(pid_counter));
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
    
    lock_guard<mutex> guard(mtx);
    
    pid_counter++;

    int instruction_count = dist(gen);
    process_table[name] = make_shared<Process>(pid_counter, name, instruction_count);

}
