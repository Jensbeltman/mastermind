#include "../include/Player.h"
#include "iostream"
#include "../include/CommandLineFunctionality.h"

Player::Player() {

}

void Player::getCodeFromConsole(std::vector<int> &code_peg_row, const bool hide_input) {
    std::string code_string;
    if (hide_input) {
        code_string = cmlf::getpass("", true);
    } else {
        std::getline(std::cin, code_string);
    }
    stringToIntVec(code_string, code_peg_row);
}

void Player::stringToIntVec(std::string &code_string, std::vector<int> &code_peg_row) {
    if (!code_peg_row.empty()) {
        code_peg_row.clear();
    }
    for (auto &c:code_string) {
        code_peg_row.push_back(static_cast<int>(c) - 48);
    }
}


