/********************************************************************
This program will convert a user-given temperature from Celsius to Fahrenheit and vice-versa and display the conversion within two decimal places.
********************************************************************/
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{ 
  char celsiheit; //Stores the user-input temperature (C or F)
  int celsius; //Stores the user-input temperature (C)
  int fahrenheit; //Stores the user-input temperature (F)
  float c_converted; //Stores the final converted temperature (C to F)
  float f_converted; //Stores the final converted temperature (F to C)

  //Asks the user to enter a temperature scale to convert from, then stores their input
  cout << "Which temperature do you have? Enter F for Fahrenheit or C for Celsius: ";
  cin >> celsiheit;

  
  switch(celsiheit)
    {
      case('C'): //If the user initially entered 'C' to convert from Celsius to Fahrenheit
	cout << "Enter a temperature in Celsius: "; //Asks the user for their temperature in Celsius
	cin >> celsius;
	c_converted = (1.8 * celsius) + 32; //Formula used to convert the user's Celsius temperature to Fahrenheit
	cout << celsius << " Celsius = " << setprecision(2) << fixed << c_converted << " Fahrenheit" << endl; //Outputs the converted temperature up to two decimal places k.
      break; //If 'C' is not satisfied, moves to next case

      case('F'): //If the user initially entered 'F' to convert from Fahrenheit to Celsius
	cout << "Enter a temperature in Fahrenheit: "; //Aks the user for their temperature in Fahrenheit
	cin >> fahrenheit;
	f_converted = 0.5556 * (fahrenheit - 32); //Formula used to convert the user's Fahrenheit temperature to Celsius
	cout << fahrenheit << " Fahrenheit = " << setprecision(2) << fixed << f_converted << " Celsius" << endl;
      break;

      default: cout << "Invalid choice" << endl; //If all the above cases fail because the user is incompetent and cannot read at a 2nd grade level
    } 

  return 0;
}
