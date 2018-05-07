/*************************************************************************
This program will verify the eligibility of joining the military from the
user’s gender and age.
*************************************************************************/

#include <iostream>
using namespace std;

void showProgInfo();
void getInfo(string& name, char& gender, int& age);
bool verifyEligibility(char gender, int age);
void printLetter(char gender, string name, int age, bool eligibility);

int main()
{
  string name;
  char gender;
  int age;
  bool eligibility;

  showProgInfo();

  getInfo(name, gender, age);

  eligibility = verifyEligibility(gender, age);

  printLetter(gender, name, age, eligibility);

  return 0;
}

void showProgInfo()
{
  cout << "****************************************************" << endl;
  cout << "This program will tell you if you are eligible to join the military." << endl;
  cout << "****************************************************" << endl;
}

void getInfo(string& name, char& gender, int& age)
{
  cout << "Enter first name: ";
  cin >> name;
  cout << "Enter gender: ";
  cin >> gender;
  cout << "Enter age: ";
  cin >> age;
}

bool verifyEligibility(char gender, int age)
{
  if (gender == 'm' && age >= 18)
    {
      return true;
    }
  else if (gender == 'f' || age < 18)
    {
      return false;
    }
}

void printLetter(char gender, string name, int age, bool eligibility)
{
  if (eligibility == true)
    {
      cout << "Dear " << name << " Please consider joining the military." << endl;
    }
  else if (eligibility == false)
    {
      cout << "Thank you for appyling, but you are too young to join the military." << endl;
    }
}
