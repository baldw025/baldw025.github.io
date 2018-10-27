#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int multiply(const int &n1, const int &n2);
int numChars(const char &key, const string &sent, int index);

int main()
{
	int num1;
	int num2;
	int index = 0;
	string sentence;
	char keys; //:^)

	cout << "Enter a number: ";
	cin >> num1;
	cout << "Enter another number: ";
	cin >> num2;
	cout << "Product of " << num1 << "x" << num2 << ": " << multiply(num1, num2) << endl;

	cout << "Enter a sentence: ";
	cin.ignore(9999, '\n');
	getline(cin, sentence);
	cout << "Enter a letter to search for in the previous string: ";
	cin >> keys;
	cout << "The letter \"" << keys << "\" was found " << numChars(keys, sentence, index) << " times in the string, \"" << sentence << "\"." << endl;

	return 0;
}

int multiply(const int &n1, const int &n2)
{
	if (n1 == 0 || n2 == 0) //Base case if any passed value is 0, or we calculate down to 0
	{
		return 0;
	}
	else if (n2 != 0)
	{
		return n1 + multiply(n1, n2 - 1); //Call the multiply function again and decrement the second value until == 0
	}
}

int numChars(const char &key, const string &sent, int index)
{
	if (sent.length() <= index) //Base case for reaching end of string, or empty string
	{
		return 0;
	}
	else if (sent[index] == key) //If a character is found, call the function again while incrementing index and count value (when pop stack)
	{
		return 1 + numChars(key, sent, index + 1);
	}
	else
	{
		return numChars(key, sent, index + 1); //If no character found, call the function again and increment index value
	}
}