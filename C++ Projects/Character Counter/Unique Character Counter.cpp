// Unique Character Counter.cpp: This program will determine the most frequent character(s) used in a given string.

#include "stdafx.h"
#include <iostream>
#include <string>


/*==========Global Values==========*/
const int ALPHABET_LENGTH = 26;	//Global constant for the length of the English Alphabet
/*=================================*/

struct Alphabet
{
	char letter; //Letter in respect to array index. 0 = A; 1 = B; etc.
	int matches; //Tracks how many times a character match is found
};

/*==================Functions====================*/
void initializeAlphabetArray(Alphabet ar[]);
char lowercaseToUppercase(char i);
void analyzeString(char* convertedString, int sLength, Alphabet ar[]);
/*==============================================*/


int main()
{
	Alphabet ar[ALPHABET_LENGTH]; //Create an array consisting of the English alphabet
	char readMe[256] = "Caught in the river, turning blue... Hold your breath as it covers you."; //Example c-string for this program
	int stringLength = strlen(readMe); //Checks and stores the value of the string's length.


	initializeAlphabetArray(ar);

	
	for (int i = 0; i < stringLength; i++)
	{
		readMe[i] = lowercaseToUppercase(readMe[i]); //Call function to convert all string characters to uppercase.
	}

	analyzeString(readMe, stringLength, ar);

	std::cout << readMe << "\n\n";
	
	
	
	
	/*Debug Stuff*/
	std::cout << ar[2].matches << " matches for the letter " << ar[2].letter << "\n\n";
	
	for (int i = 0; i < ALPHABET_LENGTH; i++)
	{
		std::cout << ar[i].letter << " " << ar[i].matches << "\n";

	}

    return 0;
}

/*============================================================================================================================================================*/
//Initalizes the Alphabet struct by getting rid of "junk" values and associating each index with their corresponding letter of the alphabet
void initializeAlphabetArray(Alphabet ar[])
{
	char init = 'A';

	for (int i = 0; i < ALPHABET_LENGTH; i++)
	{
		ar[i].matches = 0;
		ar[i].letter = init;
		init++;
	}
}

//This function will convert all characters to uppercase, if applicable, by subtracting 32 from their ascii decimal value. Helps ease character comparisons.
char lowercaseToUppercase(char i)
{
	if (i >= 'a' && i <= 'z')
		{
			i -= 32;
		}
	return i;
}

//Analyzes the converted string by identifying and storing used characters in the Alphabet struct array.
void analyzeString(char* convertedString, int sLength, Alphabet ar[])
{
	char currentCharacter;

	std::cout << convertedString << "\n\n";

	for (int i = 0; i < sLength; i++)
	{
		//Debug: currentCharacter = convertedString[i];
		currentCharacter -= 65;
		ar[currentCharacter].matches++;
		//Debug: std::cout << "\n" << convertedString[i] << " This should be " << convertedString[i] << "\n";

	}
}