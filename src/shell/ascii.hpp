#ifndef ASCII_HPP
#define ASCII_HPP

// ansi escape codes
// Repurposed from
// https://github.com/dhannn/PG-Document-Processor/blob/new-main/code_files/.display.c

#include <iostream>

#define ESC "\x1b"
#define CLEAR() (printf("%s[2J", (ESC)))
#define MOVE(ROW, COL) (printf("%s[%d;%df", (ESC), (ROW), (COL)))
#define DOWN(ROW) (printf("%s[%db", (ESC), (ROW)))

#define FMT(X) (printf("%s[%dm", (ESC), (X)))
#define HIDE_CURS() (printf("%s[?25l", (ESC)))
#define SHOW_CURS() (printf("%s[?25h", (ESC)))
#define COLOR(X, Y) (std::cout << ESC << "[" << (X) << ";" << (Y) << "m")
#define RESET_COLOR() (std::cout << ESC << "[0m")

enum FORMAT {
    BOLD = 1,
    DIM,
    ITALIC,
    UNDERLINE
};

enum COLORS{
    RESET_COLOR = 0,
    BLACK_FG = 30,
    RED_FG,
    GREEN_FG,
    YELLOW_FG,
    BLUE_FG,
    MAGENTA_FG,
    CYAN_FG,
    WHITE_FG,
    DEFAULT_FG = 39,
    BLACK_BG,
    RED_BG,
    GREEN_BG,
    YELLOW_BG,
    BLUE_BG,
    MAGENTA_BG,
    CYAN_BG,
    WHITE_BG,
    DEFAULT_BG
};

#endif
