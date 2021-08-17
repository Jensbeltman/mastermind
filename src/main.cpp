#include <iostream>

#include "../include/Game.h"

using namespace std;

int main(int argc, char** argv)
{
	std::vector<int> arguments = { 6, 4, 5, 4 }; // Default arguments for n_colors, code_length, n_row, n_games

	// Check for program arguments and replace default values if they are valid
	if (argc>1) {
		for (size_t i = 1; i<static_cast<size_t>(argc); i++) {
			try {
				arguments[i-1] = std::stoi(argv[i]);
			}
				// Standard exceptions for stoi
			catch (const std::invalid_argument& e) {
				std::cout << "Program argument " << i-1
						  << " not an integer default value used. Read readme.txt for more information." << std::endl;
			}
			catch (const std::out_of_range& e) {
				std::cout << "Program argument " << i-1
						  << " not an integer default value used. Read readme.txt for more information." << std::endl;
			}

			if (i>=arguments.size()) {
				break;
			}
		}
	}

	// Warning if a game is started with an uneven amount of games
	if (arguments[3]%2) {
		std::cout << "The number of games played should be even to make the game fair, but was set to be "
				  << arguments[3] << std::endl;
	}


	// Create a game and start it
	mastermind::Game mastermind_game(arguments[0], arguments[1], arguments[2], arguments[3]);
	mastermind_game.start();

	return 0;
}
