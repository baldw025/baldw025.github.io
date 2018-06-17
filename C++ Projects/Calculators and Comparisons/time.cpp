/************************************************************************
This program will ask the user to enter a time in seconds, past midnight, and will return x seconds as hours, minutes, and seconds past midnight.
************************************************************************/
#include <iostream>
using namespace std;

int main()
{
  const int SECONDS_IN_HOUR = 3600; 
  const int MINUTES_IN_HOUR = 60;
  const int SECONDS_IN_MINUTE = 60;
  int seconds_input; //Stores the user's "seconds" input
  int hours; //Stores hours / seconds_input
  int minutes; //Stores minutes / seconds_input
  int seconds; //Stores seconds / seconds_input
  int time; //Stores the converted and remaining time in... REAL-TIME!!! :o

  //Asks and stores the user's input
  cout << "Enter the time in seconds: ";
  cin >> seconds_input;
  cout << endl;

  //Conversion and modding process for hours to minutes to seconds. It. Just. Works. ಠ_ಠ
  hours = seconds_input / SECONDS_IN_HOUR;
  time = seconds_input % SECONDS_IN_HOUR;

  minutes = time / MINUTES_IN_HOUR;
  time = time % MINUTES_IN_HOUR;

  seconds = time;

  //Outputs the converted time in total hours, minutes, and seconds to the user, in verbatim format, because RIP points if we don't 
  cout << hours << " hours " << minutes << " minutes " << seconds << " seconds " << endl << endl;


  
  /*Debug Stuff
  cout << hours << endl;
  cout << minutes << endl;
  cout << seconds << endl;
  cout << time << endl;
  */

  return 0;
}

