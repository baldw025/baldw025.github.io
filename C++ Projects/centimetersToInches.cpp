/**********
This program will take a user-input length in centimetres and convert and display it in inches.
**********/

#include <iostream> //Initializes the input/output stream for cin cout
using namespace std; //Sets the namespace to standard

int main()
{
  const int IN_IN_YARD = 36;
  const int IN_IN_FOOT = 12;
  const int FOOT_IN_YARD = 3;
  const float CM_TO_IN = 2.54; //Stores the conversion for centimeters to inches
  int cm; //Stores the user's input length (cm)
  int yards; //Stores the conversion in yards
  int feet; //Stores the conversion in feet
  float in; //Stores the converted cm input
  int in2; //Stores a second istance of "in"
  int in_rounded; //Stores the converted and rounded centimeter input
  int measurement; //~Magic~ Variable

  ///////////////////////////////// Display a message asking for user-input, then stores user's input
  cout << "Hello! Please input a length in centimeters. I will then convert and round it to inches: " <<endl;
  cin >> cm;

  ///////////////////////////////// Converts and rounds the user's input to inches, rounded to the nearest tenth
  in = cm / (CM_TO_IN);
  in_rounded = int(in + 0.5);
  measurement = in_rounded;

  ///////////////////////////////// Converts inches to yards + rounding
  yards = measurement / IN_IN_YARD;
  measurement  = measurement % IN_IN_YARD;

  ///////////////////////////////// Converts inches to feet + rounding
  feet = measurement / IN_IN_FOOT;
  measurement = measurement  % IN_IN_FOOT;

  ///////////////////////////////// Converts ###
  in2 = measurement / 1;

  ///////////////////////////////// Outputs the converted and rounded measurements
  cout << "Your measurement is " << in << " inches, rounded to " << in_rounded << ". ";
  cout << "This is equivalent to " << yards << " yards, ";
  cout << feet << " feet, ";
  cout << "and " << in2 << " inches." << endl;

  return 0; //No errors
}
