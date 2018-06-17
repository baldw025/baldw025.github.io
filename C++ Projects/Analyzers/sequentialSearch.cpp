/******************************************************
Will fill an array of random numbers and ask the 
user for a number and will check if the number exists in the array.
******************************************************/
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

void fillArray(int ar[], int SIZE);
void printArray(const int ar[], int SIZE);
bool sequentialSearch_bool(const int a[], int s, int k);
int sequentialSearch_int(const int a[], int s, int k);
void sequentialSearch_void(const int a[], int s, int k);

int main()
{
  //declare constant SIZE and set it to 10
  const int SIZE = 10; //constant size for our array indices
  int array[SIZE]; //Declares an array with indices == SIZE
  int key; //Stores the user's key to search for
  bool found; //Tracks whether our key was found or not
  int index; //Stores the index of the key if it was found

  srand(time(0)); //Initializes our random number generaotr

  //calls fillArray to fill the array
  fillArray(array, SIZE);

  //calls printArray to display the array
  printArray(array, SIZE);

  //Asks the user for a key
  cout << "Please enter a number to search for in the array: ";
  cin >> key;
  cout << endl;

  //call sequentialSearch_bool and tell whether the key was found
  found = sequentialSearch_bool(array, SIZE, key);
  
  //If the key was found, say so, if not, say it wasn't found
  if(found == true)
    {
      cout << "Your key(" << key << ") was found in the array." << endl;
    }
  else
    {
      cout << "Your key(" << key << ") was not found in the array." << endl;
    }

  //call sequentialSearch_int and tell where the key was found or say "not found" if key doesn't exist
  index = sequentialSearch_int(array, SIZE, key);

  //If the key is found, say so and the index in which it is located, if not, say it was not found
  if(index != -1)
    {
      cout << "Your key(" << key << ") was found at index " << index << "." << endl;
    }
  else
    {
      cout << "Your key(" << key << ") was not found in any index." << endl;
    }

  //calls sequentialSearch_void to output whether the key was found or not. Because why not
  sequentialSearch_void(array, SIZE, key);

  return 0;
}

/***********************************************************
Fill the integer array with random numbers between 0 and 100.
************************************************************/
void fillArray(int ar[], int SIZE)
{
  //Going through the array, fill all indices with a random number from 0 to 1000
  for(int i = 0; i < SIZE; i++)
    {
      ar[i] = (rand() % 101); 
    }
}

/**********************************************************
Print all the numbers in the array to the screen
**********************************************************/
void printArray(const int ar[], int SIZE)
{
  //Going through the array, output each value stored in the indices
  for(int i = 0; i < SIZE; i++)
    {
      cout << ar[i] << " ";
    }

  cout << endl;
}

/***********************************************************
sequential search: returns true if key exists, otherwise
returns false.

Parameters: a - integer array
            s - size of the array
            k - key
************************************************************/
bool sequentialSearch_bool(const int a[], int s, int k)
{
  //Going through the array, check if an index equals the user's key, return if it was found or not
  for(int i = 0; i < s; i++)
    {
      if(a[i] == k)
	{
	  return true;
	}
    }

  return false;
}

/***********************************************************
sequential search: returns the index where key was found or -1 if not found.

Parameters: a - array
            s - size of array
            k - key
************************************************************/
int sequentialSearch_int(const int a[], int s, int k)
{
  //Going through the array, check if an index equals the user's key, return the index if it was found, -1 if not, no negative indices here boy-o
  for(int i = 0; i < s; i++)
    {
      if(a[i] == k)
	{
	  return i;
	}
    }

  return -1;
}

/***********************************************************
sequential search: void function. Show the result within this function.

Parameters: a - array
            s - size of array
            k - key
            f - found
************************************************************/
void sequentialSearch_void(const int a[], int s, int k)
{
  bool found = false; //You MUST use this boolean variable

  //Do not stay in the for loop after the key was found  
  for(int i = 0; i < s && found != true; i++)
    {
      if(a[i] == k)
	{
	  found = true;
	}
    }

  //tell whether the key was found here
  if(found == true)
    {
      cout << "Your key was found in the array." << endl;
    }
  else
    {
      cout << "Your key was not found in the array." << endl;
    }
}
