#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "config/config.hpp"
#include "os/os.hpp"
#include "shell/shell.hpp"

int main(int argc, char const *argv[]) {
    Shell shell;
    OperatingSystem os;
    Controller controller(os, shell);

    controller.run();

    return 0;
}
