/***************************************************************
A strange game.
The only winning move is not to play.

How about a nice game of chess?

Guess the right number and win the game. The program will tell you if you're close or not.
***************************************************************/

#include <iostream> //What's a game without an input output stream?
#include <cstdlib> //The standard utilities library... of course!
using namespace std; //The namespace has stds

int main()
{
  srand(time(0)); //Initializes the generation of random numbers for the game
  int num; //Stores the game-winning magical number that I will take forever to guess during testing. This calls for a... debug prompt!
  int guess;

  num = rand() % 100 + 1; //Generates a random number ranging from 1 to 100

  //Debug: cout << endl << endl << num << endl << endl;

  while (guess != num) //The following code will continue to execute as long as the user doesn't enter the game-winning number
    {
      cout << "Guess a number bewteen 1 and 100. Enter your guess: ";
      cin >> guess;

      if (guess > num) //If the user's guess is higher than the winning number
	{
	  cout << "Too high! Try Again!" << endl << endl;
	}
      else if (guess < num) //If the user's guess is lower than the winning number
	{
	  //cout << "Too low, like my crippling depression! -- I mean, me too thanks! Try Again!" << endl; 
	  cout << "Too low! Try Again!" << endl << endl;
	}
    }

  if (guess == num) //If the users inputs the correct number they win nothing!
    {
      cout << "You guessed it right!" << endl << endl;
    }


  return 0;
}
