/*************************************************************************
This program will output a 9x9 multiplication table
*************************************************************************/
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{ 
  cout << "     1  2  3  4  5  6  7  8  9" << endl;
  cout << "------------------------------" << endl;

  for(int row = 1; row <= 9; row++)
    {
      cout << setw(2) << row << "|";  
      for (int col = 1; col <=9; col++)	
	{
	  cout << setw(3) << col * row;
	}
      cout << endl;
    }


  return 0;
}
