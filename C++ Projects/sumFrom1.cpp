/*********************************************************************
The program should use the for loop to get the sum of all the integers from 1 up to
the user's number.

Has no fail safe or loop.
*********************************************************************/

#include <iostream>
using namespace std;

int main()
{
  int num; //Stores the user's number input
  int sum; //Stores the sum of the input number
  int i;

  //Asks the user for a positive number input and stores it in 'num'.
  cout << "Enter a positive number" << endl;
  cin >> num;
  sum = 0;

  if (num <= 0)
    {
      cout << "Your input '" << num << "' is invalid. Please input a positive number." << endl;
    }
  else
    {
	for (i = 0; i <= num; i++)
	sum = sum + i;
	cout << "The sum of all numbers from 1 to " << num << " is " << sum << "\
." << endl;

    }

 
  return 0;
}
