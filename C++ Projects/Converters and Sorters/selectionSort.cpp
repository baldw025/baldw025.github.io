/*********************************
Fills and sorts an array from greatest to least
**********************************/

#include <iostream>
#include <cstdlib>
using namespace std;

void selectionSort(int array[], int N);

int main()
{
  srand(time(0));

  const int SIZE = 10;

  //declare an array using SIZE
  int ar[SIZE];

  //fill the array with 10 random numbers between 0 and 100
  for (int i = 0; i < SIZE; i++)
    {
      ar[i] = rand() % 101;
    }

  //call selectionSort
  selectionSort(ar, SIZE);

  //print the array
  for (int i = 0; i < SIZE; i++)
    {
      cout << ar[i] << " ";
    }

  cout << endl;

  return 0;
}

//change this function so it will sort the numbers in descending order: largest down to smallest
void selectionSort(int array[], int N) 
{
  int smallIndx; //the index of the smallest value
  int temp; //temporary variable that holds the smallest value

  //last is the last index in unsorted portion
  for(int last = N-1; last >= 1; last--) 
    {
      smallIndx = 0; //assume the first item is the smallest
      //find the smallest in unsorted portion ([0..last])
      for(int i = 1; i <= last; i++) 
	{
	  if(array[i] < array[smallIndx]) //The current item is smaller 
	    smallIndx = i;
	}

      //swap the smaller with the last item in the unsorted portion
      temp = array[smallIndx]; 
      array[smallIndx] = array[last]; 
      array[last] = temp;
    } 
}
