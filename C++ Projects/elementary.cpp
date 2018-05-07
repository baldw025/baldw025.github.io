/******************************************************
A simple addition math game. Asks the user how many questions
they wish to answer and gives feedback on their performance.
******************************************************/

#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
  int n1;
  int n2;
  int questions;
  int loop;
  int answer;
  int input;
  int correct;
  int incorrect;

  srand(time(0));
  loop = 0;
  correct = 0;
  incorrect = 0;

  cout << "How many questions do you want to solve?: ";
  cin >> questions;

  for (loop =1; loop <= questions; loop++)
    {
      n1 = rand() % 10;
      n2 = rand() % 10;
      answer = n1 + n2;

      cout << n1 << " + " << n2 << " = ";
      cin >> input; 

      if (input == answer)
	{
	  correct = correct + 1;
	  cout << "Good Job" << endl << endl;
	}
      else
	{
	  incorrect = incorrect + 1;
	  cout << "Correct answer is " << answer << endl << endl;
	}
    }

  cout << "You answered " << correct << " questions correctly and " << incorrect << " questions incorrectly." << endl;

  return 0;


}
