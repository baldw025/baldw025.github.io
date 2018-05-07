/********************************
This program will create an array with various numerical data. The user can later enter a numerical key to search for and see if
it exists within our data array.
********************************/

#include <iostream>
using namespace std;

int binarySearch(const int a[], int s, int key);

int main()
{
  const int SIZE = 10;
  int ar[SIZE] = {90, 80, 70, 60, 50, 40, 30, 20, 10, 1};
  int key;

  cout << "Enter key: ";
  cin >> key;

  if(binarySearch(ar, SIZE, key) != -1)
    {
      cout << key << " was found at index " << binarySearch(ar, SIZE, key) << " in the array."  << endl;
    }
  else
    {
      cout << key << " was not found in the array." << endl;
    }

  return 0;
}

//This function returns the index where key is found or -1 if key is not found.
//s is the size of the array.
//key is the number being searched for.
int binarySearch(const int a[], int s, int key)
{
  int l = 0; //left boudary starts at first index
  int r = s - 1; //right boundary starts at last index
  int m; //middle point between left and right.

  //When l and r cross over, search ends. --> key was not found.
  while(l <= r)
    {
      //calculate the middle point between l and r
      m = (l + r) / 2;

      if(a[m] == key) //key was found
        {
        return m;
        }

      else if(a[m] < key)
        {
          r = m - 1;
        }

      else if(a[m] > key)
        {
          l = m + 1;
        }
    }

  return -1; //key wasn't found
}


