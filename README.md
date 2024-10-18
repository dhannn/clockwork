# Clockwork
Clockwork is a minimal OS emulator with two main OS features—process scheduling and memory management. 

## Dependencies
1. [MinGW-w64 12.0.0](https://winlibs.com/)
    - Use the version with POSIX threads
1. `make`
    - Install on MinGW interface

## Installation
### ANSI Escape Codes
This program uses ANSI escape sequences which signals commands such as cursor positioning and color to the terminal.

However, some terminals don't support ANSI escape sequences.

#### Command Prompt and Powershell
For these windows CLIs to support ANSI escape codes, follow these steps:

1. Go to Registry Editor.
1. Go to `HKEY_CURRENT_USER/Console`.
1. Search for the key `VirtualTerminalLevel`.
    - If not found, create a key.
1. Set the value to 1.

The key `HKEY_CURRENT_USER/Console/VirtualTerminalLevel` sets the default behavior of Windows terminals to support ANSI escape sequences.

#### Windows Terminal
The new Windows Terminal supports ANSI escape code without adjustments.

### Build
1. Run `make-mingw64` to build the executable.
1. Enter `.\cw` to run the program.
