/***********************************************************
This program will ask for today's date, a company name, and a user-defined quantity of a product they wish to purchase. If the user enters a negative number for quantity, it will be invalid, if a 0(zero) is entered, the program will cout "Hope you decide to buy our software in the future." An invoice of the transaction will be displayed if the user's input != 0.
***********************************************************/

#include <iomanip> //Header used to manipulate the input/output stream
#include <iostream> //Header used to include an input/output stream for user-input
using namespace std; //Sets the namespace as standard

int main()
{
  /////////////////////////////////////////////////////////////////////////
  const int ITEM_PRICE = 99; //Stores the scenario's fixed price of "$99".
  string date; //Stores a user-input date as a string
  string company_name; //Stores a user-input company name
  int quantity; //Stores the purchase quantity of "x" item
  float price; //Stores the overall price before discounts
  float total_discount; //Stores the total discount in respect to price
  float raw_discount; //Stores the flat, vanilla discount amounts (20%, 40%, etc.) For reasons.
  float price_final; //Stores the final price (inc. quantity + discount)
  float percent; //Stores the discount percent for future abuse as a variable, for efficiency. Also used for my switch
  int switchy; //Used for my switch, k?
  /////////////////////////////////////////////////////////////////////////


  //This section contains the iostream scenario and stores the user's inputs
  cout << "Enter today's date (mm/dd/yy): ";
  cin >> date;
  cout << endl;

  cin.ignore(10,'\n');  
  cout << "Enter your company name: ";
  getline(cin,company_name);
  cout << endl;

  cout << "Enter the quantity you would like to purchase: ";
  cin >> quantity;
  cout << endl;

  //This section converts and calculates the discount percentage in respect to quantity
  if (quantity >= 10 && quantity <= 19) //If the user's purchase quantity is [10,19], stores the appropriate values into percent and switchy(case) variables    
    {
      switchy = percent = 20;
    }
  else if (quantity >= 20 && quantity <= 49) //If the user's purchase quantity is [20-49], stores the appropriate values into percent and switchy(case) variables
    {
      switchy = percent = 30;
    }
  else if (quantity >= 50 && quantity <= 99) //If the user's purchase quantity is [50-99], stores the appropriate values into percent and switchy(case) variables
    {
      switchy = percent = 40;
    }
  else if (quantity >= 100) //If the user's purchase quantity is [100, ∞), stores the appropriate values into percent and switchy(case) variables
    {
      switchy = percent = 50;
    }
  else if (quantity == 0) //If the user's purchase quantity = 0, stores the appropriate value to switchy(case) variable
    {
      switchy = 0;
    }
  else if (quantity > 0 && quantity < 10) //If the user's non-zero purchase quantity does not rate a discount (0,9], stores the appropriate values into percent and switchy(case) variables
    {
      percent = 0;
      switchy = 10;
    }

  std::cout << std::setprecision(2) << std::fixed; //Sets the following outputs to a fixed decimal precision of "2"

  //Switch used for personal preference and for a more "clean" source appearance. That way everything isn't garbled under the above if, else if statements
  switch(switchy)
    {
      //If the user's purchase quantity is non-zero, an invoice will be calculated and generated.
      case 10:
      case 20:
      case 30:
      case 40:
      case 50:
	price = ITEM_PRICE * quantity;
	raw_discount = percent / (float)100;
	total_discount = raw_discount * price;
	price_final = price - total_discount;
	
	cout << "Invoice for " << company_name << endl << endl; 
	cout << left << setw(30) << "Price before discount" << "$" << right << setw(10) << price << endl;
	cout << left << setw(30) << "Discount" << "$" << right << setw(10) << total_discount << endl;
	cout << left << setw(30) << "Total Due" << "$" << right << setw(10) << price_final << endl << endl;
	break;
	  
      //If the user purchases zero items
      case 0: cout << "Hope you decide to buy our software in the future." << endl;
        break;

      //All above cases fail if the user enters any quantity that is less than 0, a la invalid
      default: cout << "Invalid quantity." << endl;
    }

/*

    ( ͡° ͜ʖ ͡°)
  
*/

  return 0;
}
