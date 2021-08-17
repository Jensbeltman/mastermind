// Implementation taken from http://www.cplusplus.com/articles/E6vU7k9E/
// Functions for getting command line input without showing whats typed
// get_pass have been slightly modified to not allow for empty input
#ifndef MASTERMIND_TERMINALFUNCTIONALITY_H
#define MASTERMIND_TERMINALFUNCTIONALITY_H

#include <termios.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <string>

namespace tf {
	int getch();
	std::string get_pass(const char* prompt, bool show_asterisk);
}

#endif //MASTERMIND_TERMINALFUNCTIONALITY_H
