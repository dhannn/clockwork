#include <iostream>
#include <string>
#include "config/config.hpp"
#include "process/process.hpp"

int main(int argc, char const *argv[]) {
    ConfigParser parser("config.txt");
    Config config = parser.parse();
    ProcessManager processManager(config);

    processManager.batch(100000); 
    Process process = processManager.next();

    while (process.id != -1) {
        std::cout << process.name << std::endl;
        process = processManager.next();
    }

    return 0;
}
