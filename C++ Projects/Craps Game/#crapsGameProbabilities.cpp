/*************************************************************************
This program will simulate ungodly amounts of craps games 
and output the probabilities of wining and losing.
*************************************************************************/

#include <cstdlib> //C Standard Library is included so we can use and abuse the random num gen
#include <iostream> //If you don't have an input/output stream, you're not doing it right
#include <iomanip> //Manipulator library for........ manipulation of the input/output stream. Who would've guessed?
using namespace std;

int rollDice (int& die_roll); //Function for simulating and returning the rolling value of dice
bool playGame (bool& result); //Function for returning a win or loss to the main

int main()
{
  srand(time(0)); //Initializes the generation of random numbers throughout the main

  int sweetbabyjesus = 0; //Variable used to store how many times to play the game
  int wins = 0; //Variable used to keep track of wins, initialize as zero to avoid junk
  int losses = 0; //Variable used to keep track of losses, initialize as zero to avoid junk
  bool outcome = false; //Variable that will be used to get the win/loss reference from the playGame function
  double probabilityW = 0.000; //Variable that will be used to store the probability of winning
  double probabilityL = 0.000; //Variable that will be used to store the probability of holding that 'L'

  //Asks the user how many games of craps they wish to play then stores their input as an integer
  cout << "How many games of 'Craps' do you wish to play?" << endl
       << "Games: ";
  cin >> sweetbabyjesus;

  //This for loop will repeat the game of Craps until it satisfies the user's input
  //While our gameplay loop is less than the user's input, we will keep calling the Craps game function
  //and increase our loop counter by one, keeping and storing the amounts of simulated wins and losses
  for (int i = 1; i <= sweetbabyjesus; i++)
    {
      playGame(outcome); //Calls the Craps simulation function
      
      if (outcome == 1)
	{
	  wins++; //Increases the wins counter by one if this condition is true
	}
      else if (outcome == 0)
	{
	  losses++; //Increases the losses counter by one if this condition is true
	}
    }

  //This section calculates the probability of winning and losing in relation to the amount of games simulated
  //If the win/loss results result in a proper fraction, we will calculate the probability in the following manner
  if (wins <= losses)
    {
      probabilityW = ((double)wins / (wins + losses)) * 100;
      probabilityL = 100 - probabilityW;
    }
  //If the win/loss results result in an improper fraction, we will do the opposite of the division above so that we don't get probabilities > 100%
  else if (wins > losses)
    {
      probabilityW = ((double)losses / (wins + losses)) * 100;
      probabilityL = 100 - probabilityW;
    }

  //This section displays the probability results to the user
  cout << endl << left << setw(10) << "Win %" << left << setw(10) << "Lose %" << endl;
  cout << fixed << setprecision(3) << left << setw(10) << probabilityW << probabilityL << endl;

  return 0;
}

/******************************************
This function simulates rolling a pair of dice.
It returns a random number between 2 and 12.
******************************************/
int rollDice(int& die_roll)
{
  die_roll = (rand() % 6 + 1) + (rand() % 6 + 1); //Simulates the rolling of two 6 faced die

  return die_roll;
}

/******************************************
This function will simulate one game of
Craps. Like you give a crap :^(
******************************************/
bool playGame (bool& result)
{
  int first_roll; //Stores the value of the first dice roll
  int next_roll; //Stores the roll after the first roll
  bool complete = false; //Boolean used to check if the game has been won/lost or not

  rollDice(first_roll); //Starts and stores the value of the first roll by calling the function that simulates... rolled dice (two)

  do
    {
      if (first_roll == 7 || first_roll == 11 || next_roll == first_roll) //Defines and checks the winning conditions for craps
	{
	  result = true; //Acts as the winning condition '1'
	  complete = true; //Returns true, or 1, which tells the program that the game is over and done (puts us out of the "do-while" loop)
	}
      else if (first_roll == 2 || first_roll == 3 || first_roll == 12 || next_roll == 7) //Defines and checks the losing conditions for craps
	{
	  result = false; //Acts as the losing condition '0'
	  complete = true; //Returns false, or 0, which tells the program that the game is over and done (puts us out of the "do-while" loop)
	}

      rollDice(next_roll); //When the above conditions fail, the dice will continue to be rolled until an above condition is satisfied

    }while(complete != true); //The above conditions/simulation will continue until true (game complete) is returned to the function

  return result; //Returns the win/loss condition to the main
}
