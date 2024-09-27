#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "config/config.hpp"
#include "shell/shell.hpp"

int main(int argc, char const *argv[]) {
    ConfigParser parser("config.txt");
    Config config = parser.parse();
    Shell shell = Shell();
    shell.start();
    return 0;
}
