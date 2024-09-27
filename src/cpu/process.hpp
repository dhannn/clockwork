#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <string>

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
        int _current_line;
        int _total_line;
    
    public:
        Process(int, string);

        int id() { return this->_id; }
        string name() { return this->_name; }
        ProcessState state() { return this->_state; }
        int current_line() { return this->_current_line; }
        int total_line() { return this->_total_line; }
};

#endif
