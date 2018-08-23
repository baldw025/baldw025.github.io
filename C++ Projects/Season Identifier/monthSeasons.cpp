/*******************************************************
This program will ask for a month and tell the season the month lays in.
*******************************************************/
#include <iostream>
using namespace std;

int main()
{
  int month; //Stores the month that the user inputs (1=Jan 2=Feb, etc...)

  cout << "Please enter a month. Using '1' for January, '2' for February, and etcetera: " << endl;
  cin >> month;

  switch(month)
    {
    case 12:
    case 1:
    case 2: cout << "It's a Winter Wonderland" << endl;
      break;
    case 3:
    case 4:
    case 5: cout << "It's Spring!" << endl;
      break;
    case 6:
    case 7: 
    case 8: cout << "Hot hot Summer." << endl;
      break;
    case 9: 
    case 10:
    case 11: cout << "Falling falling Fall." << endl;
      break;
    default: cout << "An invalid month was entered. Please try again." << endl;
    }



  return 0;
}
