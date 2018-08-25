/* Unique Character Counter.cpp: 
This program will determine the most frequent letter(s) used in a given c-string.
We'll initialize a struct array in respect to the English alphabet with members that will track unique letters used in the assigned string.
Afterwards, the c-string characters (A-Z) will be converted from lower-case to upper-case (if applicable) to further ease string analyzation throughout the program.
Following that, the program will read through the string and calculate the repetition of each character used in the string.
The final results of the most occurring letter(s), total characters in the string, and overall character usage will be displayed to the user.
*/

#include "stdafx.h"
#include <iostream>
#include <string>


/*==========Global Values==========*/
const int ALPHABET_LENGTH = 26;	//Global constant for the length of the English Alphabet
/*=================================*/

/*===========Structures===========*/
struct Alphabet
{
	char letter; //Letter in respect to array index. 0 = A; 1 = B; etc.
	int matches; //Tracks how many times a character match is found
};
/*================================*/

/*==================Functions====================*/
void initializeAlphabetArray(Alphabet ar[]);
void lowercaseToUppercase(Alphabet ar[],int sLength, char* cstring);
void analyzeString(const char* convertedString, int sLength, Alphabet ar[]);
int calculateMostFrequentCharacter(Alphabet ar[]);
void printOverallAnalysis(Alphabet ar[], int mFrequent, const char* cstring, int sLength);
/*===============================================*/


int main()
{
	Alphabet ar[ALPHABET_LENGTH]; //Create an array consisting of the English alphabet
	char readMe[] = "Caught in the river, turning blue... Hold your breath as it covers you.";  //Example and Test c-string for this program //Test strings: abCdEFGHijkLmnOPqrsTUVWXYZ qwertyuiopoiutyuhuomsabvd 123456,;'[/*-@@@xx4###!/HelloWorld.+++__
	int stringLength = strlen(readMe); //Checks and stores the value of the string's length.
	int mostFrequent;

	initializeAlphabetArray(ar);
	lowercaseToUppercase(ar, stringLength, readMe);
	analyzeString(readMe, stringLength, ar);
	mostFrequent = calculateMostFrequentCharacter(ar);
	printOverallAnalysis(ar, mostFrequent, readMe, stringLength);

    return 0;
}


/*============================================================================================================================================================*/
//Initializes the Alphabet struct by getting rid of "junk" values and associating each index with their corresponding letter of the alphabet
void initializeAlphabetArray(Alphabet ar[])
{
	char init = 'A'; 

	for (int i = 0; i < ALPHABET_LENGTH; i++) //Starting at the first array index, assign one character (in alphabetical order) to each struct member and remove junk values by setting each counter to 0.
	{
		ar[i].matches = 0;
		ar[i].letter = init;
		init++;
	}
}

//This function will convert all characters to upper-case, if applicable, by subtracting 32 from their ascii decimal value. Helps ease character comparisons.
void lowercaseToUppercase(Alphabet ar[],int sLength, char* cstring)
{
	for (int i = 0; i < sLength; i++)
	{
		if (cstring[i] >= 'a' && cstring[i] <= 'z')
		{
			cstring[i] -= 32;
		}
	}
	//std::cout << cstring << "\n\n";
}

//Analyzes the converted c-string by identifying and storing used characters in the respective Alphabet struct array indices.
void analyzeString(const char* convertedString, int sLength, Alphabet ar[])
{
	char currentCharacter;

	for (int i = 0; i < sLength; i++)
	{
		currentCharacter = convertedString[i]; //Set the local character variable to the current read character in the c-string
		currentCharacter -= 65; //Subtract 65 from the current-read character's ascii decimal value to identify the array index it belongs to
		ar[currentCharacter].matches++; //Increase the array index's match count by one after calculating t
	}
	//std::cout << convertedString << "\n\n";
}

//Does a thing
int calculateMostFrequentCharacter(Alphabet ar[])
{
	int highestMatch = 0;

	for (int i = 0; i < ALPHABET_LENGTH; i++)
	{
		if (ar[i].matches > highestMatch)
		{
			highestMatch = ar[i].matches;
		}
	}

	return highestMatch;
}

//Displays a table showing the character match count for all letters used in the analyzed string as well as the most frequently used letter(s)
void printOverallAnalysis(Alphabet ar[], int mFrequent, const char* cstring, int sLength)
{
	std::cout << cstring << " (" << sLength << " Characters)\n\n";

	for (int i = 0; i < ALPHABET_LENGTH; i++)
	{
		std::cout << ar[i].letter << " : " << ar[i].matches << "\n";
	}

	std::cout << "\n====================================\nMost frequent letter(s): ";
	for (int i = 0; i < ALPHABET_LENGTH; i++)
	{
		if (ar[i].matches >= mFrequent)
		{
			std::cout << ar[i].letter << " ";
		}
	}

	std::cout << "\nMax Frequency: " << mFrequent << "\n====================================\n\n";
}