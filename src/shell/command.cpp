#include <iostream>
#include <memory>
#include "command.hpp"
#include "shell.hpp"
#include "../os/os.hpp"
#include "../os/process.hpp"

using namespace std;

void ClearCommand::execute(Shell& shell, OperatingSystem& OperatingSystem)  {
    shell.start();
}

void InitializeCommand::execute(Shell& shell, OperatingSystem& os) {
    ConfigParser parser("config.txt");
    shared_ptr<Config> config = parser.parse();
    cout << "Bootstrapping OS..." << endl;


    os.bootstrap(config);

    for (int i = 0; i < 20; i++) {
        string name = "process" + to_string(i);
        os.spawn_process(name);
        this_thread::sleep_for(chrono::milliseconds(500));
    }

    os.start();
    
}

void ScreenCommand::execute(Shell& shell, OperatingSystem& os) {
    string opt = shell.args()[0];
    // string arg  = shell.args()[1];
    

    switch (shell.state) {
        case MAIN_MENU:
            
            if (opt == "-ls") {
                vector<shared_ptr<Process>> processes = os.get_processes();
                vector<shared_ptr<Process>> running;
                vector<shared_ptr<Process>> done;
                
                for (auto const& p: processes) {
                    
                    if (p->get_state() == TERMINATED) {
                        done.push_back(p);
                    } else {
                        running.push_back(p);
                    }

                }

                cout << "Running: " << endl;

                for (auto const& p: running) {
                    cout << "ID: " << p->get_id() << "\tName: " << p->get_name() << "\t" << p->get_created_at() << "\t(" << p->get_program_counter() << " / " << p->get_num_instruction() << ")" << endl; 
                }

                cout << "Terminated: " << endl;

                for (auto const& p: done) {
                    cout << "ID: " << p->get_id() << "\tName: " << p->get_name() << "\t" << p->get_created_at() << "\t(" << p->get_program_counter() << " / " << p->get_num_instruction() << ")" << endl; 
                }
            }

            break;
        
        default:
            break;
    }
}

void ExitCommand::execute(Shell& shell, OperatingSystem& os) {
    if (shell.state == MAIN_MENU) {
        shell.__is_running = false;
    } else if (shell.state == SCREEN_SINGLE) {
        shell.state = MAIN_MENU;
        shell.start();
    }
}
