//This program will grow, shrink, and output a vector based on commands issued in an external text file.
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

void analyzeFile (std::vector<std::string> vec);
void vectorInsert (std::vector<std::string> &vec, std::string word, int index);
void vectorDelete(std::vector<std::string> &vec, int index);
void vectorPrint(const std::vector<std::string> vec);

int main()
{
  std::vector<std::string> V;
  analyzeFile(V);

  return 0;
}

//Read from the input file and call the respective function(s) in respect to read command
void analyzeFile(std::vector<std::string> vec)
{
  std::ifstream fin;
  std::string command;
  std::string word;
  int index;

  fin.open("vectorData.txt");
  {
    if (!fin)
      {
	std::cout << "The file can not open or does not exist.\n\n";
      }
    else
      {
	fin >> command;

	while (fin)
	  {
	    if (command == "Delete")
	      {
		fin >> index;
		if (index >= 0) //Only account for positive indices, as per instructions
		  {
		    vectorDelete(vec, index);
		  }
	      }
	    else if (command == "Insert")
	      {
		fin >> word;
		fin >> index;
		if (index >= 0) //Only account for positive indices, as per instructions
		  {
		    vectorInsert(vec, word, index);
		  }
	      }
	    else if (command == "Print")
	      {
		vectorPrint(vec);
	      }

	    fin >> command;
	  }
      }
  }
}

//Inserts a string into its respective index if it's not beyond the current vector size
void vectorInsert(std::vector<std::string> &vec, std::string word, int index)
{
  if (index <= vec.size())
    {
      vec.insert(vec.begin() + index, word);
    }
}

//Erases from an index if it exists in our vector
void vectorDelete(std::vector<std::string> &vec, int index)
{
  //Check if we are deleting a valid index to avoid a segfault
  if (index <= vec.size())
    {
      vec.erase(vec.begin() + index);
    }
}

//Iterate through the vector and output each index. For practice, y'know. And to improve runtime
void vectorPrint(const std::vector<std::string> vec)
{
  //Declare constant string iterator, initialize it to the beginning of main vector, iterate until end index.
  for (std::vector<std::string>::const_iterator iter = vec.begin(); iter != vec.end(); iter++)
    {
      std::cout << *iter << " ";
    }
  std::cout << std::endl;
}
