#ifndef CPU_HPP
#define CPU_HPP

#include <memory>
#include <vector>

class Process;

class CoreInUseException: public std::runtime_error {
    public:
        CoreInUseException(const std::string& message): std::runtime_error(message) {};
};

class EmptyCoreException: public std::runtime_error {
    public:
        EmptyCoreException(const std::string& message): std::runtime_error(message) {};
};


class Core {
    private:
        std::shared_ptr<Process> process;
        int id;

    public:
        Core(int _id): id(_id) {};
        int get_id() { return id; };
        std::shared_ptr<Process> get_process() { return process; };
        bool is_available() { return process == nullptr; };
        
        void assign(std::shared_ptr<Process>);
        void execute();
        std::shared_ptr<Process> release();
};

class CPU {
    private:
        int tick_num;
        std::vector<std::shared_ptr<Core>> cores;

    public:
        int tick() { return tick_num++; };
        std::vector<std::shared_ptr<Core>> get_cores() { return cores; };
        void initialize_cores(int);
        std::shared_ptr<Core> get_available_core() const;
        int get_num_available_cores() const;
        int get_num_cores() const { cores.size(); };
};

#endif
