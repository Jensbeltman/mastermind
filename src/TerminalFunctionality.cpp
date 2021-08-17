#include "TerminalFunctionality.h"

using namespace std;
namespace tf {

	int getch()
	{
		int ch;
		struct termios t_old, t_new;

		tcgetattr(STDIN_FILENO, &t_old);
		t_new = t_old;
		t_new.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &t_new);

		ch = getchar();

		tcsetattr(STDIN_FILENO, TCSANOW, &t_old);
		return ch;
	}

	string get_pass(const char* prompt, bool show_asterisk = true)
	{
		const char BACKSPACE = 127;
		const char RETURN = 10;

		string password;
		unsigned char ch = 0;

		cout << prompt << endl;

		while (((ch = getch())!=RETURN) || password.empty()) {
			if (ch==BACKSPACE) {
				if (password.length()!=0) {
					if (show_asterisk)
						cout << "\b \b";
					password.resize(password.length()-1);
				}
			}
			else if(ch!=RETURN) {
				password += ch;
				if (show_asterisk)
					cout << '*';
			}
		}
		cout << endl;

		return password;
	}
}