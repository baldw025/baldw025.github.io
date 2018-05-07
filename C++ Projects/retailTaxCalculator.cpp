/***************************
This program will calculate and state  the total of a retail sale, including sales tax
***************************/

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
  double price;
  double taxrate;
  double finalprice;
  double totalsalestax;
  double tax;
 
  std::cout << std::setprecision(2) << std::fixed;

  cout << "What is  the price of your item? ";
  cin >> price;
  cout << "What is the sales tax rate of this item? ";
  cin >> taxrate;
  
  tax = taxrate / 100;
  totalsalestax = price * tax;
  finalprice = price + totalsalestax;

  cout << "The total  sales  tax  of your item is $" <<totalsalestax;
  cout << ", which makes the  final price of your item $" <<finalprice <<endl;

  return 0;
}
