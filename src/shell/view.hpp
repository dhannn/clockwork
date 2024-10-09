#ifndef VIEW_HPP
#define VIEW_HPP

#include <set>
#include <string>
#include <queue>
#include <memory>

using namespace std;

class View {
public:
    virtual ~View() = default;
    virtual void render() = 0;
    virtual void add_to_buffer(string str) {
        if ((int) screenbuffer.size() == MAX_HEIGHT) {
            screenbuffer.pop();
        }

        screenbuffer.pop();
    };

    virtual bool is_command_allowed(const std::string& command) const {
        return allowed_commands.find(command) != allowed_commands.end();
    }

protected:
    const int MAX_WIDTH = 120;
    const int MAX_HEIGHT = 30;
    set<string> allowed_commands;
    queue<string> screenbuffer;
    int current_lines = 0;
};

class MainView : public View {
public:
    const std::string HEADER[6] = {
        "  ___ _    ___   ___ _  ____      _____  ___ _  __",
        " / __| |  / _ \\ / __| |/ /\\ \\    / / _ \\| _ \\ |/ /",
        "| (__| |_| (_) | (__| ' <  \\ \\/\\/ / (_) |   / ' < ",
        " \\___|____\\___/ \\___|_|\\_\\  \\_/\\_/ \\___/|_|_\\_|\\_\\",
        " a process scheduler emulator by Daniel III Ramos ",
        ""
    };
    
    const int HEADER_TOP_PADDING = 2;
    const int MARGIN = 25;

    MainView() {
        allowed_commands = {"screen", "exit", "clear"};
    }
    void render() override;

    protected:
        std::set<std::string> allowed_commands;
        std::queue<std::string> screenbuffer;
        int current_lines = 0;
};

class SingleProcessView : public View {
public:
    SingleProcessView() {
        allowed_commands = {"exit", "clear"};
    }
    void render() override;
};

class ProcessTableView : public View {
public:
    ProcessTableView() {
        allowed_commands = {"exit", "clear"};
    }
    void render() override;
};

#endif 