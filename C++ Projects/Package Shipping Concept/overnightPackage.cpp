/*overnightPackage.cpp*/
#include "overnightPackage.h"
#include <iostream>

using std::cout;

OvernightPackage::OvernightPackage()
{
	overnightFee = 0;
	tracking = "none";
}

OvernightPackage::OvernightPackage(string &sName, string &sAddress, string &sCity, const string &sState, const long &sZipCode,
								   string &rName, string &rAddress, string &rCity, const string &rState, const long &rZipCode,
								   const string &pLabel, const string &pDate, const double &pWeight, const double &pCost, const string &pInsurance, const string &pSignature, const string &track, const double &fee)
								   :Package(sName, sAddress, sCity, sState, sZipCode, rName, rAddress, rCity, rState, rZipCode, pLabel, pDate, pWeight, pCost, pInsurance, pSignature)
{
	if (fee < 0)
	{
		cout << "Fee is invalid.";
		overnightFee = 0;
	}
	else
	{
		overnightFee = fee;
	}
	tracking = track;
}

OvernightPackage::OvernightPackage(string &sName, string &sAddress, string &sCity, const string &sState, const long &sZipCode,
								   string &rName, string &rAddress, string &rCity, const string &rState, const long &rZipCode,
								   const string &pLabel, const string &pDate, const double &pWeight, const double &pCost, const string &pInsurance, const double &fee)
								   :Package(sName, sAddress, sCity, sState, sZipCode, rName, rAddress, rCity, rState, rZipCode, pLabel, pDate, pWeight, pCost, pInsurance)
{
	overnightFee = fee;
}

string OvernightPackage::getTracking() const
{
	return tracking;
}

double OvernightPackage::getFees() const
{
	return overnightFee;
}

double OvernightPackage::calculateCost() const
{
	double cost = (getCostPerOunce() * getWeight()) + getFees();

	if (getInsuranceType() == "upto1000" && getSignatureConfirmation() == "sign")
	{
		if (tracking == "track")
		{
			return cost += 5.25 + 2.90 + 5.50;
		}
		else
		{
			return cost += 5.25 + 2.90;
		}
	}
	else if (getInsuranceType() == "upto1000" && getSignatureConfirmation() == "none")
	{
		if (tracking == "track")
		{
			return cost += 5.25 + 5.50;
		}
		else
		{
			return cost += 5.25;
		}
	}
	if (getInsuranceType() == "upto5000" && getSignatureConfirmation() == "sign")
	{
		if (tracking == "track")
		{
			return cost += 5.50 + 2.90 + 5.50;
		}
		else
		{
			return cost += 5.50 + 2.90;
		}
	}
	else if (getInsuranceType() == "upto5000" && getSignatureConfirmation() == "none")
	{
		if (tracking == "track")
		{
			return cost += 5.50 + 5.50;
		}
		else
		{
			return cost += 5.50;
		}
	}
	if (getInsuranceType() == "none" && getSignatureConfirmation() == "sign")
	{
		if (tracking == "track")
		{
			return cost += 2.90 + 5.50;
		}
		else
		{
			return cost += 2.90;
		}
	}
	else if (getInsuranceType() == "none" && getSignatureConfirmation() == "none")
	{
		if (tracking == "track")
		{
			return cost += 5.50;
		}
		else
		{
			return cost;
		}
	}
	return cost;
}