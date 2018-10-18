/*flatRatePackage.h
Contains constructors, mutators, and accessors for the flatrate class. Inherits the Package parent class to use with flatrate packages.
*/
#pragma once
#include "package.h"
#include <string>

using std::string;

class FlatRatePackage:public Package
{
private:
	string type; //Package Type ("letter", "paddedEnvelope", "legalEnvelope", "box")
	double width, length, height; //Type dimensions
public:
	//Constructors
	FlatRatePackage();
	FlatRatePackage(string &, string &, string &, const string &, const long &,
					string &, string &, string &, const string &, const long &,
					const string &, const string &, const double &, const double &, const string &, const string &, const string &, const double &, const double &, const double &);
	//Mutators
	//Accessors
	double calculateCost(const string &, const double &, const double &, const double &) const;
	string getType() const;
	double getLength() const;
	double getHeight() const;
	double getWidth() const;
};