/*********************
This program will read email addresses from email.dat 
and extract the username and department for each person.

email.dat  (userName.dep@csusm.edu) 
-------------
kslott.cs@csusm.edu
wu.cs@csusm.edu
puha.math@csusm.edu
price.phy@csusm.edu
harrison.eng@csusm.edu
**********************/

#include <iostream>
#include <fstream>
using namespace std;

int main()
{
  string email;
  ifstream fin;
  int length;

  fin.open("email.dat");

  if(!fin)
    {
      cout << "The input file doesn't exist" << endl;
    }
  else
    {
      fin >> email;

      while(fin)
	{
	  length = email.find("."); //Gets and stores the length of the first "." before the employee's department

	  //Outputs the charactrs before the first ".", then reads the next set of characters after the first ".", until we get to the position of "@"
	  cout << email.substr(0, email.find(".")) << " at " <<  email.substr(length + 1, email.find("@") - (length + 1)) << endl; 

	  fin >> email; //Reads the next line in email.dat
	}

      fin.close(); //Closes the file input stream
    }

  return 0;
}
