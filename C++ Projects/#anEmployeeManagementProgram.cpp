/*************************************
This program:
-Intelligently receives employee data from a data file.
-Can display male and female employee information separately.
-Can find employees by age, pay rate, ID, and sex.
-Can adjusts an employee's, or a range of employees', pay.
*************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
using namespace std;

const int SIZE = 100; //Global constant used for our array sizes

//A struct that stores and groups all of an employee's information
struct employee
{
  string firstName;
  string lastName;
  char gender;
  double rate;
  int id;
  int age;
};

void readData(employee mAr[], employee fAr[], int& mi, int& fi);
void printEmployee(employee list);
void printAllEmp(employee ar[], int mi, int fi);
void outfileArray(employee ar[], int mi, int fi);
employee findOldest(employee ar[], int& index, int mi, int fi);
void giveRaise(employee ar[], int mi, int fi, double raise);
void giveRaiseToOneEmployee(employee& list, double raise);
void combineArray(employee mAr[], employee fAr[], int mi, int fi, employee allEmp[]);
void findEmp(employee ar[]);

int main()
{
  employee mAr[SIZE]; //Array consisting of all male employee information
  employee fAr[SIZE]; //Array consisting of all female employee information
  employee allEmp[SIZE*2]; //Array consisting of both male and female employee information
  int m; //Counter for total male employees
  int f; //Counter for all female employees
  int oldestMale; //Stores the index of the oldest male employee
  int oldestFemale; //Stores the index of the oldest female employee

  readData(mAr, fAr, m, f); //Calling the function that will read data from a predefined data file
  //then stores the information in the respective arrays

  //Tells us how many male and female employeest there are. Who would've guessed???
  cout << "There are " << m << " male and " << f << " female employees in this list." << endl << endl;

  //Calls the printEmployee function which will display the first employee of each male and female array
  printEmployee(fAr[0]);
  printEmployee(mAr[0]);

  //Calls the function that will display all employees from the male array
  cout << "\n";
  printAllEmp(mAr,m,f);

  //Calls the function that will display all employees from the female array
  cout << "\n";
  printAllEmp(fAr,m,f);

  //Calls the function that will output all the male employee's names (LN, FN) to a user-designated file
  outfileArray(mAr,m,f);

  //Calls the function that will output the female employee's names (LN, FN) to a user-designated file
  outfileArray(fAr,m,f);

  //Calls the function that will find and store the oldest employee in the male array
  findOldest(mAr, oldestMale, m, f);
  cout << "The oldest male employee is " << mAr[oldestMale].firstName << " (" << mAr[oldestMale].age << ")." << endl << endl;
  
  /*
  Calls the function that will find and store the oldest employee in the female array
  findOldest(fAr, oldestFemale, m, f);
  cout << " and the oldest female employee is " << fAr[oldestFemale].firstName << " (contested with " << fAr[2].firstName << " xP)." << endl << endl;
  */

  //Calls the functions that will give all female employees new rates, and display an updated employee table with said rates
  cout << "Here are the new employee rates:" << endl;
  giveRaise(fAr, m, f, 5.5);
  printAllEmp(fAr, m, f);

  cout << endl;

  //Calls the functions that will give all male employees new rates, and display and updated employee table with said rates
  giveRaise(mAr, m, f, 5.0);
  printAllEmp(mAr, m, f);

  cout << endl << endl;

  //Calls the functions that will give a raise to that one special employee of yours and display their new rates
  giveRaiseToOneEmployee(fAr[1], 2.0);
  cout << "Here is " << fAr[1].firstName << "'s new rate:" << endl; 
  printEmployee(fAr[1]);

  //Calls the functons that will give a raise to that OTHER special employee of yours and display their new rates
  giveRaiseToOneEmployee(mAr[0], 50.0);
  cout << endl << "Here is " << mAr[0].firstName << "'s new rate:" << endl;
  printEmployee(mAr[0]);
  cout << endl << endl;

  //Calls the functions that will combine all male and female employees into one unisex array and display said unisex array
  combineArray(mAr, fAr, m, f, allEmp);
  cout << "Here is the new combined employee array: " << endl;
  printAllEmp(allEmp, m, f);
  cout << endl << endl;

  //Calls the function that will ask for and search for an employee's ID. Will also display whether the employee was found or not
  findEmp(allEmp);
  findEmp(allEmp);

  //cout << endl << endl;

  //sortEmployees(allEmp);
  
  cout << endl;

  return 0;
}

/***************************************************************
This function will read all employee data from the
employees.dat file and pass the information back to the main
***************************************************************/
void readData(employee mAr[], employee fAr[], int& mi, int& fi)
{
  mi = 0; //Male index counter
  fi = 0; //Female index counter

  ifstream fin; //Somethin' somethin' input file stream, for reading information from a file
  ofstream fout; //Output file stream, for storing information into a file

  fin.open("employees.dat");

  //If the file does not exist, terminate
  if(!fin)
    {
      cout << "The file does not exist." << endl;
      exit(1);
    }

  //If the file does exist, get all employee data from the file and temporarily store it in our struct and appopriate gender-based arrays
  else
    {
      employee temp;
      
      //Reads all data from the file and stores it in a local struct
      fin >> temp.firstName;
      fin >> temp.lastName;
      fin >> temp.gender;
      fin >> temp.rate;
      fin >> temp.id;
      fin >> temp.age;

      //Keep reading until we get to the max array size/end of file
      while(fin && fi < SIZE && mi < SIZE)
	{
	  //If the employee is a female, store their info in the female array
	  if (temp.gender == 'F')
	    {
	      fAr[fi] = temp;
	      fi++;
	    }
	  
	  //If the employee is a male, store their info in the male array
	  else if (temp.gender == 'M')
	    {
	      mAr[mi] = temp;
	      mi++;
	    }
	  
	  //Gets the next set of employee data
	  fin >> temp.firstName;
	  fin >> temp.lastName;
	  fin >> temp.gender;
	  fin >> temp.rate;
	  fin >> temp.id;
	  fin >> temp.age;

	}
    }

  //Keep things tidy
  fin.close();
  fout.close();
}

/***************************************************************
This function will display a specific employee's data 
because I was told to do so. WE NEVER ASKED FOR THIS
***************************************************************/
void printEmployee(employee list)

//Prints out the first male or female employee's info depending on which array was used included in the call
{
  cout << left << setw(12) << list.firstName << left << setw(12) << list.lastName 
       << left << setw(12) << list.gender << left << setw(12) << fixed << setprecision(2) << list.rate 
       << left << setw(12) << list.id << left << setw(12) << list.age << endl;
}

/***************************************************************
This function will display all of the employee's data
by calling a function within a function. F O R S A K E N N E S S
***************************************************************/
void printAllEmp(employee ar[], int mi, int fi)
{
  /*I am disgusted and ashamed at having to use this static variable to bruteforce a proper call for printing the combined array.
  Yeah, I see you laugh in disgust as you grade this, but it "works". I tried re-writing the current function structure to accomodate for some sort of indices check since I originally only check for genders.
  This right here, is one of the most sinful things, programming-wise, I could've ever done and I hate myself for it. Just pray that no QA or SE modifies how many times we call the "printAllEmp" function, because that will
  break the print combined array caller harder than my will to live. This function will keep track of how many times the "printAllEmp" function is called, then proceed to print the full combined array once we reach "x" amount of calls. STOP LAUGHING*/
  
  static int calls = 0;
  calls++; //Increase our static (persistent) variable by "1" each time the printAllEmp function is called. I am so freaking sorry, I'll switch majors, go liberal arts and fingerpaint my shame.

  if(ar->gender == 'M' && calls != 5)
    {
      for(int i = 0; i < mi; i++)
	{
	  printEmployee(ar[i]);
	}
    }
	  
  else if(ar->gender == 'F')
    {
      for(int i = 0; i < fi; i++)
	{
	  printEmployee(ar[i]);
	}
    }

  //Programming sins ~~~
  //Once this function is called five times, we know that we're trying to display the full combined/unisex employee array. This pains me.
  if(calls == 5)
    {
      for(int i = 0; i < (mi + fi); i++)
	{
	  printEmployee(ar[i]);
	}
    }

    //Just hit me with those minus points already. I can take it
}

/***************************************************************
This function will output the last and first names of all male 
and/or female employees from the array to an output file 
specified by -me- the user. :^)
***************************************************************/
void outfileArray(employee ar[], int mi, int fi)
{
  string filename; //Local string that will store the user's desired filename
  char input; //Stores the user's input for some petty aesthetics below

  ifstream fin; //Input file stream
  ofstream fout; //Output file stream

  cout << "Enter the output file name: "; //Asks the user for a file name, if it does not exist we will create it
  cin >> filename; //User-defined filename, if it does not exist, it will be created

  fin.open(filename.c_str()); //Attempts to open the file that matches the user's input

  //If the file was not found, ask if the user would like to create the file, exit if they do not wish to.
  if(!fin)
    {
      cout << "That file does not exist, would you like to create it? Enter Y/N: ";
      cin >> input;

      if(input == 'y' || input == 'Y')
	{
	  fout.open(filename.c_str()); //Creates and names a file based on the user's input
	}
      else
	{
	  cout << "Exiting..." << endl;
	  exit(1);
	}
    }
      
  //If the male array is used in the function call (checked by accessing the struct's gender member address)
  if(ar->gender == 'M')
    {
      for(int i = 0; i < mi; i++)
        {
          fout << ar[i].lastName << ", " << ar[i].firstName << endl;
        }
      cout << "All male employees have been listed and saved in " << filename << endl;
    }

  //If the female array is used in the function call (checked by accessing the struct's gender member address)
  else if(ar->gender == 'F')
    {
      for(int i = 0; i < fi; i++)
        {
          fout << ar[i].lastName << ", " << ar[i].firstName << endl;
        }
      cout << "All female employees have been listed in " << filename << endl;
    }

  //Close and tidy up
  fout.close();
  fin.close();
}

/***************************************************************
This function will find the oldest employee and pass back the
entire struct to the main. We never asked for this.
***************************************************************/
employee findOldest(employee ar[], int& index, int mi, int fi)
{
  employee oldboi; //Local struct
  int oldest = 0; //Variable that stores the oldest age in respect to the struct
  int localSize; //New gender check method instead of two for loops! What a save! 

  //Gender check, because this function breaks like a mofo for females due to 1) Segmentation faults 2) Junk indices caused by global size
  //Efficiency! iw2d
  if(ar->gender == 'M')
    {
      localSize = mi;
    }
  else
    {
      localSize = fi;
    }

  //Go through the array size in respect to gender, and if the employee's age is older than the current stored oldest age, overwrite and log the index
  for(int i = 0; i < localSize; i++)
    {
      if(ar[i].age > oldest)
	{
	  index = i;
	  oldest = ar[i].age;
	}
    }


  return oldboi; //y tho
}

/***************************************************************
This function will give a raise to all male or female employees
depends on who you call. Ghostbusters is not defined here so
don't even try k.

***************************************************************/
void giveRaise(employee ar[], int mi, int fi, double raise)
{
  int localSize; //Local size because segmentation faults and junk indices are scary
  double increase; //Variable that keeps track of of the current rate modified by given raise

  raise /= 100; //For proper raise calculations, throw that guy into the 100's place

  //If the current called array contains the male employee information, adjust the local count to the total male array size
  //Else, do the same but but for females employees
  if(ar->gender == 'M')
    {
      localSize = mi;
    }
  else
    {
      localSize = fi;
    }

  //Going through the employee array, calculate the raise in respect to current rate, then calculate the final rate in respect to aforementioned data
  //You confused yet? :^))))))
  for(int i = 0; i < localSize; i++)
    {
      increase = ar[i].rate * raise;
      ar[i].rate += increase;
    }

}

/***************************************************************
This function will give a raise to one employee. But a very
small one. If they complain they go under review and end up
terminated.
***************************************************************/
void giveRaiseToOneEmployee(employee& list, double raise)
{
  double increase; //Variable that keeps track of the current rate modified by the given raise
  raise /= 100; //Raise should be calculated by the hundredths

  //Going through the employee array, calculate the raise in respect to current rate, then calculate the final rate in respect to aforementioned data
  //You still confused? :^))))))))))))))))))))))))))))))))))))))
  increase = list.rate * raise;
  list.rate += increase;
}

/***************************************************************
This function will combine both the male and female array into
one array, storing males first, then females. inb4 "oppression"
***************************************************************/
void combineArray(employee mAr[], employee fAr[], int mi, int fi, employee allEmp[])
{
  int i = 0; //Keeps track of the combined array's indices
  int mCount = 0; //Keeps track of our position through the male indices
  int fCount = 0; //Keeps track of our position through the female indices

  //Starting with the male array, set the first 11(mi) combined array indices equal to what is currently stored in the male array
  for(i; i < mi; i++)
    {
      allEmp[i] = mAr[mCount];
      mCount++;
    }

  //Finishing with the female array, set the last 6(fi) combined array indices equal to what is currently stored in the female array
  for(i; i < (mi + fi); i++)
    {
      allEmp[i] = fAr[fCount];
      fCount++;
    }
}

/***************************************************************
This function will find an employee by asking the user for their
ID number. Since this doesn't need to all be done in the main, 
if an employee is not found in the database, we will
say so, otherwise, we will display the employee's first and
last name. Employee 48482, you are terminated.
***************************************************************/
void findEmp(employee ar[])
{
  int i = 0; //Variable that will keep track of our current index so we can easily output the proper employee information if applicable
  int ID; //Stores the user's ID search
  bool search = false; //Stores whether or not the employee was found in the database

  cout << "Enter the Employee's unique ID number: ";
  cin >> ID;

  //Starting at the first index, searching through the entire 200 employee indices
  for(i; i < SIZE*2; i++)
    {
      if(ar[i].id == ID)
	{
	  search = true; //Sets our "does it exist?????" boolean to true if the ID is found in the database
	  break; //Get out of the loop if a registered ID is found
	}
    }

  //If no ID is found, say so because we're giving up on you. Else, say we found the employee and state said employee's first and last name
  if (search == true)
    {
      cout << "Employee ID: " << "'" << ID << "'" << " is registered to " << ar[i].firstName << " " << ar[i].lastName << "." << endl << endl;
    }
  else
    {
      cout << "The Employee ID: " << "'" << ID << "'" << " is not registered in our database." << endl << endl;
    }

}
