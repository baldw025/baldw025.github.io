/****************************************************************************************************************************
This program will ask for a time in 2 integers (hours - minutes) and will tell the angles of the hour and minute hands on the clock at the given time.
****************************************************************************************************************************/
#include <iostream> //Initializes the input/output stream
#include <iomanip> //Library used for the manipulation of the namespace
/*include <prayers>*/
using namespace std; //Sets the namespace to standard

int main()
{
  const int MIN_HAND_DEG_PER_MINUTE = 6; //Keeps track of how many degrees the minute hand moves per minute
  const float HOUR_HAND_DEG_PER_MINUTE = 0.5; //Keeps track of how many degrees the hour hand moves per minute
  const int HOUR_HAND_DEG_PER_HOUR = 30;
  int hour; //Stores the user's hour input as an integer
  int min; //Stores the user's minute input as an integer
  int adjusted; //Reinforcements
  float hour_degree; //Stores the calculated hour hand degress as a 32-bit (float) value
  float min_degree; //Stores the calculated minute hand degrees as a 32-bit (float) value
  
  //Process to get the user's hour and minute input
  cout << "Enter hours: " << endl;
  cin >> hour;
  cout << "Enter minutes: " << endl;
  cin >> min;

  //Mathematical process to calculate the degree of the hour and minute hands at the given time(s)
  min_degree = 6 * min;
  adjusted = (60 * hour) + min;
  hour_degree = (hour % 12) * HOUR_HAND_DEG_PER_HOUR + (HOUR_HAND_DEG_PER_MINUTE * min);

  //Displays to the user the angles of the given hour and minute hand
  cout << "The angle of the hour hand is : " << hour_degree << endl;
  cout << "The angle of the minute hand is : " << min_degree << endl;
  
  /*
  //--COMMENT THIS OUT WHEN DONE-- #Debug Testing# --COMMENT THIS OUT WHEN DONE--
  cout << endl << endl << endl;
  cout << "--------------------" << endl;
  cout << "Hour: " << hour << endl;
  cout << "Minute: " << min << endl << endl << endl;
  cout << "Adjusted: " << adjusted << endl;
  cout << "DEG_H: " << hour_degree << endl;
  cout << "DEG_M: " << min_degree << endl;
  cout << "--------------------" << endl;
  */

  return 0; //No errors
}
