#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "config/config.hpp"
#include "os/os.hpp"

int main(int argc, char const *argv[]) {
    ConfigParser parser("config.txt");
    Config config = parser.parse();

    OperatingSystem os;
    os.bootstrap(make_shared<Config>(config));
    os.start();

    os.shutdown();
    return 0;
}
