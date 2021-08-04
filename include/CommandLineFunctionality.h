// Implementation taken from http://www.cplusplus.com/articles/E6vU7k9E/
// Functions for getting command line input without showing whats typed
#ifndef MASTERMIND_COMMANDLINEFUNCTIONALITY_H
#define MASTERMIND_COMMANDLINEFUNCTIONALITY_H

#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <string>

namespace cmlf {
    int getch();
    std::string getpass(const char *prompt, bool show_asterisk);
}


#endif //MASTERMIND_COMMANDLINEFUNCTIONALITY_H
