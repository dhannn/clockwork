#include <fstream>
#include <string>
#include <map>

class Config {
    private:
        std::map<std::string, std::string> dict;

    public:
        Config();
        bool contains(std::string);
        void add(std::string, std::string);
        std::string get(std::string);
};

class ConfigParser {
    private:
        std::ifstream config_file;

    public:
        ConfigParser(std::string);
        ~ConfigParser();
        Config parse();
};