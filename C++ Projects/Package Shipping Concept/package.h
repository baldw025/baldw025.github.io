/*package.h
Contains constructors, mutators, and accessors for the Package class. Parent class for overnight and flat rate packages.
*/
#pragma once
#include <string>

using std::string;

class Package
{
private:
	//Sender Information
	string senderName, senderAddress, senderCity, senderState;
	long senderZipCode;
	//Recipient Information
	string recipName, recipAddress, recipCity, recipState;
	long recipZipCode;
	//Package Information
	string label, date, insuranceType, signatureConfirmation;
	double weight, costPerOunce;
public:
	//Constructors
	Package();
	Package(string, string, string, string, long,
		    string, string, string, string, long,
		    string, string, double, double, string, string);
	Package(string, string, string, string, long,
			string, string, string, string, long,
			string, string, double, double, string);
	//Mutators
	//Accessors
	void printPackage() const;
	double calculateCost() const;
	string getSenderName() const;
	string getSenderAddress() const;
	string getSenderCity() const;
	string getSenderState() const;
	long getSenderZipCode() const;
	string getRecipName() const;
	string getRecipAddress() const;
	string getRecipCity() const;
	string getRecipState() const;
	long getRecipZipCode() const;
	string getLabel() const;
	string getDate() const;
	string getInsuranceType() const;
	string getSignatureConfirmation() const;
	double getWeight() const;
	double getCostPerOunce() const;
};