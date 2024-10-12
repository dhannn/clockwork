#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "config/config.hpp"
#include "os/os.hpp"
#include "shell/shell.hpp"

int main(int argc, char const *argv[]) {
    Shell shell;
    shell.start();

    return 0;
}
