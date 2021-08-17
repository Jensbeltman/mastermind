#ifndef MASTERMIND_GAME_H
#define MASTERMIND_GAME_H

#include "Board.h"
#include "Player.h"

#include "array"
#include "vector"
#include "memory"


namespace mastermind {
    // Enums for code validation
    enum class ValidateCode {
        CODE_VALID,
        CODE_EMPTY,
        CODE_INCORRECT_SIZE,
        CODE_INVALID_VALUES,
    };
    // Enums for feedback validation
    enum class ValidateFeedback {
        KEY_VALID,
        KEY_EMPTY,
        KEY_INCORRECT_SIZE,
        KEY_INVALID_VALUES,
        KEY_INCORRECT_FEEDBACK
    };

    // Main game class responsible for querying players, validating user inputs
    class Game {
    public:
        // Constructor taking in the board and game settings
        Game(int n_colors, int code_length, int n_rows, int n_games);

        // Start the game loop
        void start();

    private:
    	// Get secrete code or code guess from player. Includes validation of code and re-prompting if invalid.
    	void get_code(const std::shared_ptr<Player> &player, std::string &code_guess, bool hide_input) const;

    	// Get feedback information from player given a code guess. Includes validation of feedback and re-prompting if invalid.
    	void get_code_guess_feedback(const std::shared_ptr<Player> &player, const std::string &code_guess,
    			std::string &code_feedback) const;

    	// Validate given code
    	[[nodiscard]] ValidateCode code_validation(const std::string &code) const;

    	// Validate given code feedback
    	[[nodiscard]] ValidateFeedback
    	feedback_validation(const std::string &code_guess, const std::string &feedback_key) const;

    	//Informs the player of the faults made
    	void handle_code_validation(ValidateCode &code_error) const;

    	//Informs the player of the faults made
    	void handle_feedback_validation(ValidateFeedback &feedback_validation) const;

    	// Calculate code feedback in terms of how many code entry either has (the right color at the wrong position)(case_1_count) or (the right color and position)(case_2_count)
    	void calculate_correct_color_cases(const std::string &code, size_t &case_1_count, size_t &case_2_count) const;

    	// print player scores
    	void print_current_score() const;

        // Game bord
        Board board;

        // Number of games to be played
        size_t n_games;

        // Number of colors(numbers) that can be used for creating codes
        size_t n_colors;

        // Two players
        std::array<std::shared_ptr<Player>, 2> players;

    };
}

#endif //MASTERMIND_GAME_H
