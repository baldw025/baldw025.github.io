/*****************************************************************
This program will use a multidimensional array to display
students' scores for various tests, along with test average
and student average.
*****************************************************************/ 
#include <iostream>
#include <iomanip>
using namespace std;

const int STUDENT = 5; //Global constant for student count
const int TEST = 3; //Global constant for test amount

void showTable(int scores[STUDENT][TEST]);

int main()
{
  int scores[STUDENT][TEST] = { {45, 67, 78}, {78, 88, 56}, {86, 96, 78}, {78, 77, 67}, {67, 57, 57} }; //Initializes an array with an index of 5 and subarray index of 3, with predfined values 

  showTable(scores); //Calls the function to print the student test score sheet

  return 0;
}

void showTable(int scores[STUDENT][TEST]) //Just passing by the main's subarray values
{
  int total = 0; //Variable used to store the total score per test
  double avg = 0.00; //Variable used to calculate and store the average per test
  int studentTotal = 0; //Variable used to store the total score per student
  double studentAvg = 0.00; //Variable used to calculate and store the average per student
  

  cout << setw(10) << "Test#" << setw(10) << "Stu 1" << setw(10) << "Stu 2" << setw(10) << "Stu 3" 
       << setw(10) << "Stu 4" << setw(10) << "Stu 5" << setw(10) << "Average" << endl;

  //Sets up the three test rows, designated by 1, 2, 3
  for (int t = 0; t < TEST; t++)
    {
      cout << setw(10) << t + 1; //Displays the current test number in relation to the for loop
      total = 0; //Resets the total for the next row

      //Sets up the five student colums and displays the respective scores initialized in the main, 
      //Will continually output the values of the subarray until the parent for loop fails
      for (int s = 0; s < STUDENT; s++)
	{
	  avg = (double)(total += scores[s][t]) / STUDENT; //Average is the total of the total plus scores in the array divided by 5. Wowie
	  cout << setw(10) << scores [s][t]; //Displays the scores located in the main array in respect to the subarray
	}

      cout << setw(10) << fixed << setprecision(1) << avg; //Displays the average to a fixed decimal precision of 1
      cout << endl;
    }

  cout << setw(10) << "Average"; //Starts the next row dedicated to independent student average

  //Starting at scores[0][0], we will add down the column, then move to the next
  for (int col = 0; col < STUDENT; col++)
    {
      studentTotal = 0; //Resets the student total for the next column

      for (int row = 0; row < TEST; row++)
	{
	  studentAvg = (double)(studentTotal += scores[col][row]) / TEST; //Student average is the student's total combined score divided by the three tests
	}

      cout << setw(10) << fixed << setprecision(1) << studentAvg; //Outputs the students' average to a fixed decimal precision of 1.
    }

  cout << endl;
}
