//This program will get three strings from a user (string1, string2, string3)
//We will call a function that will search string1 for all occurrences of string2 and replace them with string3
//Store the new string in string4

#include "pch.h"
#include <iostream>
#include <string>

std::string replaceSubString(std::string string1, const std::string &string2, const std::string &string3);

int main()
{
	std::string string1; //User's sentence string
	std::string string2; //User's word to search string for
	std::string string3; //Word to replace string2 with
	std::string string4; //Final modified string

	std::cout << "Enter a sentence: ";
	getline(std::cin, string1);
	std::cout << "\nEnter a word/phrase/letter to search for: ";
	getline(std::cin, string2);
	std::cout << "Replace searched word/phrase/letter with: ";
	getline(std::cin, string3);

	//Checks and loops if the user attempts to search and replace the same word.
	//Breaks when they stop being hard-headed.
	if(string3 == string2)
	do
	{
		std::cout << "\nError: Can not search and replace the same word/phrase/letter.";
		std::cout << "\nReplace searched word/phrase/letter with: ";
		getline(std::cin, string3);
	} while (string3 == string2);

	string4 = replaceSubString(string1, string2, string3);

	std::cout << "\nModified String: " << string4 << std::endl;
	
	return 0;
}

//Finds all instances of a string and replaces it with another string
std::string replaceSubString(std::string string1, const std::string &string2, const std::string &string3)
{
	bool found = false;

	int pos = string1.find(string2, 0); //Set our position equal to the first instance of the word, if possible.

	//While not at the end of the original string, replace string with user's inputs
	//Proceed to check the rest of the string afterwards
	while (pos != string1.npos)
	{
		found = true;
		string1.replace(pos, string2.size(), string3);
		pos = string1.find(string2, pos + 1);
	}
	
	if (!found)
	{
		string1 = "No words were replaced.";
	}
	return string1;
}