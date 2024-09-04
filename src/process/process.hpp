#include <string>
#include <map>
#include "../config/config.hpp"

class Process {
    private:
        const int id;
        const std::string name;
        int current_instruction = 0;
        const int num_instructions;
    
    public:
        Process();
        Process(int, std::string, int);
        void next();
};

enum Status {
    QUEUED,
    IN_PROGRESS,
    DONE
};

class ProcessManager {
    private:
        std::map<int, Process> processes;
        int count = 0;

    public:
        ProcessManager();
        ProcessManager(Config);
        void add(std::string);
        void add(int);

        Process get(int);
        Process get(std::string);
        Process next();
};
