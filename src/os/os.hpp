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
        int batch_process_frequency;
        int max_ins;
        int min_ins;
        int delay_per_exec;
        int ticks = 0;

        random_device rd;
        mt19937 gen;
        uniform_int_distribution<> dist;

        mutex mtx;
        static atomic<int> pid_counter;
        static atomic<bool> run_stress_test;
        atomic<bool> running;
        thread main_thread;
        void run();
        void spawn_processes(int);

    public:
        OperatingSystem(): running(false), gen(rd()) {};
        void bootstrap(shared_ptr<Config>);
        void initialize_kernel();
        void start();
        void shutdown();

        void spawn_process(const string&);
        void start_stress_test();
        void stop_stress_test();

        int get_num_cores() { return cpu->get_num_cores(); };
        int get_available_cores() { return cpu->get_num_available_cores(); };

        shared_ptr<Process> get_process(string n) const { return process_table.at(n); };
        vector<shared_ptr<Process>> get_processes() const;
};

#endif
