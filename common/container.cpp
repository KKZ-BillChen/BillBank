#include "container.h"
void clear_screen()
{
#if defined _WIN32
	system("cls");
#else
	system("clear");
#endif
}
void pause_screen() {
#if defined _WIN32
	sleep_for(seconds(1));
	system("pause");
#else
	std::cout << "Press any key to continue..." << endl;
	sleep_for(seconds(1));
	system("read");
	
#endif
}
void color(int c) {
#if defined _WIN32
	if (c >= 0 && c <= 15)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
	else
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
//#else
	
#endif
}
TypeOfSavings change_between_TypeOfSavings_and_int(int a) {
	switch (a) {
	case 0:
		return Minutes_5;
		break;
	case 1:
		return Minutes_10;
		break;
	default:
		return Minutes_5;
		break;
	}
	return Minutes_5;
}
int change_between_int_and_TypeOfSavings(TypeOfSavings a) {
	switch (a) {
	case Minutes_5:
		return 5;
		break;
	case Minutes_10:
		return 10;
		break;
	default:
		return 5;
		break;
	}
	return 5;
}
string change_between_TyoeOfSavings_and_string(TypeOfSavings a) {
	switch (a) {
	case Minutes_5:
		return "5 mins";
		break;
	case Minutes_10:
		return "10 mins";
		break;
	default:
		return "5 mins";
		break;
	}
	return "5 mins";
}

string clear_password(string str) {
	int i = 0;
	if (!str.empty())
		while ((i = str.find('\0', i)) != string::npos)
			str.erase(i, 1);
	return str;
}
string secretword() {
	string pw;
#if defined _WIN32
	char c;
	int len = 0;
	pw = "";
	while ((c = _getch()) != '\r') {
		if (isprint(c)) {
			for (int i = pw.length(); i > pw.length() - len; i--)
				pw[i - 1] = pw[i];
			len = 0;
			pw += c;
			putchar('*');
		}
		else if (pw.length() > 0 && c == '\b') {
			len++;
			putchar('\b');
			putchar('\0');
			putchar('\b');
		}
	}
	std::cout << '\n';
	pw = clear_password(pw);
	return pw;
#else
	std::cin >> pw;
	return pw;
	std::cout << endl;
#endif
}