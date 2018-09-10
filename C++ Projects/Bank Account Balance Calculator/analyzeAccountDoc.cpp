/*This program will analyze a file consisting of financial account information stored in our bank. 
It will then calculate and create a new file containing each account's overall balance, manipulated by variable interest rates, after any logged withdrawals*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <string>

//Create a constant double array with our interest rates for easy adjustment, if needed in the future. Premium - Choice - Basic
const double INTEREST_RATES[3] = { 0.05, 0.03, 0.01 };
std::ifstream fin; //Declare our file input stream as a global so other functions can easily access it
std::ofstream fout ("accountInfoOutput.dat"); //Declare our file output stream as a global so other functions can easily access it. Create a file to output to. Also made global for easy future modification

//Function protype for analyzing our file
void analyzeFile();


//A clean main is a happy main :^)
int main()
{
	//Open the document containing all of our bank's account info
	fin.open("accounts.txt");

	//If the file does not exist, state so in the buffer then exit with code 1
	if (!fin)
	{
		std::cout << "The file does not exist\n";
		exit(1);
	}

	//If the file does exist, call the analyzeFile function
	else
	analyzeFile();

	return 0;
}

/*This function will read, analyze, and store data from a file containing numerous bank records. 
It will then identify all account numbers' final balance after factoring in initial balances, deposits, withdrawals, and interest rates*/
void analyzeFile()
{
	std::string accountNumber, accountType;
	double startBalance, accountDeposit, accountWithdrawal, endBalance, interestRate;

	//Generate the header of our account info report
	fout << "Account" << std::setw(8) << "Type" << std::setw(16) << "StartBalance" << std::setw(16) << "Deposit" << std::setw(16) << "Withdrawal" << std::setw(16) << "EndBalance\n"
							   << "------------------------------------------------------------------------------\n";

	//Read into the document and locally save all the information of the first account
	fin >> accountNumber >> accountType >> startBalance >> accountDeposit >> accountWithdrawal;

	//Keep reading into the file while there is no more content to read
	while(fin)
	{
	//Since we can't use switch with strings, we will check the current read account type and locally apply the correct interest amount in respect to our global array indices
	if(accountType == "Basic")
	{
		interestRate = INTEREST_RATES[2];
	}
	if(accountType == "Choice")
	{
		interestRate = INTEREST_RATES[1];
	}
	if (accountType == "Premium")
	{
		interestRate = INTEREST_RATES[0];
	}

	//Calculates the account's overall final balance by calculating balance generated purely by interest and adding that value to the account's net worth (after withdrawals).
	endBalance = (((startBalance + accountDeposit) - accountWithdrawal) * interestRate) + ((startBalance + accountDeposit) - accountWithdrawal);

	//Cleanly save the current read account's information, including calculated overall balance, into a file.
		
	fout << std::fixed << std::showpoint << std::setprecision(2) << std::setw(10) << std::left << accountNumber << std::setw(8) << std::left << accountType << std::setw(10) << std::right << startBalance << std::setw(19) << std::right <<accountDeposit << std::setw(15) << std::right << accountWithdrawal << std::setw(15) << std::right << endBalance << std::endl;

	//Read the next line in our account info document, if applicable
	fin >> accountNumber >> accountType >> startBalance >> accountDeposit >> accountWithdrawal;
	}

	fin.close(); //Close the file input stream, for sanity.
	fout.close(); //Close the file output stream, for my sake.
}
