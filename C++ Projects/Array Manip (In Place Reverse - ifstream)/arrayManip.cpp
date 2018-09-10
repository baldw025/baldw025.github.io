//This program will read an array from a file (Max of 10 indices, for now), print it in the buffer, reverse the array in place, and calculate the greatest and least values of the array
#include <iostream>
#include <fstream>
#include <string>

const int SIZE = 10;

void readData(int ar[]);
void printArray(const int ar[]);
void reverseArray(int ar[]);
void minMax(const int ar[], int& minimum, int& maximum);

int main()
{
  int A[SIZE];
  int userInput;
  int min, max;

  readData(A);
  printArray(A);
  reverseArray(A);
  printArray(A);
  minMax(A, min, max);

  std::cout << "Minimum Element: " << min << " | Maximum Element: " << max << std::endl;

  return 0;
}

//Read & store integer data from a file into an array fixed at 10 indices
void readData(int ar[])
{
  std::ifstream fin;
  std::ofstream fout;
  int readNumber;
  int index = 0;

  fin.open("array.txt");
  {
    if(!fin)
      {
	std::cout << "The file does not exist\n";
      }
    else
      {
	while(fin)
	  {
	    fin >> readNumber;
	    ar[index] = readNumber;
	    index++;
	  }
      }
  }
  fin.close();
}

//Loop through the array indices and output their contents
void printArray(const int ar[])
{
  for(int i = 0; i < SIZE; i++)
    {
      std::cout << ar[i] << " ";
    }
  std::cout << std::endl;
}

//Reverse the array in place by setting leftmost indices equal to rightmost indices
void reverseArray(int ar[])
{
  int left = 0; //Leftmost Array Index
  int right = SIZE - 1; //Rightmost Array Index
  int temp; //Temporarly store the value of the current index
  
  //Temporarily store the first index, set last index equal to first index, set first index (temp) to last index
  for(left, right; left <= right; left++, right--)
    {
      temp = ar[left];
      ar[left] = ar[right];
      ar[right] = temp;
    }
}

//Calculates the greatest and least value stored in the array
void minMax(const int ar[], int& minimum, int& maximum)
{
  minimum = 999;
  maximum = 0;

  for(int i = 0; i < SIZE; i++)
    {
      if(ar[i] > maximum)
	{
	  maximum = ar[i];
	}

      else if(ar[i] < minimum)
	{
	  minimum = ar[i];
	}
    }
}
