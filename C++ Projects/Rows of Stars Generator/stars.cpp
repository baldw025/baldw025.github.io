
/***************************************************************************************
I accidentally made this when making the ascii table. I don't even know how. But yeah. The user will enter a number greater than 1 and the respective amount of stars will show up in variable amounts of rows.
***************************************************************************************/

#include <iostream>
using namespace std;

int main()
{
  int stars; //Will store the amount of stars the user wishes to display

  //Asks the user how many stars they wish to display then stores their input
  cout << "How many stars would you like to torture the shell with?: ";
  cin >> stars;

  for(int row = 1; row <= stars; row++) //Starting star outputs on the first row, then adding a new row each time the row is less than the needed stars
    {
      for (int col = stars; col >= row; col--) //Begins a column on the first row, 'x' places from the left, where 'x' == the amount of stars to show, then goes back a place for each time the column count is greater than the row amount. Why tho
	{
	  cout << " ";
	}
      for (int col = 1; col <= row; col++) //Does the opposite of above and instead of placing spaces, it places an asterisk. I managed to flip/rotate the star layout both ways horizontally and the standard left-justified vertical position. Every orientation except the desired one in this assignment. I even managed to get the stars structured as claw marks. smh. It works properly now, but I'm still salty. 
        {
          cout << "*";
        }
      cout << endl;
    }

  return 0;
}
