//
// Created by jens on 8/3/21.
//

#include "../include/Mastermind.h"
#include "../include/HumanPlayer.h"
#include <iostream>
#include <iomanip>

#define ERR_CODE_EMPTY 1
#define ERR_CODE_INCORRECT_SIZE 2
#define ERR_CODE_INVALID_VALUES 3

#define ERR_KEY_EMPTY 1
#define ERR_KEY_INCORRECT_SIZE 2
#define ERR_KEY_INVALID_VALUES 3
#define ERR_KEY_INCORRECT_FEEDBACK 4


Mastermind::Mastermind(int n_colors, int n_pegs_pr_row, int n_rows, int n_games) : n_colors(n_colors),
                                                                                   n_pegs_pr_row(n_pegs_pr_row),
                                                                                   n_rows(n_rows), n_games(n_games) {


    if (n_colors > 10) {
        std::cout << "Number of colors cannot exceed 10 and have thus been change to 10" << std::endl;
        n_colors = 10;
    }

    std::cout << "Mastermind game created with the following parameters:\n"
              << "\tn_colors: " << n_colors << "\n"
              << "\tn_pegs_pr_row: " << n_pegs_pr_row << "\n"
              << "\tn_rows: " << n_rows << "\n"
              << "\tn_games: " << n_games << "\n" << std::endl;

    clear_board();

    players[0] = std::make_shared<HumanPlayer>();
    players[1] = std::make_shared<HumanPlayer>();
    scores = {0, 0};
}

void Mastermind::initialize_rows(std::vector<std::vector<int>> &rows) {
    rows.resize(n_rows);
    for (auto &p:rows) {
        p.resize(n_pegs_pr_row);
        std::fill(p.begin(), p.end(), 0);
    }
}

void Mastermind::clear_board() {
    initialize_rows(code_peg_rows);
    initialize_rows(key_peg_rows);
    secrete_code.resize(n_pegs_pr_row);
    std::fill(secrete_code.begin(), secrete_code.end(), 0);
}

void Mastermind::start() {
    for (int game_i = 0; game_i < n_games; game_i++) {
        std::cout << "\nStarting game " << game_i + 1 << " of " << n_games << "\n" << std::endl;
        clear_board();

        // switching player roles
        size_t code_maker_i = game_i % 2;
        size_t code_breaker_i = static_cast<size_t>(!code_maker_i);


        // Get secrete code from code maker
        while (validate_code_pegs(secrete_code)) {
            std::cout << "\nPlayer(" + std::to_string(code_maker_i) + ")(Code Maker) please enter code:" << std::endl;
            players[code_maker_i]->getCode(secrete_code);
        }

        // Play through the rows of the board
        for (int row_i = 0; row_i < n_rows; row_i++) {

            // Query code breaker for valid code guess
            int code_error = -1;
            std::cout << "Player(" + std::to_string(code_breaker_i) + ")(Code Breaker) please enter code guess:"
                      << std::endl;
            while (code_error) {
                players[code_breaker_i]->getCodeGuess(code_peg_rows[row_i]);
                code_error = validate_code_pegs(code_peg_rows[row_i]);
                if (code_error) {
                    handle_code_error(code_error, row_i);
                    std::cout << "Please re-enter code:" << std::endl;
                }
            }

            // Query code breaker for valid feedback on code gues from code maker
            int key_error = -1;
            std::cout << "\nPlayer(" + std::to_string(code_maker_i) + ")(Code Maker) please enter feedback key:"
                      << std::endl;
            while (key_error) {
                players[code_maker_i]->getCodeGuessFeedback(code_peg_rows[row_i], key_peg_rows[row_i]);
                key_error = validate_key_pegs(code_peg_rows[row_i], key_peg_rows[row_i]);
                if (key_error) {
                    handle_key_error(key_error, row_i);
                    std::cout << "Please re-enter feedback key:" << std::endl;
                }

            }


            print_board();// Print the contents of the game board


            // Check for game ending conditions and reward code maker according condition
            if (secrete_code == code_peg_rows[row_i]) {
                scores[code_maker_i] += row_i + 1;
                std::cout << "Player(" + std::to_string(code_breaker_i) + ")(Code Breaker) found the right code!\n"
                          << std::endl;
                std::cout << "Current Score:"
                          << "\n\tPlayer(0) " + std::to_string(scores[0])
                          << "\n\tPlayer(1) " + std::to_string(scores[1])
                          << std::endl;
                break;

            } else if (n_rows == (row_i + 1)) {
                scores[code_maker_i] += row_i + 1 + static_cast<int>(row_i == (n_rows - 1));
                std::cout
                        << "Player(" + std::to_string(code_breaker_i) + ")(Code Breaker) did not find the right code!\n"
                        << std::endl;
                std::cout << "Current Score:"
                          << "\n\tPlayer(0) " + std::to_string(scores[0])
                          << "\n\tPlayer(1) " + std::to_string(scores[1])
                          << std::endl;
            }
        }
    }

    // Find winning player(s) based on score
    if(scores[0]==scores[1]) {
        std::cout << "The games resulted in a draw  " << scores[1] << " to " << scores[2] << std::endl;
    }
    else{
        int winning_player = std::distance(scores.begin(), std::max_element(scores.begin(), scores.end()));
        std::cout << "Player(" + std::to_string(winning_player) + ") won " << scores[winning_player] << " to "
        << scores[static_cast<int>(!winning_player)] << std::endl;
    }
}


int Mastermind::validate_code_pegs(const std::vector<int> &code_pegs) {
    if (code_pegs.empty()) {

        return ERR_CODE_EMPTY;
    }
    if (code_pegs.size() != n_pegs_pr_row) {
        return ERR_CODE_INCORRECT_SIZE;
    }

    for (auto &p:code_pegs) {
        if (p <= 0 || p > n_colors) {
            return ERR_CODE_INVALID_VALUES;
        }
    }
    return 0;
}

int Mastermind::validate_key_pegs(const std::vector<int> &code_pegs, const std::vector<int> &key_pegs) {
    if (key_pegs.empty()) {
        return ERR_KEY_EMPTY;
    }
    if (key_pegs.size() != n_pegs_pr_row) {
        return ERR_KEY_INCORRECT_SIZE;
    }

    for (auto &p:key_pegs) {
        if (p < 0 || p > 2) {
            return ERR_KEY_INVALID_VALUES;
        }
    }

    // Check if the feedback was correct based on code guess
    int n1, n2;
    get_code_feedback(code_pegs, n1, n2);

    int n1c = std::count(key_pegs.begin(), key_pegs.end(), 1);
    int n2c = std::count(key_pegs.begin(), key_pegs.end(), 2);

    if (n1 != n1c || n2 != n2c) {
        return ERR_KEY_INCORRECT_FEEDBACK;
    }
    return 0;
}

void Mastermind::get_code_feedback(const std::vector<int> &code_pegs, int &n1, int &n2) {
    n1 = 0;
    n2 = 0;

    // Find matched color and position cases between code guess and secrete code
    std::vector<int> remaining_indexes;
    for (int i = 0; i < n_pegs_pr_row; i++) {
        if (code_pegs[i] == secrete_code[i]) {
            n2++;
        } else {
            remaining_indexes.push_back(i);
        }
    }


    std::vector<int> color_counts_code(n_colors + 1, 0); // +1 added for empty spot "color value"(0) to avoid decrementing color values in loop

    // Go through non matched code pegs and count the occurrences of colors
    for (int &i:remaining_indexes) {
        color_counts_code[code_pegs[i]]++;
    }
    // Checks for colors in non matched secrete code values having the same color as non matched code values. Avoids matching duplicated by using color counts
    for (int &i:remaining_indexes) {
        if (color_counts_code[secrete_code[i]]) {
            n1++;
            color_counts_code[secrete_code[i]]--;
        }
    }
}

void Mastermind::print_board() {
    std::cout << "\nCurrent game status, Code guess | feedback: \n";
    for (int r = n_rows - 1; r >= 0; r--) {
        for (int p = 0; p < n_pegs_pr_row; p++) {
            std::cout << code_peg_rows[r][p] << " ";
        }
        std::cout << "| ";
        for (int p = 0; p < n_pegs_pr_row; p++) {
            std::cout << key_peg_rows[r][p] << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;

}

void Mastermind::handle_code_error(int &code_error, int &row_i) {
    std::cout << "(Code Error) ";
    switch (code_error) {
        case ERR_CODE_EMPTY:
            std::cout << "Empty code received." << std::endl;
            break;
        case ERR_CODE_INCORRECT_SIZE:
            std::cout << "Code of invalid size(" << code_peg_rows[row_i].size()
                      << ") received, code size should be " << n_pegs_pr_row << "." << std::endl;
            break;
        case ERR_CODE_INVALID_VALUES:
            std::cout << "Code with invalid values received, allowed values are ";
            for (int i = 1; i <= n_colors; i++) {
                std::cout << i;
                if (i < n_colors) {
                    std::cout << ",";
                }
            }
            std::cout << "." << std::endl;
            break;

    }
}

void Mastermind::handle_key_error(int &key_error, int &row_i) {
    std::cout << "(Key Error) ";
    switch (key_error) {
        case ERR_KEY_EMPTY:
            std::cout << "Empty feedback key received." << std::endl;
            break;
        case ERR_KEY_INCORRECT_SIZE:
            std::cout << "Feedback key of invalid size(" << key_peg_rows[row_i].size()
                      << ") received, key size should be " << n_pegs_pr_row << "." << std::endl;
            break;
        case ERR_KEY_INVALID_VALUES:
            std::cout << "Feedback key with invalid values received, allowed values are 0,1,2."
                      << std::endl;
            break;
        case ERR_KEY_INCORRECT_FEEDBACK:
            std::cout << "Feedback key incorrect." << std::endl;
            break;
    }
}

