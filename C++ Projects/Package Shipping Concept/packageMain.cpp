/*packageMain.cpp
Main file. Calls the function that will process the entirety of an external shipping file.
*/
#include "package.h"
#include "overnightPackage.h"
#include "packageInventory.h"

int main()
{
	//Parameterized Constructor Test
	//Package package1("AmyJohnson", "3465RegentsRd.", "SanDiego", "CA", 92130,
	//				 "EdwardJohnes", "439NWGreens", "Fayetteville", "NY", 13066,
	//				 "HG9983", "06/03/2016", 10, 0.7, "upto1000", "none");
	//OvernightPackage package2("MaryPalmer", "6534SpringburstDr", "PalmSprings", "CA", 92240,
	//				 "DennisGarcia", "8FifthSt", "Denver", "CO", 66665,
	//				 "UI0900", "10/11/2016", 20.1, 0.8, "upto5000", 7);
	//package1.calculateCost();
	//package1.printPackage();

	PackageInventory inventory;
	inventory.ProcessShippingFile("ShippingList.txt");

	return 0;
}
