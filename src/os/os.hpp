#include <queue>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <thread>

#include "config/config.hpp"

using namespace std;

class Scheduler;
class Dispatcher;
class Process;

class OperatingSystem {
    private:
        shared_ptr<Config> config;
        unique_ptr<Scheduler> scheduler;
        unique_ptr<Dispatcher> dispatcher;
        map<string, Process> process_table;
        static const int pid_counter = 0;

        thread main_thread;

        void run();

    public:
        void bootstrap(shared_ptr<Config>);
        void initialize_kernel();
        void start_services();
        void start();
        void shutdown();

        void spawn_process(const string&);
        void remove_process(const string&); 
        void spawn_processes(int);

        shared_ptr<Process> get_process(string) const;
        vector<shared_ptr<Process>> get_processes() const;
};

class Dispatcher {
    private:

    public:
        void preempt(shared_ptr<Core>);
        void dispatch(shared_ptr<Core>, shared_ptr<Process>);
};

class Core {
    private:
        shared_ptr<Process> process;

    public:
        void assign(shared_ptr<Process>);
        void execute();
        shared_ptr<Process> free();
        shared_ptr<Process> get_process();
        bool is_available();
};

class CPU {
    private:
        vector<shared_ptr<Core>> cores;

    public:
        void initialize_cores(int);
        shared_ptr<Core> get_available_core();
};

class SchedulingPolicy {
    private:
        virtual shared_ptr<Process> next() const = 0;
};

class Scheduler {
    private:
        queue<shared_ptr<Process>> ready_queue;
        unique_ptr<SchedulingPolicy> policy;
        set<shared_ptr<Process>> done;
        void finish_process(shared_ptr<Process>);
    
    public:
        void add_process(shared_ptr<Process>);
        shared_ptr<Process> next();
};
