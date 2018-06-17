/**************************
This program will keep track of a vendor's salsa sales. 
We will show how many jars of each salsa were sold and
what the most/least popular salsas are. Vámonos!
**************************/

#include <iostream> //A shallow stream, unlike its river counterpart
#include <iomanip> //Manipulation of the stream so it can become a river
using namespace std; //The namespace still needs medical attention

const int INDICES = 5; //Global constant specifically used for the parallel array sizes.

void fillJarsSoldArray(string sauce[INDICES], int sold[INDICES]);
void printSales (string sauce[INDICES], int sold[INDICES]);
int getTotal (int sold[INDICES]);
void getHighestLowestSelling (int &most, int &least, int sold[INDICES]);

int main()
{
  int highest; //Stores the index value of the highest selling salsa
  int lowest; //Stores the index value of the least selling salsa
  int total; //Stores the total amount of jars sold
  string salsa[INDICES] = {"Mild", "Medium", "Sweet", "Hot", "Zesty"}; //Initializes the salsa name array with an index of 5 and respective salsa names
  int sales[INDICES]; //Creates an array of index 5 that will store user-input sales/salsa

  fillJarsSoldArray(salsa, sales); //Calls the function that will ask the user about salsa sales and will store their inputs
  printSales (salsa, sales); //Calls the function that will print out the sales for each salsa type
  total = getTotal(sales); //Calls the function that will calculate and return the total amount of salsa jars sold
  getHighestLowestSelling(highest, lowest, sales); //Calls the function that will determine which salsa sold the most and return the proper index value

  //This section outputs the total jars sold, and the least/most sold salsa types
  cout << "\nThe total number of jars sold is: " << total << endl
       << "The best-selling selling salsa type is: " << salsa[highest] << endl
       << "The least-selling salsa type is: " << salsa[lowest] << endl;

  return 0;
}

/***************************************************
This function will ask the user to input the amount
of jars/salsa sold. It will then store their inputs
into the proper array. Negative jar amounts will be
rejected.
***************************************************/
void fillJarsSoldArray(string sauce[INDICES], int sold[INDICES])
{
  int input;

  //Going through the entire array index, we will replace each index with a user-defined value
  for(int i = 0; i < INDICES; i++)
    {
      do
	{
	  cout << "Enter the number of jars sold for " << sauce[i] << ": ";
	  cin >> input;
	  sold[i] = input;

	}while(input < 0); //Reject all inputs that make this statement true
    }
}

/***************************************************
This function will display the amount of sales per
salsa in relevance to the user's inputs. 
Lookin' all nice and all.
***************************************************/
void printSales (string sauce[INDICES], int sold[INDICES])
{
  cout << endl << endl;

  //Arrays are in parallel, so one for loop is enough to scan through and output the array indices
  for(int i = 0; i < INDICES; i++)
    {
      cout << left << setw(20) << sauce[i] << setw(20) << sold[i] << endl;
    }
}

/***************************************************
This function will calculate and return the total
amount of salsa jars sold
***************************************************/
int getTotal (int sold[INDICES])
{
  int jars = 0; //Initialize our jar counter to 0 to avoid junk numbers

  //Going through the entire array index, we will add all the array indices for a grand total of jars sold/
  for (int i = 0; i < INDICES; i++)
    {
      jars += sold[i];
    }

  return jars;
}

/***************************************************
This function will determine and return which
salsa sold the most and sold the least. Returns the
index number to the main, which I is requested
in the assignment if I read it correctly. 
I dunno. Please be gentle with the -1's ty.
***************************************************/
void getHighestLowestSelling (int &most, int &least, int sold[INDICES])
{
  int max = -1; //Initialize a variable to test for the initial greatest number in the array
  int min = 99999; //Initialize a variable to test for the initial least number in the array
  
  for (int i = 0; i < INDICES; i++) //Going through the entire array index
    {
      if (sold[i] > max) //If the current value in the array index is greater than the current value stored in max, swap and store the current index
	{
	  max = sold[i];
	  most = i;
	}

      else if (sold[i] < min) //If the current value in the array index is less than the current value stored in min, swap and store the current index
	{
	  min = sold[i];
	  least = i;
	}
    }
}
