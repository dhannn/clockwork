#include "process.hpp"
#include <string>

using namespace std;

Process::Process(int id, string name) {
    this->_name = name;
    this->_id = id;
    this->_current_line = 0;
    // TODO: Change to make max_line random
    this->_total_line = 1000;
    this->_state = READY;
}
