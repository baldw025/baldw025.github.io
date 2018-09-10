/*This program will get a string input from the user, remove all whitespace from the input if applicable, then display the modified string in the buffer*/
#include <iostream>
#include <string>
#include <sstream>

void removeSpace(std::string& originString);

int main()
{
	std::string string1;

	std::cout << "Input a sentence: ";
	std::getline(std::cin, string1);

	removeSpace(string1);

	std::cout << string1 << std::endl;

	return 0;
}

//This function will receive a pass by value string, remove any whitespace, and output the modified string in the buffer.
void removeSpace(std::string& originString)
{
	std::string currentWord; //Temporary string that will store our currently read word from the stringstream

	std::stringstream stream;

	stream << originString; 

	originString = ""; //Clear the original string so we can rewrite to it without whitespace

	//While there is still data in the stringstream, read and store the current read word into our original string
	while (stream >> currentWord)
	{
		originString += currentWord;
	}
}
