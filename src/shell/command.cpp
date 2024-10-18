#include <iostream>
#include <fstream>
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
    shell.display("Bootstrapping OS...");
    os.bootstrap(config);
    shell.display("Starting machine...");
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
        
        try {
            Process process = *os.get_process(args[1]);
            
            if (process.get_state() == TERMINATED) {
                shell.display_error("Process " + process.get_name() + " not found");
                return;
            }

            shell.clear_screen();
            shell.display_process(
                process.get_name(), 
                process.get_id(),
                process.get_program_counter(), 
                process.get_num_instruction());

            shell.current_process = args[1];
            shell.state = SCREEN_SINGLE;
        } catch(const std::out_of_range& e) {
            shell.display_error("Process " + args[1] + " not found. Spawn processes by using screen -S <process-name>");
        }
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
    shell.display("Stopping stress test...");
    os.stop_stress_test();
}

struct PCB {
    string name;
    string time_created;
    int num_ins;
    int max_ins;
};

void ReportUtilCommand::execute(Shell& shell, OperatingSystem& os, const std::vector<std::string>& args) {

    vector<string> name;
    vector<string> time_created;
    vector<int> core_id;
    vector<int> num_ins;
    vector<int> max_ins;

    ofstream file("clockwork-log.txt");
    shell.display("Saving to clockwork-log.txt");

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

    vector<struct PCB> _finished;

    file << endl << "CPU utilization: " << ((os.get_num_cores() - os.get_available_cores() * 1.0) / os.get_num_cores()) * 100 << "%" << endl;
    file << "Cores Used: " << os.get_num_cores() - os.get_available_cores() << endl;
    file << "Cores Available: " << os.get_available_cores() << endl << endl;
    file << "Running processes:" << endl;
    
    for (int i = 0; i < name.size(); i++) {

        if (core_id[i] != -1) {
                
                string _n = name[i];
                char buff[100] = "";

                if (_n.length() > 15) {
                    _n = _n.substr(0, 12).append("...");
                }

                sprintf(buff, "%-15s  (%s)  Core: %d  %8d / %-8d\n", 
                    _n.c_str(), time_created[i].c_str(), core_id[i], num_ins[i], max_ins[i]);

                file << buff;
        } else {
            struct PCB pcb {
                .name = name[i],
                .time_created = time_created[i],
                .num_ins = num_ins[i],
                .max_ins = max_ins[i]
            };

            _finished.push_back(pcb);
        }
    }
    

    file << "\nTerminated processes:" << endl;
    for (PCB pcb: _finished) {
        
        string _n = pcb.name;

        if (_n.length() > 15) {
            _n = _n.substr(0, 12).append("...");
        }

        char buff[100] = "";

        sprintf(buff, "%-15s (%s)  Finished  %8d / %-8d\n", 
            _n.c_str(), pcb.time_created.c_str(), pcb.num_ins, pcb.max_ins);

        file << buff;
    }

    file << endl;
}

void ExitCommand::execute(Shell& shell, OperatingSystem& os, const std::vector<std::string>& args) {
    if (shell.state == SCREEN_SINGLE || shell.state == SCREEN_MULTIPLE) {
        shell.state = MAIN_MENU;
        shell.start();
        return;
    }

    shell.display("Shutting down OS...");
    cout << "    ";
    this_thread::sleep_for(chrono::milliseconds(1000));
    os.shutdown();
    shell.stop();
}
