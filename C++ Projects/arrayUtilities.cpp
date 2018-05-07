/******************************
A program based around modifying numerical array data.
A UI will be displayed to the user asking them to fill an array that they can later sort, get statistics on, and search through.
******************************/

#include <iostream> //Streaming at 2560x1440 @ 144 fps.
using namespace std; //The namespace needs medical attention

void fillArray (int ar[], int SIZE);
double findAverage (int ar[], int SIZE);
int findHighest (int ar[], int SIZE);
void doubleArray (int ar[], int SIZE);
void selectionSort (int ar[], int SIZE);
int sequentialSearch (int ar[], int SIZE, int key);
void barGraph (int ar[], int SIZE);
void printArray (const int ar[], int SIZE);

int main()
{
  const int SIZE = 5; //A constant used to limit the array to an index size of 5 (0-4).
  int ar [SIZE]; //Declares an array of index 5
  int selection; //Stores the user's selection input
  double average; //Stores the average number of the array
  int highest; //Stores the highest number in the array
  int key; //Stores the user's key/number to search for (Case 7)

  //While the user doesn't quit the program, we will continue to display and ask which function they'd wish to use
  do
    {
      //Displays an array function menu to the user. My, my. So many choices and so little time.
      cout << "\n===============" << endl
	   << "1: Fill the Array" << endl
	   << "2: Print the Array" << endl
	   << "3: Calculate the Average" << endl
	   << "4: Show the Highest Number" << endl
	   << "5: Double Each Number" << endl
	   << "6: Selection Sort in Descending Order" << endl
	   << "7: Sequential Search" << endl
	   << "8: Show Bar Graph" << endl
	   << "9: Quit" << endl
	   << "===============" << endl;

      cout << "Enter your choice: ";
      cin >> selection;
      cout << endl;

      //This switch will determine which function to call in respect to the user's above selection
      switch(selection)
	{
	case 1: //Fills the array with user-defined values
	  fillArray (ar, SIZE);
	  break;

	case 2: //Displays the values stored in the array
	  printArray (ar, SIZE);
	  break;

	case 3:  //Calculates and displays the average number found in the array
	  average = findAverage (ar, SIZE);
	  cout << "The average number is " << average << endl << endl;
	  break;

	case 4: //Calculates and displays what the highest number is in the array
	  highest = findHighest(ar, SIZE);
	  cout << "The highest number is " << highest << endl << endl;
	  break;

	case 5: //Doubles, overwrites, and displays values in the array
	  doubleArray(ar, SIZE);
	  cout << "The array indices have been doubled." << endl << endl;
	  break;

	case 6: //Sorts the array indices from greatest to least
	  selectionSort(ar, SIZE);
	  cout << "The array has been sorted from greatest to least." << endl << endl;
	  break;

	case 7: //Asks the user to input a value to search for in the array and returns if the value was found or not
	  cout << "Please enter a number to search for: ";
	  cin >> key;

	  if(sequentialSearch(ar, SIZE, key) != -1)
	    {
	      cout << endl << key << " was found at index " << sequentialSearch(ar, SIZE, key) << endl << endl;
	    }
	  else
	    {
	      cout << endl << key << " was not found in the array." << endl << endl;
	    }
	  break;

	case 8: //Displays a "bar graph" that is in relation to the array index values. One asterisk = 10
	  barGraph(ar, SIZE);
	  break;

	case 9: //#wastehistime2017
	  cout << "Thank you for using our system." << endl << endl;
	  break;

	default: cout << "Invalid Choice. Please enter a selection choice ranging from 1 - 9." << endl << endl; //If the user enters a selection choice != 1-9
	  break;
	}
    }while(selection != 9); //We will continue to ask the user for a selection choice until the user quits the program

  return 0;
}

/***********************************************
This function will fill the main array with
user-defined values
***********************************************/
void fillArray (int ar[], int SIZE)
{
  for (int i = 0; i < SIZE; i++) //Starting at 0, until we get five inputs, ask the user to input a number
    {
      cout << "Enter a number: ";
      cin >> ar[i]; //Stores the user's input into the array index
    }
}


/***********************************************
This function will display all the numbers
in the array to the user
***********************************************/
void printArray (const int ar[], int SIZE)
{
  cout << "The numbers in the array are: ";

  for (int i = 0; i < SIZE; i++) //Starting at the first index in the array
    {
      cout << ar[i] << " "; //Displays the current value in the index followed by a space. For a e s t h e t i c s
    }
  cout << endl << endl;
}

/***********************************************
This function will fill find the overall average
of the numbers stored in the array and return it
to the main
***********************************************/
double findAverage (int ar[], int SIZE)
{
  int total = 0; //Initialize our total to 0 to avoid junk numbers
  double average = 0.00; //Same as above

  for (int i = 0; i < SIZE; i++) //Starting at the first index in the array
    {
      total = ar[i] + total; //Adds the value stored in the current index to total
    }

  average = (double)total / SIZE; //To attain the average, take the sum of the array and divide it by the array size. Type cast total to get that floating point

  return average;
}

/***********************************************
This function will find the highest number in
the array and return it to the main
***********************************************/
int findHighest (int ar[], int SIZE)
{
  int highest = -1; //Initialize our highest variable to avoud junk numbers

  for (int i = 0; i < SIZE; i++) //Starting at the first array index
    {
      if (ar[i] > highest)  //If the current value in the array index is greater than the current stored highest, that index will equal the highest. #itjustworks
	{
	  highest = ar[i]; //Yes
	}
    }


  return highest;
}

/***********************************************
This function will physically, irreversably,
permanently, double the values in the array's
indices. What is done cannot be undone. Well, it
could be, but I cba making another function
***********************************************/
void doubleArray (int ar[], int SIZE)
{
  for (int i = 0; i < SIZE; i++) //Starting at the first array index, we will multiply each index by 2 because that's how arithmetic operations work to attain the double of a value. js
    {
      ar[i] = ar[i] * 2; //Above
    }
}

/***********************************************
This function will sort the array indices from
greatest to least
***********************************************/
void selectionSort(int ar[], int SIZE)
{
  int smallest; //the index of the smallest value
  int temp; //temporary variable that holds the smallest value

  //last is the last index in unsorted portion
  for(int last = SIZE-1; last >= 1; last--)
    {
      smallest = 0; //assume the first item is the smallest
      
      //finds the smallest in unsorted portion ([0..last])
      for(int i = 1; i <= last; i++)
        {
          if(ar[i] < ar[smallest]) //The current item is smaller
            smallest = i;
        }

      //swap the smaller with the last item in the unsorted portion
      temp = ar[smallest];
      ar[smallest] = ar[last];
      ar[last] = temp;
    }
}

/***********************************************
This function will search and see if the user's
number is stored somewhere in the array. If not,
tears will be shed.
***********************************************/
int sequentialSearch(int ar[], int SIZE, int key)
{
  int l = 0; //left boudary starts at first index
  int r = SIZE - 1; //right boundary starts at last index
  int m; //middle point between left and right.

  //When l and r cross over, search ends. --> key was not found.
  while(l <= r)
    {
      //calculates the middle point between l and r
      m = (l + r) / 2;

      if(ar[m] == key) //key was found
        {
	  return m;
        }

      else if(ar[m] > key)  //If the key is less than the middle value, we will guide to the left
        {
          r = m - 1;
        }

      else if(ar[m] < key) //If the key is greater than the middle value, we will guide to the right
        {
          l = m + 1;
        }
    }

  return -1; //key wasn't found
}

/***********************************************
This function will display a bar graph
representing numbers in the array. One star/
asterisk = 10.
***********************************************/
void barGraph (int ar[], int SIZE)
{
  for (int i = 0; i < SIZE; i++) //Starting at the first index, increasing by 1 after all the following code is executed
    {
      cout << "Slot " << i << ": ";

      for (int ass = 0; ass < ar[i] / 10; ass++) //Asterisk count starting at 0, increases each time the array index is divisible by 10
	{
	  cout << "*"; //Pretty asterisk
	}
      cout << endl;
    }
}
