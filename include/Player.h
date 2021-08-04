#ifndef MASTERMIND_PLAYER_H
#define MASTERMIND_PLAYER_H

#include "string"
#include "vector"

// Player base class. The intention of the base class is to allow for implementations computer players
class Player {
public:
    Player();

// Code Breaker
    // Get attempt at guessing code
    virtual void getCodeGuess(std::vector<int> &code_peg_row) = 0;

// Code Maker
    // Get feedback infomation given a code guess
    virtual void getCodeGuessFeedback(const std::vector<int> &code_peg_row, std::vector<int> &key_peg_row) = 0;

    // Get the code to be guessed
    virtual void getCode(std::vector<int> &code_peg_row) = 0;

protected:
// Utility functions
    // Reads line from cin and converts chars to intergers. Can optionally replace typed characters with asterisks
    static void getCodeFromConsole(std::vector<int> &code_peg_row, bool hide_input = false);

    // Convertion from string to integer vector
    static void stringToIntVec(std::string &code_string, std::vector<int> &code_peg_row);
};


#endif //MASTERMIND_PLAYER_H
