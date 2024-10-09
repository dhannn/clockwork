#include "process.hpp"
#include <string>
#include <ctime>

using namespace std;

Process::Process(int id, string name) {
    this->_name = name;
    this->_id = id;
    this->_current_line = 0;
    this->_created_at = time(nullptr);
    // TODO: Change to make max_line random
    this->_total_line = 1000;
    this->_state = READY;
}
