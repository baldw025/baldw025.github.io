/***************************
This program will get 2 numbers from the keyboard and output the average number.
***************************/
#include <iostream>
using namespace std;

int main()
{
  int num1;
  int num2;
  int sum;
  double avg;

  cout << "Enter a number of your choosing: ";
  cin >> num1;
  cout << "Enter the second number of your choosing: ";
  cin >> num2;

  sum = num1 + num2;
  avg = sum / 2.0;

  cout <<"The average of the two numbers is " <<avg <<endl;
  
  return 0;
}
