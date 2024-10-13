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
        
        vector<string> name;
        vector<string> time_created;
        vector<int> core_id;
        vector<int> num_ins;
        vector<int> max_ins;

        auto running = os.get_running_processes();
        for (int i = 0; i < os.get_num_cores(); i++) {

            if (running[i] == nullptr) {
                continue;
            }

            Process p = *running[i];
            name.push_back(p.get_name());
            time_created.push_back(p.get_created_at());
            core_id.push_back(i);
            num_ins.push_back(p.get_program_counter());
            max_ins.push_back(p.get_num_instruction());
        }
        
        auto finished = os.get_finished_processes();

        for (auto const& p: finished) {
            name.push_back(p->get_name());
            time_created.push_back(p->get_created_at());
            core_id.push_back(-1);
            num_ins.push_back(p->get_program_counter());
            max_ins.push_back(p->get_num_instruction());
        }

        shell.display_processes(
            os.get_num_cores() - os.get_available_cores(),
            os.get_num_cores(),
            name,
            time_created,
            core_id,
            num_ins,
            max_ins
        );
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

void SchedulerTestCommand::execute(Shell& shell, OperatingSystem& os, const std::vector<std::string>& args) {
    shell.display("Spawning process every " + to_string(os.get_batch_frequency()) + " ticks...");
    os.start_stress_test();
}

void SchedulerStopCommand::execute(Shell& shell, OperatingSystem& os, const std::vector<std::string>& args) {
    os.stop_stress_test();
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
