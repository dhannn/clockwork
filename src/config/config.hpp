#include <fstream>
#include <string>

class ConfigParser {
    private:
        std::ifstream configFile;

    public:
        ConfigParser(std::string);
        ~ConfigParser();
        Config parse();
};

class Config {
    public:
        const int num_cpu;
        const std::string scheduler;
        const int quantum_cycle;
        const int batch_process_freq;
        const int min_ins;
        const int max_ins;
        Config(int, std::string, int, int, int, int);
};
