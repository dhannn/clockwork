#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "view.hpp"
#include "command.hpp"
#include <memory>
#include <map>

class Shell;  // Forward declaration

class Controller {
public:
    Controller(CPU& cpu, Shell& shell);
    void execute_command(const std::string& commandInput, const std::vector<std::string>& args);
    void change_view(std::unique_ptr<View> newView);
    View* get_current_view() const { return currentView.get(); }

private:
    CPU& shell;
    Shell& shell;
    std::unique_ptr<View> currentView;
    std::map<std::string, std::unique_ptr<Command>> commands;

    void initialize_commands();
};

#endif
