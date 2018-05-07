/**********
This program will generate a store receipt. Automatically grabs the system time, asks the clerk for the item name and price. Optional unique or fixed clerk name. User-friendly.
**********/
#include <iostream> //Input Output Stream
#include <iomanip> //Manipulator header for IO Stream
#include <ctime> //Header used for getting system time
#include <string> //Header used for string types and conversions
#include <unistd.h> //Header used for sleep function (ms) through the OS API

using namespace std;

int main()
{
  std::cout << std::setprecision(2) << std::fixed; //Sets fixed decimal places to 2 in the standard namespace
  
  //Magical Variables
  time_t now = time(0); //Gets the system time
  char* datetime = ctime(&now); //Converts the system time to a character
  const float TAX_RATE = 7.75; //Defines the tax rate
  string item; //Stores the name of the purchased item
  string clerk; //Stores the clerk's name
  float price; //Stores the purchased item's price as a 32-bit value
  float tax; //Stores the tax as a hundredth float as a 32-bit value
  float salestax; //Stores the calculated tax in relevance to tax rate as a 32-bit value
  float finalprice; //Stores final price including salestax as a 32-bit value
  string vanilla = "DeAndre";
  
  //This is client - clerk chat simulation, for banter
  cout << "Hello! Which car part would you like to purchase today?" << endl;
  getline (cin,item);
  cout << "Excellent choice! That '" << item << "' will make a fine addition to your vehicle!" << endl <<endl <<endl;

  //Information for the clerk to enter
  cout << "(For the Clerk) What is the price of the customer's item?" << endl;
  cin >> price;
  
  //(Optional) cout for unique clerks
  //cout << "(For the Clerk) What is the tending clerk's name?" << endl;
  //cin >> clerk;
  //cout << endl;


  //Calculations for Salex Tax
  tax = TAX_RATE /100;
  salestax = tax * price;
  finalprice = price + salestax;
  
  //Receipt Generation
  cout << "Generating and printing receipt..." << endl << endl << endl;
  usleep(3000000);
  
  cout << "----------------------------------------------------" << endl; //(52)
  cout << "|         iPE Performance Parts and Tuning         |" << endl; //Store Name
  cout << "----------------------------------------------------" << endl << endl; //(52)
  cout << setw(53) << datetime; //Displays system time and date
  //cout << right << setw(42) << "Clerk: " << right << setw(10) << clerk << endl << endl << endl; //(Optional) Displays the unique clerk's name
  cout << right << setw(42) << "Clerk: " << right << setw(10) << vanilla << endl << endl << endl; //Displays a fixed clerk name //(Optional) Displays a fixed clerk name << vanilla
  cout << left << setw(26) << item << right << setw(26) << price << endl; //Displays the item + price
  cout << left << setw(26) << "Sales Tax" << right << setw(26) << salestax << endl; //Displays the sales tax
  cout << left << setw(26) << "Total" << right << setw(26) << finalprice << endl << endl; //Displays the total + sales tax
  cout << "----------------------------------------------------" << endl; //(52)
  cout << "| Thank you for shopping at Innotech Performance!! |" << endl;
  cout << "----------------------------------------------------" << endl << endl; // :^)



return 0;
}
