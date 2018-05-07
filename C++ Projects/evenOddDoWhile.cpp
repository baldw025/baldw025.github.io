/*********************************
This program will get an unknown number of user-input numbers and determine which are even/odd along with their average. Entering 0 will terminate this program.
*********************************/

#include <iostream>
using namespace std;

int main()
{
  char input; //Stores the user's continuance input
  int num; //Stores the user's number input
  int even; //Stores the amount of even inputs
  int odd; //Stores the amount of odd inputs
  int total; //Stores the total of the inputs
  int loop; //Keeps track of how many times the program has looped
  float average; //Stores the average of the number inputs

  //Initializes all the above variables as 0, so we don't get random "junk" numbers 
  loop = 0;
  even = 0;
  odd = 0;
  total = 0;
  average = 0.00;

  //Loops in continuum until the user enters a zero
  do
    {
      cout << "Do you have a number to check? y/n: " << endl;
      cin >> input;
      
      if (input == 'y')
	{
	  loop++;
	  cout << "Enter a number: ";
	  cin >> num;
	  if(0 == num % 2)
	    {
	      even = even + 1;
	      total = total + num;
	      cout << num << " is even." << endl << endl;
	    }
	  else
	    {
	      odd = odd + 1;
	      total = total + num;
	      cout << num << " is odd." << endl << endl;
	    }
	}
      else  if (input == 'n' && loop != 0)
	{
	  average = (float)total / loop;
	  cout << even << " even numbers" << endl;
	  cout << odd << " odd numbers" << endl;
	  cout << "The average is " << average << endl;
	}
       else
	 {
	   cout << "No numbers were checked." << endl;
	   return 0;
	 }
    }while (input != 'y' || input != 'n');


  return 0;
}
