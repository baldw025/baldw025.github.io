/*flatRatePackage.cpp*/

#include "flatRatePackage.h"
#include "package.h"
#include <iostream>

using std::cout;
using std::endl;

FlatRatePackage::FlatRatePackage()
{
	type = "Unknown Package Type";
	width, length, height = -1;
}

FlatRatePackage::FlatRatePackage(string &sName, string &sAddress, string &sCity, const string &sState, const long &sZipCode,
								 string &rName, string &rAddress, string &rCity, const string &rState, const long &rZipCode,
								 const string &pLabel, const string &pDate, const double &pWeight, const double &pCost, const string &pInsurance, const string &pSignature, const string &t, const double &l, const double &w, const double &h)
							     :Package(sName, sAddress, sCity, sState, sZipCode, rName, rAddress, rCity, rState, rZipCode, pLabel, pDate, pWeight, pCost, pInsurance, pSignature)
{
	if (t == "letter" || t == "paddedEnvelope" || t == "legalEnvelope" || t == "box")
	{
		type = t;
		length = l;
		width = w;
		height = h;
	}
}

double FlatRatePackage::calculateCost(const string &t, const double &l, const double &w, const double &h) const
{
	double cost = 0.0;

	if (t == "box")
	{
		if (l < 12 || w < 12 || h < 5) //Large
		{
			cost = 20.10;
		}
		if (l < 8 || w < 11 || h < 5) //Medium
		{
			cost = 17.75;
		}
		if (l < 5 || w < 8 || h < 2) //Small
		{
			cost = 11.30;
		}
	}
	if (t == "paddedEnvelope")
	{
		cost = 9.45;
	}
	if (t == "legalEnvelope")
	{
		cost = 7.65;
	}
	if (t == "letter")
	{
		cost = 3.20;
	}

	if (getInsuranceType() == "upto1000" && getSignatureConfirmation() == "sign")
	{
		return cost + 5.25 + 2.90;
	}
	if (getInsuranceType() == "upto1000" && getSignatureConfirmation() == "none")
	{
		return cost + 5.25;
	}
	if (getInsuranceType() == "upto5000" && getSignatureConfirmation() == "sign")
	{
		return cost + 5.50 + 2.90;
	}
	if (getInsuranceType() == "upto5000" && getSignatureConfirmation() == "none")
	{
		return cost + 5.50;
	}

	return cost;
}

string FlatRatePackage::getType() const
{
	return type;
}

double FlatRatePackage::getLength() const
{
	return length;
}

double FlatRatePackage::getHeight() const
{
	return height;
}

double FlatRatePackage::getWidth() const
{
	return width;
}
