/*************************************************************************
This program will simulate a game of craps.
*************************************************************************/

#include <cstdlib>
#include <iostream>
#include <iomanip>
using namespace std;
int rollDice (int& die_roll);

int main()
{
  srand(time(0)); //Initializes the generation of random numbers throughout the main
  int first_roll; //Stores the value of the first dice roll
  int next_roll; //Stores the roll after the first roll
  bool complete; //For while condition cleanliness, will equal 1 if the user wins or loses the game

  rollDice(first_roll); //Starts and stores the value of the first roll by calling the function that simulates... rolled dice (two)
  cout << first_roll << endl; //Displays the value of the first roll

  do
    {
      if (first_roll == 7 || first_roll == 11 || next_roll == first_roll) //Defines and checks the winning conditions for craps
	{
	  cout << "====You Win!====" << endl; //Displays that the player has won, according the rules of craps, a game which I still don't understand
	  return true; //Returns true, or 1, which tells the program that the game is over and done (puts us out of the "do-while" loop)
	}
      else if (first_roll == 2 || first_roll == 3 || first_roll == 12 || next_roll == 7) //Defines and checks the losing conditions for craps
	{
	  cout << "====You Lost!====" << endl; //Displays that the player has lost, according the rules of craps
	  return true; //Returns true, or 1, which tells the program that the game is over and done (puts us out of the "do-while" loop)
	}

      rollDice(next_roll); //When the above conditions fail, the dice will continue to be rolled until an above condition is satisfied
      cout << next_roll << endl; //Displays the value of the next roll(s)

    }while(complete != true); //The above conditions/simulation will continue until "1/True (Win/Loss)" is returned to the program

  return 0;
}

int rollDice(int& die_roll)
/******************************************
This function simulates rolling a pair of dice.
It returns a random number between 2 and 12.
******************************************/
{
  die_roll = (rand() % 6 + 1) + (rand() % 6 + 1);

  return die_roll; 
}
