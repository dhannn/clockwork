#include <iostream>
#include <string>
#include "config/config.hpp"

int main(int argc, char const *argv[]) {
    ConfigParser parser("config.txt");
    Config config = parser.parse();
    std::string str = config.get("quantum-cycles");
    std::cout << str;
    return 0;
}
