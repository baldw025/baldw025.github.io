#include <iostream>
#include <string>
#include "balancedDelimiterCheck.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
	Stack stack;
	char userInput;
	string userString;

	do {
		cout << "Enter a string to check delimiter balance: ";
		getline(cin, userString);
		stack.isProperlyBalanced(userString);
		cout << "Would you like to check another string? Enter \"Y\" for yes, or any other character to exit: ";
		cin.get(userInput);
		cin.ignore(9999, '\n');
	} while (userInput == 'Y' || userInput == 'y');

	return 0;
}