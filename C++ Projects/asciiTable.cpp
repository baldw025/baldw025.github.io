/***************************************************************************************
This program will output a 16-wide table of ASCII characters ranging from 33 - 126.
***************************************************************************************/

#include <iostream> //Input output stream, needed for cout
#include <iomanip> //Input output stream manipulator, needed for setw
using namespace std; //Standard namespace yadda yadda

int main()
{
  int step; //Counter that keeps track of characters per line
  step = 0; //Initializes the counter as 0, so no random value is used

  for (char a = 33; a <= 126; a++) //Statement that initializes our initial ascii char 'a' to 33 '!', and while said char is less than or equal to 126, 'a' will increase by '1'
    {
      step ++; //When the condition above succeedes, the counter will increase by 1. It helps prevent weirdness by residing outside of the below if statement.

      if (step < 16) //If the characters per line is less than 15, output the next ascii character.
	{
	  cout << left << setw(3) << a;
	}
      else //When the above condition fails, it will add the last desired row value of 16, start a new 'char line' via endline, then reset the counter to 0
	{
	  cout << left << setw(3) << a;
	  cout << endl;
	  step = 0;
	}
    }
  cout << endl; // a e s t h e t i c s
  return 0;
}
