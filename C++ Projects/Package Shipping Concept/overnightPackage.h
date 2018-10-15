/*overnightPackage.h
Contains constructors, mutators, and accessors for the overnight package class. Inherits the Package parent class to use with overnight packages.
*/
#pragma once
#include "package.h"

class OvernightPackage:public Package
{
private:
	double overnightFee;
	string tracking; //"None", "Track"
public:
	//Constructors
	OvernightPackage();
	OvernightPackage(string &, string &, string &, const string &, const long &,
					 string &, string &, string &, const string &, const long &,
					 const string &, const string &, const double &, const double &, const string &, const string &, const string &, const double &);
	OvernightPackage(string &, string &, string &, const string &, const long &,
					 string &, string &, string &, const string &, const long &,
					 const string &, const string &, const double &, const double &, const string &, const double &);
	//Mutators
	//Accessors
	string getTracking() const;
	double getFees() const;
	double calculateCost() const;
};
