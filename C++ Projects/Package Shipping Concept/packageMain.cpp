/*packageMain.cpp
Main file. Calls the function that will process the entirety of an external shipping file.
*/
#include "package.h"
#include "overnightPackage.h"
#include "packageInventory.h"

int main()
{
	PackageInventory inventory;
	inventory.ProcessShippingFile("ShippingList.txt");

	return 0;
}
