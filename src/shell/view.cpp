#include "view.hpp"
#include "ascii.hpp"
#include <iostream>
#include <string>

using namespace std;

void MainView::render() {
    int offset = 0;
    COLOR(YELLOW_FG, DEFAULT_BG);

    // For the offset
    string str(MAX_WIDTH, ' ');
    screenbuffer.push(str);
    screenbuffer.push(str);
    
    for (std::string line: HEADER) {
        MOVE(2 + offset, MARGIN);
        std::cout << line;
        screenbuffer.push(str);
        offset++;
    }

    std::cout << std::endl;
    COLOR(RESET_COLOR, RESET_COLOR);
}

void SingleProcessView::render() {
    
}
