/**********************
Test for a custom header file.
Converts characters to upper, copies characters from other string arrays and checks the length of a string.
**********************/

#include <iostream>
#include "myStrCharFunc.h"
using namespace std;

int main()
{
  char wd[10] = "Hello";
  
  cout << wd << endl; // Hello
  
  myStrcpy(wd, "Hi");
  
  cout << wd << endl; // Hi
  cout << myToUpper('a') << endl; //A
  cout << myToUpper('t') << endl; //T
  cout << myToUpper('Z') << endl; //Z
  cout << myStrlen(wd) << endl; // 2
  
  return 0;
}
