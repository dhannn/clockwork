#include <iostream>
#include <memory>
#include "command.hpp"
#include "shell.hpp"
#include "../os/os.hpp"
#include "../os/process.hpp"

using namespace std;

void ClearCommand::execute(Shell& shell, OperatingSystem& os, const std::vector<std::string>& args)  {
    shell.clear_screen();

    if (shell.state == MAIN_MENU) {
        shell.start();
    } 
}

void InitializeCommand::execute(Shell& shell, OperatingSystem& os, const std::vector<std::string>& args) {
    ConfigParser parser("config.txt");
    auto config = parser.parse();
    os.bootstrap(config);
    os.start();
}

void ScreenCommand::execute(Shell& shell, OperatingSystem& os, const std::vector<std::string>& args) {
    auto const& opt = args[0];

    if (opt == "-S") {
        shell.clear_screen();
        os.spawn_process(args[1]);
        Process process = *os.get_process(args[1]);
        shell.display_process(
            process.get_name(), 
            process.get_id(),
            process.get_program_counter(), 
            process.get_num_instruction());

        shell.current_process = args[1];
        shell.state = SCREEN_SINGLE;
    } else if (opt == "-r") {
        shell.clear_screen();
        Process process = *os.get_process(args[1]);
        shell.display_process(
            process.get_name(), 
            process.get_id(),
            process.get_program_counter(), 
            process.get_num_instruction());

        shell.current_process = args[1];
        shell.state = SCREEN_SINGLE;
    } else if (opt == "-ls") {
        vector<shared_ptr<Process>> processes = os.get_processes();
        vector<string> names;
        vector<string> created_at;
        
        int available_cores = os.get_available_cores();
        int num_cores = os.get_num_cores();
        // shell.display_processes(num_cores - available_cores, num_cores,);
    } else {
        shell.display_error("Incorrect usage of screen. Usage: screen [-ls | -S <new-process-name> | -r <old-process-name>]");
    }
}

void ProcessSMICommand::execute(Shell& shell, OperatingSystem& os, const std::vector<std::string>& args)  {
    if (shell.state != SCREEN_SINGLE) {
        shell.display_error("Command process-smi cannot be accessed. Please choose a process via screen [-s <process-name> | -r <process-name>] ");
        return;
    }

    if (shell.current_process != "") {
        Process process = *os.get_process(shell.current_process);
        shell.display_process(
            process.get_name(), 
            process.get_id(),
            process.get_program_counter(), 
            process.get_num_instruction());
    } 
}

void ExitCommand::execute(Shell& shell, OperatingSystem& os, const std::vector<std::string>& args) {
    if (shell.state == SCREEN_SINGLE || shell.state == SCREEN_MULTIPLE) {
        shell.state = MAIN_MENU;
        shell.start();
        return;
    }

    os.shutdown();
    shell.stop();
}
