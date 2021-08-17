#include "Board.h"

#include "iostream"

namespace mastermind {

	Board::Board(int code_length, int n_rows)
			:code_length(code_length), n_rows(n_rows)
	{
		rows.resize(n_rows, Row{ std::string(code_length, '0'), std::string(code_length, '0') });
	}

	void Board::clear()
	{
		std::fill(rows.begin(), rows.end(), Row{ std::string(code_length, '0'), std::string(code_length, '0') });
	}

	void Board::print() const
	{
		std::cout << "\nGame board, Code Guess | Feedback Key: \n";

		for (const Row& row:rows) {
			for (const char& code_val:row.code_guess) {
				std::cout << code_val << " ";
			}
			std::cout << "| ";
			for (const char& key_val:row.feedback_key) {
				std::cout << key_val << " ";
			}
			std::cout << "\n";
		}
		std::cout << std::endl;
	}

}