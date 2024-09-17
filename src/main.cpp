#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "config/config.hpp"
#include "process/process.hpp"
#include "shell/shell.hpp"

int main(int argc, char const *argv[]) {
    ConfigParser parser("config.txt");
    Config config = parser.parse();
    CPU cpu(config);

    cpu.start();
    cpu.spawn_batch();
    cpu.print_process();
    cpu.terminate_batch();
    cpu.stop();
    cpu.print_process();

    std::cout << "Done";
    
    // COLOR(YELLOW_FG, DEFAULT_BG);
    // FMT(ITALIC);
    // COLOR(RESET_COLOR, RESET_COLOR);
    // std::string BUFF;

    // Shell shell = Shell();

    // shell.main();
    // COLOR(RESET_COLOR, RESET_COLOR);
    return 0;
}
