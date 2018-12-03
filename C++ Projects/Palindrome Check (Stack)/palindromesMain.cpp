#include <iostream>
#include <string>
#include "palindromeStackMethod.h"
//#include "palindromeQueueMethod.h"

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
		cout << "Enter a string to check if it is palindrome: ";
		getline(cin, userString);
		for (int i = 0; i < int(userString.size()); i++)
		{
			stack.push(userString[i]);
		}
		stack.isPalindrome(userString);
		cout << "Would you like to check another string? Enter \"Y\" for yes, or any other character to exit: ";
		cin.get(userInput);
		cin.ignore(9999, '\n');
		stack.deleteStack();
	} while (userInput == 'Y' || userInput == 'y');

	return 0;
}