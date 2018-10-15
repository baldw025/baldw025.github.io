/*package.cpp*/
#include "package.h"
#include <string>
#include <iostream>
#include <iomanip>

using std::string;
using std::cout;
using std::endl;
using std::left;
using std::right;
using std::setw;

Package::Package()
{
	//Sender
	senderName = "Sender Name is Unknown";
	senderAddress = "Sender Address is Unknown";
	senderCity = "Sender City is Unknown";
	senderState = "Sender State is Unknown";
	senderZipCode = 11111111;
	//Recipient
	recipName = "Recipient Name is Unknown";
	recipAddress = "Recipient Address is Unknown";
	recipCity = "Recipient City is Unknown";
	recipState = "Recipient State is Unknown";
	recipZipCode = 11111111;
	//Package
	label = "Package Label is Unknown";
	date = "Package Date is Unknown";
	insuranceType = "Insurance Type is Unknown";
	weight = 0;
	costPerOunce = 0;
	signatureConfirmation = "none";
}
Package::Package(string, string, string, string, long, string, string, string, string, long, string, string, double, double, string)
{
}
Package::Package(string sName, string sAddress, string sCity, string sState, long sZipCode,
				 string rName, string rAddress, string rCity, string rState, long rZipCode,
				 string pLabel, string pDate, double pWeight, double pCost, string pInsurance, string pSignature)
{
	//Sender
	senderName = sName;
	senderAddress = sAddress;
	senderCity = sCity;
	senderState = sState;
	senderZipCode = sZipCode;
	//Recipient
	recipName = rName;
	recipAddress = rAddress;
	recipCity = rCity;
	recipState = rState;
	recipZipCode = rZipCode;
	//Package
	label = pLabel;
	date = pDate;
	if (pWeight < 0)
	{
		cout << "Invalid Weight.";
	}
	else
	{
		weight = pWeight;
	}
	if (pCost < 0)
	{
		cout << "Invalid Fee.";
	}
	else
	{
		costPerOunce = pCost;
	}
	insuranceType = pInsurance;
	signatureConfirmation = pSignature;
}

void Package::printPackage() const
{
	cout << "-----------------------------------------\n"
		<< "Standard Package #" << endl
		<< "-----------------------------------------\n"
		<< left << setw(12) << "Sender: " << getSenderName() << endl
		<< left << setw(12) << " " << getSenderAddress() << endl
		<< left << setw(12) << " " << getSenderCity() << ", " << getSenderState() << " " << getSenderZipCode() << endl
		<< left << setw(12) << "Recipient: " << getRecipName() << endl
		<< left << setw(12) << " " << getRecipAddress() << endl
		<< left << setw(12) << " " << getRecipCity() << ", " << getRecipState() << " " << getRecipZipCode() << endl
		<< left << setw(12) << "Label: " << getLabel() << endl
		<< left << setw(12) << "Mailed on: " << getDate() << endl
		<< left << setw(12) << "Weight: " << getWeight() << endl
		<< left << setw(12) << "Insurance: " << getInsuranceType() << endl
		<< left << setw(12) << "Signature: " << getSignatureConfirmation() << endl
		<< left << setw(12) << "Cost: " << getCostPerOunce() << endl
		<< "-----------------------------------------\n";
}

double Package::calculateCost() const
{
	double cost = getCostPerOunce() * weight;

	if (getInsuranceType() == "upto1000" && getSignatureConfirmation() == "sign")
	{
		return cost += 5.25 + 2.90;
	}
	else if (getInsuranceType() == "upto1000" && getSignatureConfirmation() == "none")
	{
		return cost += 5.25;
	}
	if (getInsuranceType() == "upto5000" && getSignatureConfirmation() == "sign")
	{
		return cost += 5.50 + 2.90;
	}
	else if (getInsuranceType() == "upto5000" && getSignatureConfirmation() == "none")
	{
		return cost += 5.50;
	}
	if (getInsuranceType() == "none" && getSignatureConfirmation() == "sign")
	{
		return cost += 2.90;
	}
	else if (getInsuranceType() == "none" && getSignatureConfirmation() == "none")
	{
		return cost;
	}
	return cost;
}

string Package::getSenderName() const
{
	return senderName;;
}

string Package::getSenderAddress() const
{
	return senderAddress;
}

string Package::getSenderCity() const
{
	return senderCity;
}

string Package::getSenderState() const
{
	return senderState;
}

long Package::getSenderZipCode() const
{
	return senderZipCode;
}

string Package::getRecipName() const
{
	return recipName;
}

string Package::getRecipAddress() const
{
	return recipAddress;
}

string Package::getRecipCity() const
{
	return recipCity;
}

string Package::getRecipState() const
{
	return recipState;
}

long Package::getRecipZipCode() const
{
	return recipZipCode;
}

string Package::getLabel() const
{
	return label;
}

string Package::getDate() const
{
	return date;
}

string Package::getInsuranceType() const
{
	return insuranceType;
}

string Package::getSignatureConfirmation() const
{
	return signatureConfirmation;
}

double Package::getWeight() const
{
	return weight;
}

double Package::getCostPerOunce() const
{
	return costPerOunce;
}
