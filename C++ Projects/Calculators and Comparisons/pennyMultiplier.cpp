/***********************************************************************
This program will calculate how much a person would earn over a period 
of time if their salary starts as one penny, then doubles every day.
***********************************************************************/

#include <iostream> //If you want a useful and interactive program, you should probably include yhe input output stream
#include <iomanip> //Manipulator for the input output stream. Precisions, widths, the whole nine yards
using namespace std; //Standard namespace

int main()
{
  int days_input; //Stores the user-input days
  int days_list; //Used for equating rows to respective days_input
  float salary = 0.01; //Initial declaration of a variable variable that will hold the adjusted salaries throughout the week
  float total_salary = 0.00; //Stores the total summary for number of days worked

  do
    {
      //Asks the user how many days they worked then stores their input
      cout << "Enter the number of days you worked: ";
      cin >> days_input;

      //Creates rows equivalent to the number of days worked, then displays the respective salary in respect to day worked
      for (days_list = 1; days_list <= days_input; days_list++)
	{
	  total_salary = total_salary + salary;
	  cout << setw(5) << days_list << setw(15) << salary << endl;
	  salary = salary * 2;
	}

    }while (days_input < 1); //If the user inputs a value less than '1', it will be rejected and the 'do' statement will execute again until the user stops being hard-headed

  cout << endl << "Total " << setw(14) << total_salary << endl; //Displays the total salary for 'x' days worked

  return 0;
}
