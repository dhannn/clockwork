#include "command.hpp"
#include "shell.hpp"
#include "../cpu/cpu.hpp"

void ClearCommand::execute(Shell& shell, CPU& cpu)  {
    shell.start();
}

void ScreenCommand::execute(Shell& shell, CPU& cpu) {
    string opt = shell.args()[0];
    string arg = shell.args()[1];
    
    if (opt == "-S") {
        cpu.spawn_process(arg);
        Process process = cpu.get_process(arg);
        shell.print_process(
            process.name(), 
            process.current_line(), 
            process.total_line());
    } else if (opt == "-r") {
        try {
            Process process = cpu.get_process(arg);

            shell.print_process(
                process.name(), 
                process.current_line(), 
                process.total_line());
        } catch(const std::exception& e) {
            cerr << "Process " << arg << " cannot be found" << endl << endl;
        }
    } else {
        
    }

    shell.state = SCREEN_SINGLE;
}

void ExitCommand::execute(Shell& shell, CPU& cpu) {
    if (shell.state == MAIN_MENU) {
        shell.__is_running = false;
    } else if (shell.state == SCREEN_SINGLE) {
        shell.state = MAIN_MENU;
        shell.start();
    }
}
