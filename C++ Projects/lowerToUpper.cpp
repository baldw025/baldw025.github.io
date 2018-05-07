/**************************************************************
This program will ask the user for a lower-case letter then convert the user's input to a capital letter; with a period, because reasons.

Has no fail safe for non-lower-case letters.
**************************************************************/
#include <iostream>
using namespace std;

int main()
{

  char ch; //Stores the user's character input as a character
  int iout; //Converts the user's character to an integer
  char fout;//Converts the converted integer to a character

  //This is where the magic happens
  cout << "Enter a lowercase letter: " << endl; //Gets user input
  cin >> ch; //Stores user input as a char
  iout = ch; //Sets the char = to an int
  iout = iout - 32; //Converts the ASCII character with a fixed 32 diff
  fout = iout; //Stores the converted ASCII character int as a char
  cout << "The uppercase is "<< fout << "." << endl; //Final converted output
  
  return 0; //No issues

}
