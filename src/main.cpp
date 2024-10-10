#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "config/config.hpp"

int main(int argc, char const *argv[]) {
    ConfigParser parser("config.txt");
    Config config = parser.parse();
    return 0;
}
