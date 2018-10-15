/*packageInventory.cpp
Essential file. Processes commands and information from an external file ("ShippingList.txt") and contains all mutation function definitions for package vectors.
*/
#include "packageInventory.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

using std::cout;
using std::left;
using std::right;
using std::setw;
using std::setprecision;
using std::fixed;
using std::showpoint;
using std::noshowpoint;
using std::endl;
using std::resetiosflags;
using std::ios;
using std::string;
using std::ifstream;

//Default Constructor
PackageInventory::PackageInventory()
{
}

//Adds a spacey boi before each uppercase character in a string (Excluding first character in string). Helps separate fist and last names and other information from external file.
void addSpaceyBois(string &thread)
{
	for (int i = 1; i < thread.length(); i++)
	{
		if (thread[i] >= 'A' && thread[i] <= 'Z')
		{
			thread = thread.insert(i, 1, ' ');
			i++;
		}
	}
}

//Verifies and pushes back standard package information into the appropriate vector
void PackageInventory::CreateNewPackage(string &sName, string &sAddress, string &sCity, const string &sState, const long &sZipCode,
										string &rName, string &rAddress, string &rCity, const string &rState, const long &rZipCode,
										const string &pLabel, const string &pDate, const double &pWeight, const double &pCost, const string &pInsurance, const string &pSignature)
{
	addSpaceyBois(sName); addSpaceyBois(sAddress); addSpaceyBois(sCity);
	addSpaceyBois(rName); addSpaceyBois(rAddress); addSpaceyBois(rCity);

	Package package(sName, sAddress, sCity, sState, sZipCode,
				    rName, rAddress, rCity, rState, rZipCode,
					pLabel, pDate, pWeight, pCost, pInsurance, pSignature);

	if (pWeight > 0)
	{
		packages.push_back(package);
		cout << "Standard Package shipping info successfully stored.\n";
	}
	else
	{
		cout << "Error: Can not store standard package information. (Invalid package weight)\n";
	}
}

//Verifies and pushes back overnight package information into the appropriate vector
void PackageInventory::CreateNewOvernight(string &sName, string &sAddress, string &sCity, const string &sState, const long &sZipCode,
										  string &rName, string &rAddress, string &rCity, const string &rState, const long &rZipCode,
										  const string &pLabel, const string &pDate, const double &pWeight, const double &pCost, const string &pInsurance, const string &pSignature, const string &track, const double &fee)
{
	addSpaceyBois(sName); addSpaceyBois(sAddress); addSpaceyBois(sCity);
	addSpaceyBois(rName); addSpaceyBois(rAddress); addSpaceyBois(rCity);
	
	OvernightPackage overnight(sName, sAddress, sCity, sState, sZipCode,
							   rName, rAddress, rCity, rState, rZipCode,
							   pLabel, pDate, pWeight, pCost, pInsurance, pSignature, track, fee);

	if (pWeight > 0)
	{
		overnightPackages.push_back(overnight);
		cout << "Overnight Package shipping info successfully stored.\n";
	}
	else
	{
		cout << "Error: Can not store overnight package information. (Invalid package weight)\n";
	}

}

//Verifies and pushes back flat rate package information into the appropriate vector
void PackageInventory::CreateNewFlatRate(string &sName, string &sAddress, string &sCity, const string &sState, const long &sZipCode,
										 string &rName, string &rAddress, string &rCity, const string &rState, const long &rZipCode,
										 const string &pLabel, const string &pDate, const double &pWeight, const double &pCost, const string &pInsurance, const string &pSignature, const string &t, const double &len, const double &wid, const double &hei)
{
	addSpaceyBois(sName); addSpaceyBois(sAddress); addSpaceyBois(sCity);
	addSpaceyBois(rName); addSpaceyBois(rAddress); addSpaceyBois(rCity);

	FlatRatePackage flatrate(sName, sAddress, sCity, sState, sZipCode,
							 rName, rAddress, rCity, rState, rZipCode,
						     pLabel, pDate, pWeight, pCost, pInsurance, pSignature, t, len, wid, hei);

	if (t == "letter" || t == "paddedEnvelope" || t == "legalEnvelope" || t == "box")
	{
		flatRatePackages.push_back(flatrate);
		cout << "Flat Rate Package shipping info successfully stored.\n";
	}
	else
	{
		cout << "Error: Can not store flat rate package information. (Invalid or unknown package type)\n";
	}
}

//Prints out all stored standard package information
void PackageInventory::PrintAllPackages() const
{
	cout << "-----------------------------------------\n"
		<< "|Standard Packages Prepared for Shipping|\n"
		<< "|Total Packages: " << left << setw(3) << packages.size() << right << setw(21) << "|" << endl;
	for (int i = 0; i < packages.size(); i++)
	{
		cout << "-----------------------------------------\n"
			 << "Standard Package #" << i + 1 << endl
			 << "-----------------------------------------\n"
			 << left << setw(12) << "Sender: " << packages[i].getSenderName() << endl
			 << left << setw(12) << " " << packages[i].getSenderAddress() << endl
			 << left << setw(12) << " " << packages[i].getSenderCity() << ", " << packages[i].getSenderState() << " " << packages[i].getSenderZipCode() << endl
			 << left << setw(12) << "Recipient: " << packages[i].getRecipName() << endl
			 << left << setw(12) << " " << packages[i].getRecipAddress() << endl
			 << left << setw(12) << " " << packages[i].getRecipCity() << ", " << packages[i].getRecipState() << " " << packages[i].getRecipZipCode() << endl
			 << left << setw(12) << "Label: " << packages[i].getLabel() << endl
			 << left << setw(12) << "Mailed on: " << packages[i].getDate() << endl
			 << left << setw(12) << "Weight: " << packages[i].getWeight() << endl
			 << left << setw(12) << "Insurance: " << packages[i].getInsuranceType() << endl
			 << left << setw(12) << "Signature: " << packages[i].getSignatureConfirmation() << endl
			 << left << setw(12) << "Cost: " << fixed << showpoint << setprecision(2) << "$" << packages[i].calculateCost() << endl
			 << "-----------------------------------------\n";
	}
}

//Prints out all stored overnight package information
void PackageInventory::PrintAllOvernightPackages() const
{
	cout << "------------------------------------------\n"
		<< "|Overnight Packages Prepared for Shipping|\n"
		<< "|Total Packages: " << left << setw(3) << overnightPackages.size() << right << setw(22) << "|" << endl;
	for (int i = 0; i < overnightPackages.size(); i++)
	{
		cout << "------------------------------------------\n"
			 << "Overnight Package #" << i + 1 << endl
			 << "------------------------------------------\n"
			 << left << setw(12) << "Sender: " << overnightPackages[i].getSenderName() << endl
			 << left << setw(12) << " " << overnightPackages[i].getSenderAddress() << endl
			 << left << setw(12) << " " << overnightPackages[i].getSenderCity() << ", " << overnightPackages[i].getSenderState() << " " << overnightPackages[i].getSenderZipCode() << endl
			 << left << setw(12) << "Recipient: " << overnightPackages[i].getRecipName() << endl
			 << left << setw(12) << " " << overnightPackages[i].getRecipAddress() << endl
			 << left << setw(12) << " " << overnightPackages[i].getRecipCity() << ", " << overnightPackages[i].getRecipState() << " " << overnightPackages[i].getRecipZipCode() << endl
			 << left << setw(12) << "Label: " << overnightPackages[i].getLabel() << endl
			 << left << setw(12) << "Mailed on: " << overnightPackages[i].getDate() << endl
			 << left << setw(12) << "Weight: " << overnightPackages[i].getWeight() << endl
			 << left << setw(12) << "Insurance: " << overnightPackages[i].getInsuranceType() << endl
			 << left << setw(12) << "Signature: " << overnightPackages[i].getSignatureConfirmation() << endl
			 << left << setw(12) << "Tracking: " << overnightPackages[i].getTracking() << endl
			 << left << setw(12) << "Cost: " << fixed << showpoint << setprecision(2) << "$" << overnightPackages[i].calculateCost() << endl
			 << "------------------------------------------\n";
	}
}

//Print out all flat rate package information
void PackageInventory::PrintAllFlatRatePackages() const
{
	cout << "------------------------------------------\n"
		<< "|Flat Rate Packages Prepared for Shipping|\n"
		<< "|Total Packages: " << left << setw(3) << flatRatePackages.size() << right << setw(22) << "|" << endl;
	for (int i = 0; i < flatRatePackages.size(); i++)
	{
		cout << "------------------------------------------\n"
			 << "Flat Rate Package #" << i + 1 << endl
			 << "------------------------------------------\n"
			 << left << setw(12) << "Sender: " << flatRatePackages[i].getSenderName() << endl
			 << left << setw(12) << " " << flatRatePackages[i].getSenderAddress() << endl
			 << left << setw(12) << " " << flatRatePackages[i].getSenderCity() << ", " << flatRatePackages[i].getSenderState() << " " << flatRatePackages[i].getSenderZipCode() << endl
			 << left << setw(12) << "Recipient: " << flatRatePackages[i].getRecipName() << endl
			 << left << setw(12) << " " << flatRatePackages[i].getRecipAddress() << endl
			 << left << setw(12) << " " << flatRatePackages[i].getRecipCity() << ", " << flatRatePackages[i].getRecipState() << " " << flatRatePackages[i].getRecipZipCode() << endl
			 << left << setw(12) << "Label: " << flatRatePackages[i].getLabel() << endl
			 << left << setw(12) << "Mailed on: " << flatRatePackages[i].getDate() << endl
			 << left << setw(12) << "Weight: " << flatRatePackages[i].getWeight() << endl
			 << left << setw(12) << "Type: " << flatRatePackages[i].getType() << endl
			 << left << setw(12) << "Dimensions: " << noshowpoint << resetiosflags(ios::fixed) << flatRatePackages[i].getLength() << "x" << flatRatePackages[i].getWidth() << "x" << flatRatePackages[i].getHeight() << endl
			 << left << setw(12) << "Insurance: " << flatRatePackages[i].getInsuranceType() << endl
			 << left << setw(12) << "Signature: " << flatRatePackages[i].getSignatureConfirmation() << endl
			 << left << setw(12) << "Cost: " << fixed << showpoint << setprecision(2) << "$" << flatRatePackages[i].calculateCost() << endl
			 << "------------------------------------------\n";
	}
}

//Finds and prints all packages (standard, overnight, and flat rate) that were shipped in a specific month in a specific year
void PackageInventory::PrintShippedOnMonthYear(string m, string y) const
{
	string date;
	bool found = false;

	if (m.length() == 1) //Inserts a zero in front of single-digit months since they can be present in our command file. It makes our lives easier. (9/2018 - > 09/2018)
	{
		m = m.insert(0, "0");
	}

	for (int i = 0; i < packages.size(); i++) //Check if any standard packages were shipped on the passed date. Print if true.
	{
		date = packages[i].getDate();
		if (m == date.substr(0, date.find("/", 0)) && y == date.substr(6, date.find('\n', 5)))
		{
		   found = true;
		   cout << "-----------------------------------------\n"
				<< "|Standard Package Shipped in " << setw(2) << m << "/" << setw(4) << y << setw(5) << "|"
			    << "\n-----------------------------------------\n"
				<< "Standard Package #" << i + 1 << endl
				<< "-----------------------------------------\n"
				<< left << setw(12) << "Sender: " << packages[i].getSenderName() << endl
				<< left << setw(12) << " " << packages[i].getSenderAddress() << endl
				<< left << setw(12) << " " << packages[i].getSenderCity() << ", " << packages[i].getSenderState() << " " << packages[i].getSenderZipCode() << endl
				<< left << setw(12) << "Recipient: " << packages[i].getRecipName() << endl
				<< left << setw(12) << " " << packages[i].getRecipAddress() << endl
				<< left << setw(12) << " " << packages[i].getRecipCity() << ", " << packages[i].getRecipState() << " " << packages[i].getRecipZipCode() << endl
				<< left << setw(12) << "Label: " << packages[i].getLabel() << endl
				<< left << setw(12) << "Mailed on: " << packages[i].getDate() << endl
				<< left << setw(12) << "Weight: " << packages[i].getWeight() << endl
				<< left << setw(12) << "Insurance: " << packages[i].getInsuranceType() << endl
				<< left << setw(12) << "Signature: " << packages[i].getSignatureConfirmation() << endl
				<< left << setw(12) << "Cost: " << fixed << showpoint << setprecision(2) << "$" << packages[i].calculateCost() << endl
				<< "-----------------------------------------\n";
		}
	}
	for (int i = 0; i < overnightPackages.size(); i++) //Check if any overnight packages were shipped on the passed date. Print if true.
	{
		date = overnightPackages[i].getDate();
		if (m == date.substr(0, date.find("/", 0)) && y == date.substr(6, date.find('\n', 5)))
		{
			found = true;
			cout << "-----------------------------------------\n"
				<< "|Overnight Package Shipped in " << right << setw(2) << m << "/" << setw(4) << y << setw(4) << "|"
				<< "\n-----------------------------------------\n"
				<< "Overnight Package #" << i + 1 << endl
				<< "-----------------------------------------\n"
				<< left << setw(12) << "Sender: " << overnightPackages[i].getSenderName() << endl
				<< left << setw(12) << " " << overnightPackages[i].getSenderAddress() << endl
				<< left << setw(12) << " " << overnightPackages[i].getSenderCity() << ", " << overnightPackages[i].getSenderState() << " " << overnightPackages[i].getSenderZipCode() << endl
				<< left << setw(12) << "Recipient: " << overnightPackages[i].getRecipName() << endl
				<< left << setw(12) << " " << overnightPackages[i].getRecipAddress() << endl
				<< left << setw(12) << " " << overnightPackages[i].getRecipCity() << ", " << overnightPackages[i].getRecipState() << " " << overnightPackages[i].getRecipZipCode() << endl
				<< left << setw(12) << "Label: " << overnightPackages[i].getLabel() << endl
				<< left << setw(12) << "Mailed on: " << overnightPackages[i].getDate() << endl
				<< left << setw(12) << "Weight: " << overnightPackages[i].getWeight() << endl
				<< left << setw(12) << "Insurance: " << overnightPackages[i].getInsuranceType() << endl
				<< left << setw(12) << "Signature: " << overnightPackages[i].getSignatureConfirmation() << endl
				<< left << setw(12) << "Tracking: " << overnightPackages[i].getTracking() << endl
				<< left << setw(12) << "Cost: " << fixed << showpoint << setprecision(2) << "$" << overnightPackages[i].calculateCost() << endl
				<< "-----------------------------------------\n";
		}
	}
	for (int i = 0; i < flatRatePackages.size(); i++) //Check if any flat rate packages were shipped on the passed date. Print if true.
	{
		date = flatRatePackages[i].getDate();
		if (m == date.substr(0, date.find("/", 0)) && y == date.substr(6, date.find('\n', 5)))
		{
			found = true;
			cout << "-----------------------------------------\n"
				<< "|Flat Rate Package Shipped in " << right << setw(2) << m << "/" << setw(4) << y << setw(4) << "|"
				<< "\n-----------------------------------------\n"
				<< "Flat Rate Package #" << i + 1 << endl
				<< "-----------------------------------------\n"
				<< left << setw(12) << "Sender: " << flatRatePackages[i].getSenderName() << endl
				<< left << setw(12) << " " << flatRatePackages[i].getSenderAddress() << endl
				<< left << setw(12) << " " << flatRatePackages[i].getSenderCity() << ", " << flatRatePackages[i].getSenderState() << " " << flatRatePackages[i].getSenderZipCode() << endl
				<< left << setw(12) << "Recipient: " << flatRatePackages[i].getRecipName() << endl
				<< left << setw(12) << " " << flatRatePackages[i].getRecipAddress() << endl
				<< left << setw(12) << " " << flatRatePackages[i].getRecipCity() << ", " << flatRatePackages[i].getRecipState() << " " << flatRatePackages[i].getRecipZipCode() << endl
				<< left << setw(12) << "Label: " << flatRatePackages[i].getLabel() << endl
				<< left << setw(12) << "Mailed on: " << flatRatePackages[i].getDate() << endl
				<< left << setw(12) << "Weight: " << flatRatePackages[i].getWeight() << endl
				<< left << setw(12) << "Type: " << flatRatePackages[i].getType() << endl
				<< left << setw(12) << "Dimensions: " << noshowpoint << resetiosflags(ios::fixed) << flatRatePackages[i].getLength() << "x" << flatRatePackages[i].getWidth() << "x" << flatRatePackages[i].getHeight() << endl
				<< left << setw(12) << "Insurance: " << flatRatePackages[i].getInsuranceType() << endl
				<< left << setw(12) << "Signature: " << flatRatePackages[i].getSignatureConfirmation() << endl
				<< left << setw(12) << "Cost: " << fixed << showpoint << setprecision(2) << "$" << flatRatePackages[i].calculateCost() << endl
				<< "-----------------------------------------\n";
		}
	}
	if (!found)
	{
		cout << "-----------------------------------------\n"
			<< "|No Packages were Shipped in " << right << setw(2) << m << "/" << setw(4) << y << "." << setw(4) << "|"
			<< "\n-----------------------------------------\n";
	}
}

//Calculates and prints the total cost of a specific stored package type (standard, overnight, flat rate)
void PackageInventory::calculateTotalCost(const string & pT) const
{
	double totalCost = 0.0;

	if (pT == "packages")
	{
		for (int i = 0; i < packages.size(); i++)
		{
			totalCost += packages[i].calculateCost();
		}
		cout << "The total cost of all " << packages.size() << " shipped standard packages is: $" << totalCost << endl;
	}
	if (pT == "overnightPackages")
	{
		for (int i = 0; i < overnightPackages.size(); i++)
		{
			totalCost += overnightPackages[i].calculateCost();
		}
		cout << "The total cost of all " << overnightPackages.size() << " shipped overnight packages is: $" << totalCost << endl;
	}
	if (pT == "flatRatePackages")
	{
		for (int i = 0; i < flatRatePackages.size(); i++)
		{
			totalCost += flatRatePackages[i].calculateCost();
		}
		cout << "The total cost of all " << flatRatePackages.size() << " shipped flat rate packages is: $" << totalCost << endl;
	}
}

//Primary function that processes commands from an external file and calls the respective commands to execute.
void PackageInventory::ProcessShippingFile(const string &fileName)
{
	ifstream fin;
	string command;
	string month, day;
	string packageType;
	string senderName, senderAddress, senderCity, senderState; //Sender Information
	long senderZIPcode; //Sender Information
	string recipName, recipAddress, recipCity, recipState; //Recipient Information
	long recipZIPcode; //Recipient Information
	string label, date, insuranceType, signatureConfirmation, tracking, type; //Package Information
	double weight, costPerOunce, overnightFee, width, length, height; //Package Information

	fin.open(fileName);
	if (!fin)
	{
		cout << "The shipping file \"" << fileName << "\" can not be opened or does not exist.\n";
	}
	else
	{
		cout << "Successfully opened shipping file: \"" << fileName << "\"\n";
		fin >> command;
		while (fin)
		{
			if (command == "CreateNewPackage")
			{
				fin >> senderName >> senderAddress >> senderCity >> senderState >> senderZIPcode
					>> recipName >> recipAddress >> recipCity >> recipState >> recipZIPcode
					>> label >> date >> weight >> costPerOunce >> insuranceType >> signatureConfirmation;

				CreateNewPackage(senderName, senderAddress, senderCity, senderState, senderZIPcode,
								 recipName, recipAddress, recipCity, recipState, recipZIPcode,
								 label, date, weight, costPerOunce, insuranceType, signatureConfirmation);
			}
			if (command == "CreateNewOvernight")
			{
				fin >> senderName >> senderAddress >> senderCity >> senderState >> senderZIPcode
					>> recipName >> recipAddress >> recipCity >> recipState >> recipZIPcode
					>> label >> date >> weight >> costPerOunce >> insuranceType >> signatureConfirmation
					>> tracking >> overnightFee;

				CreateNewOvernight(senderName, senderAddress, senderCity, senderState, senderZIPcode,
					recipName, recipAddress, recipCity, recipState, recipZIPcode,
					label, date, weight, costPerOunce, insuranceType, signatureConfirmation, tracking, overnightFee);
			}
			if (command == "CreateNewFlatRate")
			{
				fin >> senderName >> senderAddress >> senderCity >> senderState >> senderZIPcode
					>> recipName >> recipAddress >> recipCity >> recipState >> recipZIPcode
					>> label >> date >> weight >> costPerOunce >> insuranceType >> signatureConfirmation
					>> type >> length >> width >> height;

				CreateNewFlatRate(senderName, senderAddress, senderCity, senderState, senderZIPcode,
								  recipName, recipAddress, recipCity, recipState, recipZIPcode,
								  label, date, weight, costPerOunce, insuranceType, signatureConfirmation, type, length, width, height);
			}
			if (command == "PrintAllPackages")
			{
				PrintAllPackages();
			}
			if (command == "PrintAllOvernightPackages")
			{
				PrintAllOvernightPackages();
			}
			if (command == "PrintAllFlatRatePackages")
			{
				PrintAllFlatRatePackages();
			}
			if (command == "PrintShippedonMonthYear")
			{
				fin >> month >> day;
				PrintShippedOnMonthYear(month, day);
			}
			if (command == "CalculateTotalCost")
			{
				fin >> packageType;
				calculateTotalCost(packageType);
			}
			fin >> command;
		}
	}
	fin.close();
}