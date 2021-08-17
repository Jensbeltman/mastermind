#ifndef MASTERMIND_HUMANPLAYER_H
#define MASTERMIND_HUMANPLAYER_H

#include "Player.h"
namespace mastermind {
	class HumanPlayer : public Player {
	public:
		// Using inherited constructor
		using Player::Player;

		// Get code from terminal
		void get_code(std::string& code, bool hide_input) const override;

		// Get code feedback from terminal (same as get_code)
		virtual void get_code_feedback(std::string& code_feedback, const std::string& code) const override;
	private:
		// Reads line from cin and converts chars to intergers. Can optionally replace typed characters with asterisks
		void get_code_from_terminal(std::string& code, bool hide_input = false) const;
	};
}
#endif //MASTERMIND_HUMANPLAYER_H
