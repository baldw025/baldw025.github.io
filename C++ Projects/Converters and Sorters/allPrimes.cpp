/**********************************
This program creates a table with all prime numbers ranging from 0 - 1000.
***********************************/

#include <iostream>
#include <iomanip>
#include "myMeth.h"
using namespace std;
int isPrime(int num);

int main()
{
  int step = 0; //Step counter for inputs per row
  int counter = 0; //Loop counter for final output

  for (int num = 2; num <= 1000; num++) //Using prime numbers from 2 to 1000
    {
      if (isPrime(num) == true && step != 10) //While the number is prime and there are less than 10 numbers per line, we will output the humber the table
	{
	  counter++;
	  cout << right << setw(3) << num << "   "; //Outputs the number with a fixed 3-wide space at the front and rear for beauty
	  step++; //Increases the step count by 1
	}
      else if (step == 10) //When there are 10 numbers displayed on the current line, we will start a new line and restart the step counter
	{
	  cout << endl;	  
	  step = 0;
	} 
    }

  cout << endl << endl; //Thank goodness

  cout << "There are " << counter << " prime numbers between 2 and 1000" << endl << endl;

  return 0;
}
