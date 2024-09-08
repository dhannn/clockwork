#include "controller.hpp"
#include "shell.hpp"
#include "../process/process.hpp"

void Controller::clear(Shell &shell, CPU cpu) {
    shell.main();
}

void Controller::exit(Shell &shell, CPU cpu) {
    shell.__is_running = false;
}
