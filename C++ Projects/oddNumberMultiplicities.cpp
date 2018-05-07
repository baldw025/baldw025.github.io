/*************************************************************************
This program will display the double and triple multiplicities for all odd numbers from 99 down to 1.
************************************************************************/
#include <iomanip>
#include <iostream>
using namespace std;

int main()
{
  int initial;
  initial = 99;
    
  cout << setw(10) << "Number" << setw(10) << "Double" << setw(10) << "Triple" << endl;
  for(initial; initial >= 1; initial-=2)
    {
      cout << setw(10) << initial << setw(10) << initial*2 << setw(10) << initial*3 << endl;
    }

  return 0;
}




