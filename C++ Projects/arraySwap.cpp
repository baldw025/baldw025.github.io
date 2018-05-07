/*************************************************************
Swapping array indices around, from left to right, right to left.
Interesting one.
*************************************************************/

#include <cstdlib>
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
  srand(time(0)); //Initializes the random number generator
  const int SIZE = 10; //Stores 10 as a constant variable throughout the program for future-proofing
  int swap[SIZE]; //Creates array "swap" with an index of 10
  int temp = 0;

  for (int l = 0; l < SIZE; l++)
    {
      swap [l] = (rand() % 100 + 1);
    }

  for (int l = 0; l < SIZE; l++)
    {
      cout << setw(3) << swap[l];
    }

  cout << endl;

  for (int l = 0, r = SIZE - 1; l <= r; l++, r--)
    {
      temp = swap[l];
      swap[l] = swap[r];
      swap[r] = temp;
    }

  for (int r = 0; r < SIZE; r++)
    {
      cout << setw(3) << swap[r];
    }


  cout << endl;

  return 0;
}
