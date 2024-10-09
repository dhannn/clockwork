#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <string>
#include <ctime>

using namespace std;

enum ProcessState {
    READY,
    RUNNING, 
    DONE
};

class Process {
    private:
        int _id;
        string _name;
        ProcessState _state;
        time_t _created_at;
        int _current_line;
        int _total_line;

    
    public:
        Process(int, string);
        int id() { return this->_id; }
        string name() { return _name; }
        ProcessState state() { return _state; }
        string created_at() {
            struct tm* timeinfo = localtime(&_created_at);
            char buffer[80];
            strftime(buffer, 80, "%m/%d/%Y %I:%M:%S%p", timeinfo);
            return buffer;
        };
        int current_line() { return _current_line; }
        int total_line() { return _total_line; }
};

#endif
