#ifndef MASTERMIND_MASTERMIND_H
#define MASTERMIND_MASTERMIND_H

#include "array"
#include "vector"
#include "Player.h"
#include "memory"

// Main game object responsible for querying players, validation inputs and showing game state
class Mastermind {
public:
    Mastermind(int n_colors, int n_pegs_pr_row, int n_rows, int n_games);
    // Game loop
    void start();

private:
    // Game settings
    int n_colors;
    int n_pegs_pr_row;
    int n_rows;
    int n_games;

    // Containers for contents of the game boar. Code peg color represented by numbers from 1 to 9 and key peg color is represented by 1,2, 0 is used for empty peg spots.
    std::vector<int> secrete_code;
    std::vector<std::vector<int>> code_peg_rows;
    std::vector<std::vector<int>> key_peg_rows;

    // Containers for players and scores
    std::array<std::shared_ptr<Player>, 2> players;
    std::array<double, 2> scores;

    // Validate given code
    int validate_code_pegs(const std::vector<int> &code_pegs);

    // Validate given code feedback
    int validate_key_pegs(const std::vector<int> &code_pegs, const std::vector<int> &key_pegs);

    //Informs the player of the faults made
    void handle_code_error(int &code_error, int &row_i);

    //Informs the player of the faults made
    void handle_key_error(int &key_error, int &row_i);

    // Clears the board contents between games
    void clear_board();

    // Initialize empty board
    void initialize_rows(std::vector<std::vector<int>> &rows);

    // Get code feedback in terms of how many code entry either has (the right color at the wrong position)(n1) or (the right color and position)(n2)
    void get_code_feedback(const std::vector<int> &code_pegs, int &n1, int &n2);

    // Print the contents of the game board
    void print_board();
};


#endif //MASTERMIND_MASTERMIND_H
