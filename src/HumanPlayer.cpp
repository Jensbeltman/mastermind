#include "HumanPlayer.h"
#include "TerminalFunctionality.h"

void HumanPlayer::get_code(std::string& code, const bool hide_input) const
{
	get_code_from_terminal(code, hide_input);
}

void HumanPlayer::get_code_feedback(std::string& code_feedback, const std::string&) const
{
	get_code_from_terminal(code_feedback, false);
}

void HumanPlayer::get_code_from_terminal(std::string& code, bool hide_input) const
{
	if (hide_input) {
		code = tf::get_pass("", true);
	}
	else {
		std::getline(std::cin, code);
	}
}



