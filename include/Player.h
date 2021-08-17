#ifndef MASTERMIND_PLAYER_H
#define MASTERMIND_PLAYER_H

#include "string"
#include "vector"

namespace mastermind {
// Player base class. The intention of the base class is to allow for implementations computer players hence the virtual get_code and get_code_feedback functions
	class Player {
	public:
		explicit Player(std::string name);

		virtual ~Player() = default;

		// Get a code from the player secrete or code. Option for hiding the input in the case of a human player
		virtual void get_code(std::string& code, bool hide_input) const = 0;

		// Get code feedback based on given code.
		virtual void get_code_feedback(std::string& code_feedback, const std::string& code) const = 0;

		std::string name;

		int score = 0;
	};
}

#endif //MASTERMIND_PLAYER_H
