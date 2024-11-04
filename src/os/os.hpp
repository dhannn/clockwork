#ifndef OS_HPP
#define OS_HPP

#include <memory>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <thread>
#include <atomic>
#include <random>

#include "../config/config.hpp"
#include "scheduling_policy.hpp"
#include "cpu.hpp"

using namespace std;

class Scheduler;
class Dispatcher;
class Process;

class OperatingSystem {
    private:
        shared_ptr<Config> config;
        shared_ptr<Scheduler> scheduler;
        shared_ptr<Dispatcher> dispatcher;
        shared_ptr<CPU> cpu;
        map<string, shared_ptr<Process>> process_table;
        
        int num_cores;
        long long int batch_process_frequency;
        long long int max_ins;
        long long int min_ins;
        long long int delay_per_exec;
        long long int ticks = 0;
        long long int quantum_cycles;
        string scheduler_type;

        shared_ptr<SchedulingPolicy> policy;

        random_device rd;
        mt19937 gen;
        uniform_int_distribution<long long> dist;

        mutex mtx;
        static atomic<int> pid_counter;
        static atomic<bool> run_stress_test;
        atomic<bool> running;
        thread main_thread;
        set<shared_ptr<Process>> finished;
        void run();
        void initialize_scheduler(string scheduler);

    public:
        OperatingSystem(): running(false), gen(rd()) {};
        void bootstrap(shared_ptr<Config>);
        void initialize_kernel();
        void start();
        void shutdown();

        bool is_running() { return running; };

        void spawn_process(const string&);
        void start_stress_test();
        void stop_stress_test();

        int get_batch_frequency() {
            return batch_process_frequency;
        }
        int get_num_cores() { return cpu->get_num_cores(); };
        int get_available_cores() { return cpu->get_num_available_cores(); };

        shared_ptr<Process> get_process(string n) const { return process_table.at(n); };
        vector<shared_ptr<Process>> get_processes() const;
        vector<shared_ptr<Process>> get_running_processes() const;
        vector<shared_ptr<Process>> get_finished_processes() const;
};

#endif
