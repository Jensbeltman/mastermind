#ifndef MASTERMIND_HUMANPLAYER_H
#define MASTERMIND_HUMANPLAYER_H

#include "Player.h"

class HumanPlayer : public Player {
// Code Breaker
    void getCodeGuess(std::vector<int> &code_peg_row) override;

// Code Maker
    void getCodeGuessFeedback(const std::vector<int> &code_peg_row, std::vector<int> &key_peg_row) override;

    void getCode(std::vector<int> &code_peg_row) override;

};


#endif //MASTERMIND_HUMANPLAYER_H
