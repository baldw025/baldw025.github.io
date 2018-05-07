/*********************************************************************************************
This program will take in an unknown number of user-input ages, calculate their averages, then display the average age, how many ages are adults and minors, and which ages are the oldest and youngest. 
*********************************************************************************************/

#include <iostream>
using namespace std;

int main()
{
  int adults = 0; //Initializes the adults counter to '0'. This stores ages >= 18
  int age; //Stores the user's age input, which will then impact what happens throughout the programerino
  int minors = 0; //Initializes the minors counter to '0'. This stores ages < 18
  int loop = 0; //Loop counter for usage in calculating the average age
  int oldest = -1; //Initializes the oldest age to '-1'. Condition and logic-wise, you will not be considered old if you're still in the womb (-1).
  int total = 0; //Initializes the total counter to '0'. Keeps track of the total of the input ages
  int youngest = 200; //Initializes youngest age to '200'. Like the Sole Survivor. Condition and logic-wise, you will not be considered young at the the pruny age of 200.
  float average = 0.00; //Initializes the average to 0.00. Because I can and for uniformity. Will store the average of the ages.

  //Getting and storing an age from the user
  cout << "Enter an age: ";
  cin >> age;
  
  while (age >= 0) //While the user continues to enter a positive number for an age, the following code will be executed and looped
    {
      loop ++;
      total = total + age;

      if (age >= 18) //If the input age is greater than or equal to 18, the age will register as an adult and process the following spaghetti
	{
	  adults++;
	  if (age > oldest && loop == 1) //If an adult age is the VERY FIRST input age, it will be stored as the oldest and youngest age. This also aids in proper final outputs if only adult ages were entered during the run.
	    {
	      oldest = age;
	      youngest = age;
	    }
	  else if (age > oldest) //If the next adult age is greater than the current oldest age, it will replace that value
	    {
	      oldest = age;
	    }
	  else if (age < youngest) //If the next adult age is less than the current youngest age, it will replace that value 
	    {
	      youngest = age;
	    }
	}

      else if (age < 18) //If the input age is less than 18, the age will register as a minor and process the following spaghetti MKII
	{
	  minors++;
	  if (age < youngest && loop == 1) //If a minor age is the VERY FIRST input age, it will be stored as the oldest and youngest age. This also aids in proper final outputs if only minor ages were entered during the run.
	    {
	      youngest = age;
	      oldest = age;
	    }
	  else if (age > oldest) //If the next minor age is greater than the current oldest age, it will replace that value
	    {
	      oldest = age;
	    }
	  else if (age < youngest) //If the next minor age is less than the current youngest age, it will replace that value
	    {
	      youngest = age;
	    }
	}
      cout << "Enter an age: ";
      cin >> age;
    }

  if (age < 0 && loop == 0) //This condition will be true if the user initially enters a negative value (doesn't enter the age input while loop)
    {
      cout << "No ages were entered." << endl << endl;
    }
  else //Whenever the user inputs a negative number while in the while loop, the program will terminate and output the following age statistics
    {
      average = (float)total / (float)loop;
      cout << endl << average << " (average)" << endl;
      cout << minors << " (minors)" << endl;
      cout << adults << " (adults)" << endl;
      cout << oldest << " (oldest)" << endl;
      cout << youngest << " (youngest)" << endl;
    }

  return 0;
}
