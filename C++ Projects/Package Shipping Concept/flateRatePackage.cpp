/*flatRatePackage.cpp
TODO: Satisfy rest of conditional checks in project guidelines (Dimensions, Validity, calculateCost redefiniton)
*/

#include "flateRatePackage.h"
#include "package.h"

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
		width = w;
		length = l;
		height = h;
	}							     
	else //TODO:Remove placeholder, Finish condition checks
	{
		type = "Invalid Package Type";
		width = -1;
		length = -1;
		height = -1;
	}
}

double FlatRatePackage::calculateCost() const //TODO:Remove placeholder, Finish condition checks
{
	return 0.0;
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
