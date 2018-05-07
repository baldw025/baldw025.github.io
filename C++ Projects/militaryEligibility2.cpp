/*****************************************************
This program will ask the user to enter his/her age and it will display an age-dependant message.
*****************************************************/
#include <iostream>
using namespace std;

int main()
{
  char gender; //Stores the user's gender
  int age; //Stores the user's age
  int youngage; //Stores the calculated young age

  //Asks the user for their gender
  cout << "Please enter your gender, using 'M' for Male or 'F' for Female: " << endl;
  cin >> gender;
  
  if (gender == 'm' || gender == 'M')
    {
      cout << "Please enter your age: " << endl;
      cin >> age;
      youngage = 17 - age;

      if (age >= 17 && age <=42)
	{
	  cout << "The military is looking for more people like you." << endl;
	}
      else if (age < 16 && age >= 0)
	{
	  cout << "Sorry, but you need to wait " << youngage << " more years before being applicable for the military." << endl;
	}
      if (age == 16)
	{
	  cout << "Sorry, but you need to wait " << youngage << " more year before being applicable for the miltiary." << endl;
	}
      else if (age > 42)
	{
	  cout << "Thank you for using the system." << endl;
	}
      else if (age < 0)
	{
	  cout << "An invalid age was entered. Please try again." << endl;
	}
    }
  else if (gender == 'f' || gender == 'F')
    {
      cout << "Thank you for using the system, but we are only looking for men." << endl;
    }
  else
    {
      cout << "An invalid gender was entered. Please try again." << endl;
    }



  /*
  youngage = 17 - age;

  if (age >= 17 && age <= 42)
    {
      cout << "The military is looking for more people like you." << endl;
    }
  else if (age < 16 && age >= 0) //An unneccessary grammatical fix for when an age = 16. yeears -> year
    {
      cout << "Sorry, but you need to wait " << youngage << " more years before being applicable for the military.\
" << endl;
    }
  if (age == 16) //An unneccessary grammatical fix for when an age = 16. yeears -> year
    {
      cout << "Sorry, but you need to wait " << youngage << " more year before being applicable for the military."\
	   << endl;
    }
  else if (age > 42)
    {
      cout << "Thank you for using the system." << endl;
    }
  if (age < 0)
    {
      cout << "An invalid age was entered. Please try again." << endl;
    }
  */

  return 0;
}
