#include <memory>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <iostream>
#include "config.hpp"

using namespace std;

Config::Config() {
    std::string keys[] = {
        "num-cpu",
        "scheduler",
        "quantum-cycles",
        "batch-process-freq",
        "min-ins",
        "max-ins",
        "delay-per-exec"
    };
    
    for (std::string key: keys){
        dict[key] = "";
    }
}

bool Config::contains(std::string key) {
    return dict.find(key) != dict.end();
}

void Config::add(std::string key, std::string val) {
    dict[key] = val;
}

std::string Config::get(std::string key) {
    if (!Config::contains(key)) {
        throw std::runtime_error("Invalid key: " + key);
    }

    return dict[key];
}

ConfigParser::ConfigParser(std::string filename) {
    config_file = std::ifstream(filename);
}

shared_ptr<Config> ConfigParser::parse() {
    std::string str = "";
    std::string prev = "";
    bool is_key = true;

    shared_ptr<Config> config = make_shared<Config>();

    cout << "Reading config file...\n";

    while(config_file >> str) {

        if (is_key) {

            cout << "Reading " << str << endl;

            if (!config->contains(str)) {
                throw std::runtime_error("Invalid key found: " + str);
            }

            if (config->get(str) != "") {
                throw std::runtime_error("Duplicate key: " + str);
            }

            is_key = false;
        } else {
            config->add(prev, str);
            is_key = true;
        }

        prev = str;
    };

    return config;
}

ConfigParser::~ConfigParser() {
    if (config_file.is_open()) {
        config_file.close();
    }
}
