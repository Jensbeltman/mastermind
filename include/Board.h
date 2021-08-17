#ifndef MASTERMIND_BOARD_H
#define MASTERMIND_BOARD_H

#include "vector"
#include "string"

namespace mastermind {
    // Struct for containing row information
    struct Row {
        std::string code_guess;
        std::string feedback_key;
    };

    // Board struct containing rows and the secrete code
    class Board {
    public:
        // Initialize board with number of color, code length and number of rows
        Board(int code_length, int n_rows);

        // clear the content of the board
        void clear();

        // print the contents of the board to terminal
        void print() const;

        // How long the codes should be
        size_t code_length;
        // Number of rows/chances for the codebreaker to guess the secrete code
        size_t n_rows;

        // Secrete code made by the code maker
        std::string secrete_code;
        // Rows for code guesses and feedback
        std::vector<Row> rows;
    };
}

#endif //MASTERMIND_BOARD_H
