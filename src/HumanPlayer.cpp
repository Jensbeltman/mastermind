//
// Created by jens on 8/3/21.
//

#include "../include/HumanPlayer.h"

void HumanPlayer::getCodeGuess(std::vector<int> &code_peg_row) {
    getCodeFromConsole(code_peg_row);
}

void HumanPlayer::getCodeGuessFeedback(const std::vector<int> &code_peg_row, std::vector<int> &key_peg_row) {
    getCodeFromConsole(key_peg_row);
}

void HumanPlayer::getCode(std::vector<int> &code_peg_row) {
    getCodeFromConsole(code_peg_row, true);
}