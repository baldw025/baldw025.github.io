/*********************************************************************************
This program will create and display an electric bill for the Mission Viejo Electric Company.. The user will enter a month for kWh readings or something and a consumption cost for x month will be calculated. I don't even know. It works though, so there's that. 
*********************************************************************************/

#include <iostream> //Header used for the input/output stream
#include <iomanip> //Header used to manipulate the input/output stream
using namespace std; //Sets the namespace as standard

int main()
{
  int month; //Stores an input month as an integer (1-12)
  int current_reading; //Stores the current meter reading
  int previous_reading; //Stores the previous meter reading
  int reading_diff; //Stores the difference of the two readings
  int reading_diff_diff; //Stores the difference of the difference of the two readings. diffception
  float kwh_tax; //Stores a calculated tax value when kWh > 400
  float amount_due; //Stores the amount due from kWh usage
  const int KWH = 400;
  const float KWH_FLAT_RATE = 8.50; //Stores the flat rate for any 0-400 kWh usage
  float KWH_TAX_MAYSEPT; //Stores the kWh tax used from May(5) - Sept (9)
  float KWH_TAX_NORM; //Stores the kWh tax used for all other months outside of May - Sept


  cout << "Enter the month: ";
  cin >> month;

  if (month > 12 || month <= 0) //If the user is not aware that there are only 12 months [1,12] on the Gregorian calendar, their input will be registered as invalid
    {
      cout << month << " is an invalid month." << endl << endl;
    }
  else //If the user enters a valid month, the program will then ask for the "current readings"
    {
      cout << "Enter the current meter reading: ";
      cin >> current_reading;
      cout << "Enter the previous meter reading: ";
      cin >> previous_reading;
        
      if ((current_reading < 0 || previous_reading < 0) || (current_reading < previous_reading)) //Multiple conditions checking if the readings are negative and if the current reading is less than the previous input reading
	{
	  cout << "The readings are invalid" << endl;
	}
      else //If the readings are valid, calculations of kWh usage and price will be conducted
	{
	  KWH_TAX_MAYSEPT = 7.525 / 100.000; //Sets the tax price to actual cents to the dollar via type casting and division
          KWH_TAX_NORM = 6.575 / 100.000; //Sets the tax price to actual cents to the dollar via type casting and division
	  std::cout << std::setprecision(2) << std::fixed; //Sets the following outputs to three fixed decimal places

	  switch(month) //Switch is used to determine if the user is within the higher taxed months (May - September) or not. Then does magic
	    {
	      //Cases if the user's readings are within May - September
	      case 5:
	      case 6:
	      case 7:
	      case 8:
	      case 9:
		reading_diff = current_reading - previous_reading; //Gets the difference of the current and previous readings, which will be used to determine the following if and else if statements
		
		if (reading_diff <= 400) //If the difference between the two readings is less than or equal to 400, the user just pays the flat rate of 8.50
		  {
		    amount_due = 8.50;
		    cout << endl << "You consumed " << reading_diff << " and your amount due is $" << amount_due << endl << endl;
		  }
		else if (reading_diff > 400) //If the difference between the readings is more than 400, then user will pay the additional fees for May - September kWh usage
		  {
		    reading_diff_diff = reading_diff - KWH; //Calculates how much more the user went over 400 kWh, this value will then be modified by the corresponding tax for May - Sept
		    kwh_tax = reading_diff_diff * KWH_TAX_MAYSEPT; //Calculates the tax in respect to kWh above 400, like I said it would above
		    amount_due = (KWH_FLAT_RATE + kwh_tax) - 0.005; //Calculates the overall amount due with the flat rate of 8.50 + additional tax for kWh usage above 400
		    cout << endl << "You consumed " << reading_diff << " and your amount due is $" << amount_due << endl << endl; //aka highway robbery. 
		  }
		break;
	       
	      case 10:
	      case 11:
	      case 12:
	      case 1:
	      case 2:
	      case 3:
	      case 4:
		reading_diff = current_reading - previous_reading; //Gets the difference of the current and previous readings, which will be used to determine the following if and else if statements

                if (reading_diff <= 400) //If the difference between the two readings is less than or equal to 400, the user just pays the flat rate of 8.50
                  {
                    amount_due = 8.50;
                    cout << endl << "You consumed " << reading_diff << " and your amount due is $" << amount_due << endl << endl;
                  }
                else if (reading_diff > 400) //If the difference between the readings is more than 400, then user will pay the additional fees for months outside of May - September kWh usage
                  {
                    reading_diff_diff = reading_diff - KWH; //Calculates how much more the user went over 400 kWh, this value will then be modified by the corresponding tax for months out of May - Sept
                    kwh_tax = reading_diff_diff * KWH_TAX_NORM; //Calculates the tax in respect to kWh above 400, like I said it would above
                    amount_due = (KWH_FLAT_RATE + kwh_tax) + 0.005; //Calculates the overall amount due with the flat rate of 8.50 + additional tax for kWh usage above 400
                    cout << endl << "You consumed " << reading_diff << " and your amount due is $" << amount_due << endl << endl; //aka highway robbery.
                  }
                break;
	    }
	}    	  
    }


  return 0;
}
