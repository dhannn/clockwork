#include "controller.hpp"

Controller::Controller(OperatingSystem& _os, Shell& _shell) : os(_os), shell(_shell) {
    commands["clear"] = std::make_unique<ClearCommand>();
    commands["screen"] = std::make_unique<ScreenCommand>();
    commands["exit"] = std::make_unique<ExitCommand>();
    commands["initialize"] = std::make_unique<InitializeCommand>();
    commands["process-smi"] = std::make_unique<ProcessSMICommand>();
    commands["scheduler-test"] = std::make_unique<SchedulerTestCommand>();
    commands["scheduler-stop"] = std::make_unique<SchedulerStopCommand>();
    commands["report-util"] = std::make_unique<ReportUtilCommand>();
}

void Controller::execute_command(
    const std::string& command_input, const std::vector<std::string>& args) {
            
    if (commands.find(command_input) != commands.end()) {
        commands[command_input]->execute(shell, os, args);
    } else {
        shell.display_error("Command not found: " + command_input);
    }
}

void Controller::run() {
    shell.start();
    while (shell.is_running()) {
        auto [command_input, args] = shell.accept();
        execute_command(command_input, args);
    }
}