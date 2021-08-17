#include "Game.h"
#include "HumanPlayer.h"

#include <iostream>

namespace mastermind {

	Game::Game(int n_colors, int code_length, int n_rows, int n_games)
			:board(code_length, n_rows), n_games(n_games),
			 n_colors(n_colors)
	{

		// Check if number of colors is valid and change if it is not
		if (n_colors>9) {
			std::cout << "Number of colors cannot exceed 9 and have thus been change to 9" << std::endl;
			n_colors = 9;
		}

		// Print game info
		std::cout << "mastermind game created with the following parameters:\n"
				  << "\tNumber of colors(single digit integers): " << n_colors << "\n"
				  << "\tcode_length: " << code_length << "\n"
				  << "\tNumber of board rows: " << n_rows << "\n"
				  << "\tNumber of games to play: " << n_games << "\n" << std::endl;


		// Get player names
		std::string name;
		std::cout << "Enter the name of the first player:" << std::endl;
		std::cin >> name;
		players[0] = std::make_shared<HumanPlayer>(name);
		std::cout << "Enter the name of the second player:" << std::endl;
		std::cin >> name;
		players[1] = std::make_shared<HumanPlayer>(name);
	}

	void Game::start()
	{
		for (size_t game_i = 0; game_i<n_games; game_i++) {
			std::cout << "\nStarting game " << game_i+1 << " of " << n_games << "\n" << std::endl;
			board.clear(); // clear old codes guesses and feedback

			// Switching player roles
			std::shared_ptr<Player>& code_maker = players[game_i%2];
			std::shared_ptr<Player>& code_breaker = players[static_cast<size_t>(!(game_i%2))];

			// Get secrete code from code maker
			std::cout << "Player("+code_maker->name+") please enter secrete code:" << std::endl;
			get_code(code_maker, board.secrete_code, true); // Character hidden to keep code secrete for the code breaker

			// Play through the rows of the board
			for (size_t row_i = 0; row_i<board.n_rows; row_i++) {
				Row& current_row = board.rows[row_i];

				std::cout << "Player("+code_breaker->name+") please enter code guess:" << std::endl;
				get_code(code_breaker, current_row.code_guess, false);

				// Get code guess from code maker
				std::cout << "\nPlayer("+code_maker->name+") please enter feedback key:" << std::endl;
				get_code_guess_feedback(code_maker, current_row.code_guess, current_row.feedback_key);

				board.print();// print the contents of the game board now that a new set of guess and feedback is available

				// Game ends of the feedback states that the gues was corrects
				if (static_cast<size_t>(std::abs(std::count(current_row.code_guess.begin(), current_row.code_guess.end(), 2)))==board.code_length) {
					code_maker->score += row_i+1; // Code maker gets points pr row used by the code breaker
					std::cout << "Player("+code_breaker->name+") found the right code!\n" << std::endl;
					print_current_score();
					break;

				}
				// Game ends if all rows have been used without the code breaker guessing the secrete code
				else if (board.n_rows==(row_i+1)) {
					code_maker->score += row_i+2; // One extra point for the code maker when the code was not guessed on the last attempt
					std::cout << "Player("+code_breaker->name+") did not find the right code!\n" << std::endl;
					print_current_score();
				}
			}
		}

		// Find winning player(s) based on score
		if (players[0]->score==players[1]->score) {
			std::cout << "The games resulted in a draw!" << std::endl;
		}
		else {
			auto& winning_player = players[0]->score>players[1]->score ? players[0] : players[1];
			std::cout << "Player("+winning_player->name+") won!" << std::endl;
		}
	}

	void Game::get_code(const std::shared_ptr<Player>& player, std::string& code_guess, bool hide_input) const
	{
		player->get_code(code_guess, hide_input);
		ValidateCode code_valdation = code_validation(code_guess);

		while (code_valdation!=ValidateCode::CODE_VALID) {
			handle_code_validation(code_valdation);
			std::cout << "Please re-enter code:" << std::endl;
			player->get_code(code_guess, hide_input);
			code_valdation = code_validation(code_guess);
		}
	}

	void Game::get_code_guess_feedback(const std::shared_ptr<Player>& player, const std::string& code_guess,
			std::string& code_feedback) const
	{
		// Query player for valid feedback on code gues from code maker
		player->get_code(code_feedback, false);
		ValidateFeedback key_validation = feedback_validation(code_guess, code_feedback);

		while (key_validation!=ValidateFeedback::KEY_VALID) {
			handle_feedback_validation(key_validation);
			std::cout << "Please re-enter feedback key:" << std::endl;
			player->get_code_feedback(code_feedback, code_guess);
			key_validation = feedback_validation(code_guess, code_feedback);
		}
	}

	ValidateCode Game::code_validation(const std::string& code) const
	{
		if (code.empty()) {
			return ValidateCode::CODE_EMPTY;
		}
		if (code.size()!=board.code_length) {
			return ValidateCode::CODE_INCORRECT_SIZE;
		}

		for (const char& c:code) {
			if (c<='0' ||  c>('0'+static_cast<char>(n_colors))) {
				return ValidateCode::CODE_INVALID_VALUES;
			}
		}
		return ValidateCode::CODE_VALID;
	}

	ValidateFeedback
	Game::feedback_validation(const std::string& code_guess, const std::string& feedback_key) const
	{
		if (feedback_key.empty()) {
			return ValidateFeedback::KEY_EMPTY;
		}
		if (feedback_key.size()!=board.code_length) {
			return ValidateFeedback::KEY_INCORRECT_SIZE;
		}

		for (const char& p:feedback_key) {
			if (p<'0' || p>'2') {
				return ValidateFeedback::KEY_INVALID_VALUES;
			}
		}

		// Checks if the feedback was correct based on code guess
		size_t case_1, case_2; // Two cases of correct color
		calculate_correct_color_cases(code_guess, case_1, case_2);

		// Count the number of correct color cases in the feedback key
		size_t c_1_count = std::count(feedback_key.begin(), feedback_key.end(), '1');
		size_t c_2_count = std::count(feedback_key.begin(), feedback_key.end(), '2');

		// Compare
		if (case_1!=c_1_count || case_2!=c_2_count) {
			return ValidateFeedback::KEY_INCORRECT_FEEDBACK;
		}

		return ValidateFeedback::KEY_VALID;
	}

	void Game::calculate_correct_color_cases(const std::string& code, size_t& case_1_count, size_t& case_2_count) const
	{
		case_1_count = 0;
		case_2_count = 0;

		// Find matched color and position cases between code guess and secrete code
		std::vector<size_t> remaining_indexes;
		for (size_t i = 0; i<board.code_length; i++) {
			if (code[i]==board.secrete_code[i]) {
				case_2_count++;
			}
			else {
				remaining_indexes.push_back(i);
			}
		}
		std::vector<size_t> code_as_int, secrete_code_as_int;
		std::transform(code.begin(), code.end(), std::back_inserter(code_as_int), [](const char& c) { return static_cast<size_t>(c-'0'); });
		std::transform(board.secrete_code.begin(), board.secrete_code.end(), std::back_inserter(secrete_code_as_int), [](const char& c) { return static_cast<size_t>(c-'0'); });

		std::vector<size_t> color_counts_code(n_colors+1, 0); // +1 added for empty spot "color value"(0) to avoid decrementing color values in loop

		// Go through non matched code values and count the occurrences of colors
		for (size_t& i:remaining_indexes) {
			color_counts_code[code_as_int[i]]++;
		}
		// Checks for colors in non matched secrete code values having the same color as non matched code values. Avoids matching duplicated by using color counts
		for (size_t& i:remaining_indexes) {
			if (color_counts_code[secrete_code_as_int[i]]>0) {
				case_1_count++;
				color_counts_code[secrete_code_as_int[i]]--;
			}
		}
	}

	void Game::handle_code_validation(ValidateCode& code_error) const
	{
		std::cout << "(Code Error) ";
		switch (code_error) {
		case ValidateCode::CODE_VALID:
			break;
		case ValidateCode::CODE_EMPTY:
			std::cout << "Empty code received." << std::endl;
			break;
		case ValidateCode::CODE_INCORRECT_SIZE:
			std::cout << "Code of invalid size received, code size should be " << board.code_length << "."
					  << std::endl;
			break;
		case ValidateCode::CODE_INVALID_VALUES:
			std::cout << "Code with invalid values received, allowed values are ";
			for (size_t i = 1; i<=n_colors; i++) {
				std::cout << i;
				if (i<n_colors) {
					std::cout << ",";
				}
			}
			std::cout << "." << std::endl;
			break;

		}
	}

	void Game::handle_feedback_validation(ValidateFeedback& feedback_validation) const
	{
		std::cout << "(Key Error) ";
		switch (feedback_validation) {
		case ValidateFeedback::KEY_VALID:
			break;
		case ValidateFeedback::KEY_EMPTY:
			std::cout << "Empty feedback key received." << std::endl;
			break;
		case ValidateFeedback::KEY_INCORRECT_SIZE:
			std::cout << "Code feedback key of invalid size received, key size should be " << board.code_length
					  << "." << std::endl;
			break;
		case ValidateFeedback::KEY_INVALID_VALUES:
			std::cout << "Feedback key with invalid values received, allowed values are 0,1,2."
					  << std::endl;
			break;
		case ValidateFeedback::KEY_INCORRECT_FEEDBACK:
			std::cout << "Feedback key incorrect." << std::endl;
			break;

		}
	}

	void Game::print_current_score() const
	{
		std::cout << "Current Score:"
				  << "\n\tPlayer("+players[0]->name+") "+std::to_string(players[0]->score)
				  << "\n\tPlayer("+players[1]->name+") "+std::to_string(players[1]->score)
				  << std::endl;
	}

}