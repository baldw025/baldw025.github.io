/*packageInventory.h
Contains constructors, mutators, and accessors for the package inventory class. Manages vectors of various package types.
*/
#pragma once
#include "package.h"
#include "flateRatePackage.h"
#include "overnightPackage.h"
#include <vector>

using std::vector;

class PackageInventory
{
private:
	vector <Package> packages;
	vector <OvernightPackage> overnightPackages;
	vector <FlatRatePackage> flatRatePackages;
public:
	//Constructors
	PackageInventory();
	//Mutators
	void CreateNewPackage(string &, string &, string &, const string &, const long &,
						  string &, string &, string &, const string &, const long &,
			              const string &, const string &, const double &, const double &, const string &, const string &);

	void CreateNewOvernight(string &, string &, string &, const string &, const long &,
							string &, string &, string &, const string &, const long &,
							const string &, const string &, const double &, const double &, const string &, const string &, const string &, const double &);

	void CreateNewFlatRate(string &, string &, string &, const string &, const long &,
						   string &, string &, string &, const string &, const long &,
						   const string &, const string &, const double &, const double &, const string &, const string &, const string &, const double &, const double &, const double &);
	//Accessors
	void PrintAllPackages() const;
	void PrintAllOvernightPackages() const;
	void PrintAllFlatRatePackages() const;
	void PrintShippedOnMonthYear(string, string) const;
	void calculateTotalCost(const string &) const;
	void ProcessShippingFile(const string &);
};