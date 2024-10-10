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
        std::vector<std::shared_ptr<Core>> cores;

    public:
        void initialize_cores(int);
        std::shared_ptr<Core> get_available_core() const;
};

#endif
