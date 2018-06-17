/*********************************
This program will create a mail order receipt/invoice for the seller and/or buyer.
There will be various discounts for the different months, a shipping calculator by pound, and a sales tax dependent on the buyer's county
*********************************/

//Souce Inclusions//
#include <iostream> //I suggest including the input/output library for an "interactive" program with user input and program output
#include <iomanip> //Manipulator library for the input/output stream. Used for fixed decimal places in this case.
using namespace std; //Sets the entire namespace to standard

//Function Prototypes//
void getCustomerInfo (int& accountNum, int& month, int& day, int& year, char& countyCode, string& countierCode);
void getItemsInfo (double& price, int& weight);
double calcDiscount (int month, double totalPrice, double& totalDiscount);
double calcSalesTax (char countyCode, double totalPrice, double totalDiscount, double& govFunding);
double calcShipping (int weight, double& w8m8);
void outputInvoice (int accountNum, int month, int day, int year, double totalPrice, double totalDiscount, double govFunding, double w8m8, double& totalDue, string countierCode);

int main() //The main function that brings all the other functions to the yard, with some calculations and declarations included
{
  int acc; //Stores the buyer's account number referenced from the customer info function
  int m; //Stores the referenced purchase month from the customer info function
  int d; //Stores the referenced purchase day from the customer info function
  int y; //Stores the referenced purchase year from the customer info function
  char cC; //Stores the the buyer's county code referenced from the customer info function
  string cCC;
  double totalPrice; //Stores the total price of the user's order as a 64-bit floating point 
  int totalWeight; //Stores the total weight of the user's order as an integer, we are assuming these are in pounds (lbs.)
  double discount; //Stores the total discount on total price before tax
  double salesTax; //Government Funding Simulator 2018, stores the sales tax on the total price after discount takes effect
  double shipping; //Stores the shipping cost in respect to totalWeight
  double totalEverything; //Stores the absolute upmost total due after discounts, sales tax, and shipping fees

  getCustomerInfo(acc, m, d, y, cC, cCC); //Gets and stores the referenced values from the customer info function into the main
  getItemsInfo(totalPrice, totalWeight); //Gets and stores the user/customer's item price(s) and weight(s)
  discount = calcDiscount(m, totalPrice, discount); //Calls the function to calculate the order discount in respect to the month
  salesTax = calcSalesTax(cC, totalPrice, discount, salesTax); //Calls the function to calculate the sales tax in respect to county
  shipping = calcShipping(totalWeight, shipping); //Calls the function to calculate shipping costs in respect to weight
  outputInvoice (acc, m, d, y, totalPrice, discount, salesTax, shipping, totalEverything, cCC); //Calls the function that will get all the user's input information and generate a invoice/receipt that reflects said information

  return 0; //Reports back with no erros
}

/********************************************************************
This function will ask the seller to input the buyer's account number,
the date of sale as three integers (requested in the assignment k), and
the buyer's country code. Will return to main
********************************************************************/

void getCustomerInfo(int& accountNum, int& month, int& day, int& year, char& countyCode, string& countierCode) //Variables will be refernced to the main
{
  bool valid; //This will keep track of the validity (satisfied conditions) of the user's inputs

  valid = false; //We will initialize the valid boolean to false (0), to prevent false-positive validity checks 

  //Asks the user to input the buyer/customer's account number
  cout << "Enter the customer's account number: ";
  cin >> accountNum;

  do
    {
      //Here, we will ask the user to enter the customer's purchase date as three seperate integers as that was asked in the assignment
      cout << endl << "Enter the month, day, and year of this sale (MM/DD/YYYY): ";
      cout << endl << "Month (MM): ";
      cin >> month;
      cout << "Day (DD): ";
      cin >> day;
      cout << "Year (YYYY): ";
      cin >> year;

      //If the user enters an invalid date format (invalid month (13), day (32), etc) we will ask the user to re-enter the date,
      //otherwise, the valid boolean will be set to true and break out of the do-while loop
      if (month >= 1 && month <= 12 && day >= 1 && day <= 31 && year >= 1901 && year <= 2077) //Because Great War of 2077
        {
          valid = true; //Sets the valid boolean to true, advancing the program
          continue; //Tells the program to continue, useful if there's nothing you'd like to set/adjust if the condition is satisfied
        }
      else
	{
	  cout << "An invalid date was entered. Please enter a valid date in the format MM/DD/YYYY." << endl; //Tells the user the date is invalid and the proper format
	}

    }while(valid != true); //The condition which must be broken for us to break out of the do-while loop

  valid = false; //Reset the valid boolean to false (0), to prevent false-positive validity checks

  do
    {
      //After a valid date is entered we will ask the user to input the customer's county code
      cout << endl << "Enter the customer's county code" << endl
	   << "============================" << endl
	   << "Input 'S' for San Diego" << endl
	   << "Input 'O' for Orange County" << endl
	   << "Input 'L' for L.A. County" << endl
	   << "============================" << endl << endl
	   << "County Code: ";
      cin >> countyCode;

      //This switch will check for valid inputs, lowercase and uppercase characters that represent an included county are legal (S, s, O, o, L, l), for user-friendliness
      //If the user enters an "illegal" character (Z, r, q, etc.) the switch will resort to default and state invalid county and restart this do-while loop
      //I've also made it so that any valid input character gets converted to its appropriate string. Because why not? A nice UI is a happy UI
      switch(countyCode) 
	{
	case 'S':
	case 's':
	  countierCode = "San Diego";
	  valid = true;
	  break;

	case 'O':
	case 'o':
	  countierCode = "Orange County";
	  valid = true;
          break;

	case 'L':
	case 'l':
	  countierCode = "Los Angeles";
	  valid = true;
	  break;

	default: valid = false; 
	  cout << endl << "An invalid county county code was entered. Please enter a valid country code. " << endl;
	  break;
	}

    }while(valid != true); //The condition which must be broken for us to break out of the do-while loop

}

/********************************************************************
This function will get various item info from the user. This info
includes purchase quantity, price(s) per item, and their weight(s).
It will continue to ask the user if they want to purchase an item until
a "N/No" response is input. Will return to main
********************************************************************/

void getItemsInfo (double& price, int& weight)
{
  char input; //Stores the user's continuance input
  double inputP; //Stores the user's input price
  int inputW; //Stores the user's input weight

  price = 0.00; //Initialize the price to zero to avoid junk numbers, a good and fair practice
  weight = 0; //Initialize the weight to zero to avoid junk numbers and because it was literally Hitler when attempting to debug the shipping function

  cout << endl << "Do you want to order an item? Enter Y or N: ";
  cin >> input;

  while (input == 'Y' || input == 'y') //While the user enters a lowercase or uppercase 'Y' the program will continue to ask for an item price and weight
    {
      cout << "Enter a price: ";
      cin >> inputP;
      cout << "Enter a weight: ";
      cin >> inputW;
      
      //This section adds up the total price and weight in relation to the user's above inputs, then gets stored for future pass by reference
      price = price + inputP;
      weight = weight + inputW;

      //Asks the user if they want to order another item, then stores their answer. If their answer is yes (Y/y), then the while loop will run again
      cout << endl << "Do you want to order another item? Enter Y or N: ";
      cin >> input;
    }
  cout << endl;
}

/********************************************************************
This function will calculate the order's discount in respect to the
current input month. Will return to main
********************************************************************/
double calcDiscount (int month, double totalPrice, double& totalDiscount)
{
  double discount; //Temporarily stores the various discount percentages to aid in calculating the total discount in currency

  //This switch will test the user's month input with the following cases. A matched respective case will then calculate and store the total discount
  switch(month)
    {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5: 
      discount = 0.05;
      totalDiscount = totalPrice * discount;
      break;

    case 6:
    case 7:
    case 8:
      discount = 0.10;
      totalDiscount = totalPrice * discount;
      break;

    case 9:
    case 10:
    case 11:
    case 12:
      discount = 0.15;
      totalDiscount = totalPrice * discount;
      break;
    }

  return totalDiscount;
}

/********************************************************************
This function will calculate the total sales tax of the order
after the discount has taken effect. Will return to main
********************************************************************/
double calcSalesTax (char countyCode, double totalPrice, double totalDiscount, double& govFunding)
{
  double st; //Temporarily stores the various sales tax percentages to aid in calculating county tax

  govFunding = totalPrice - totalDiscount; //Calculates and stores the discounted price (Overall Price minus the discount) as we are applying the county tax to the discounted price

  //This switch will test the user's county input which will apply the respective county tax and sum up the discounted price + county tax
  switch(countyCode)
    {
    case 'S':
    case 's':
    case 'O':
    case 'o':
      st = 0.0775;
      govFunding = govFunding * st;
      break;

    case 'L':
    case 'l':
      st = 0.0825;
      govFunding = govFunding * st;
      break;
    }

  return govFunding;
}

/********************************************************************
This function will calculate the total shipping cost of the order
in respect to the order's reported weight. There is a flat rate if
the item is under 25 pounds, 0.10 cent increase per pound 26 -50, 
and a 0.07 cent increase per pound over 50. Something like that
********************************************************************/

double calcShipping (int weight, double& w8m8)
{
  const double FLAT_RATE = 5.00; //A constant for usage as the flat shipping rate. Could be a global constant, yeah, but that's not "desired" in this course. y tho
  double weightDiff1; //Stores the overall weight difference that is in excess of 25 lbs;
  double weightDiff2; //Stores the second stage weight difference, which is essentially the weight thaat is over 25 lbs
  double weightDiff3; //Stores the third stage weight difference, which is essentially all pounds in excess of 50 lbs

  if (weight <= 25) //If the user's order weight is less than or equal to 25 lbs, it qualifies for just the standard flat rate of 5 dollars
    {
      w8m8 = FLAT_RATE; //Sets the shipping weight costs to the flat rate (5.00)
    }
  else if (weight >= 26 && weight <= 50) //If the user's package is en excess of 25 lbs, but less than 50 lbs, then it will get charged 10 cents for every pound over 25 lbs
    {
      weightDiff1 = weight - 25; //Gets the difference for pounds over 25
      weightDiff2 = weightDiff1 * 0.10; //Calculates the 10 cent addition for every pound over 25
      w8m8 = FLAT_RATE + weightDiff2; //Calculates and stores the final shipping cost for the order (5 dollar flat rate + 0.10 cent charge for every pound over 25
    }
  else if (weight > 50) //If the user's package is in excess of 50 lbs, then it will be charged the flat rate, plus an additional 10 cents for the next 25 lbs, plus 7 cents for every pound over 50 lbs
    {
      weightDiff1 = weight - 25; //Gets the difference for pounds over 25 lbs
      weightDiff2 = weightDiff1 - 25; //Gets the difference again for the adjusted weight in excess of 25 for second stage weight calculations
      weightDiff2 = weightDiff2 * 0.10; //Calculates and stores second stage weight for the second set of 25 lbs in the order
      weightDiff3 = weight - 50; //Gets the difference for pounds over 50 lbs
      weightDiff3 = weightDiff3 * 0.07; //Calculates and stores the third stage weight difference
      w8m8 = FLAT_RATE + weightDiff2 + weightDiff3; //Adds up the monstrosity above and stores it as the final overall shipping cost
    }
  return w8m8;
}

/********************************************************************
This functions will get *all* of the user's inputs and output them
into a nice pretty order invoice format for records and such. It will
also calculate the overall overall price of the mailOrder, with 
discount, county tax, and shipping accounted for.
********************************************************************/

void outputInvoice (int accountNum, int month, int day, int year, double totalPrice, double totalDiscount, double govFunding, double w8m8, double& totalDue, string countierCode)
{
  std::cout << std::setprecision(2) << std::fixed; //Sets the rest of the function to output to a fixed decimal precision of 2

  totalDue = w8m8 + govFunding + (totalPrice - totalDiscount); //Calculates and stores the overall ~overall~ total price, which accounts for the discount, shipping fee, and tax

  //Generates an invoice/receipt for the user using previously input values
  cout << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl 
       << "ACCOUNT NUMBER" << setw(36) << right << "COUNTY" << endl
       << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl //Count of 50
       << left << setw(25) << accountNum << right << setw(25) << countierCode << endl << endl
       << "DATE OF SALE " << month << "/" << day << "/" << year << endl << endl
       << left << setw(18) << "Total Sale Amount:" << right << setw(18) << "$ " << right << setw(8) << totalPrice << endl
       << left << setw(18) << "Discount:" << right << setw(18) << "$ " << right << setw(8) << totalDiscount << endl
       << left << setw(18) << "Sales Tax:" << right << setw(18) << "$ " << right << setw(8) << govFunding << endl
       << left << setw(18) << "Shipping:" << right << setw(18) << "$ " << right << setw(8) << w8m8 << endl
       << left << setw(18) << "Total Due:" << right << setw(18) << "$ " << right << setw(8) << totalDue << endl
       << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl << endl;
}
