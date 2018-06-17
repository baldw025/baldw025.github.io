/**********************************
A personal, purely experimental, and just parodical security-ish system I made when barely learning how to code in C++.
Very basic and simplistic and vulnerable as heck but it gets the job done.
**********************************/
//////////////////////////////////////////////////////////////////////////////
#include <iostream> //Input Output Stream
#include <iomanip> //Modifier library for IO Stream
#include <iomanip> //Manipulator header for IO Stream
#include <ctime> //Header used for getting system time
#include <string> //Header used for string types and conversions
#include <unistd.h> //Header used for sleep function (ms) through the OS API
#include <termios.h> //Used for... 'security' purposes
#include <fstream> //Filestream
using namespace std;
//////////////////////////////////////////////////////////////////////////////

int main()
{  
  /***********************
    cin.ignore(1000,'\n');
  ***********************/
  ////////////////////////////////////////////////////////
  time_t now = time(0); //Stores the current system time
  char* datetime = ctime(&now); //Stores the current system time as a character
  bool authorization = false; //Stores whether the user's password input is legitimate
  bool inputInvalid = false; //If the input is invalid, this will trigger the proper following code
  string hack =  "Root Hack.exe"; //Shortcut for Root Hack because lazy
  string CC = "Server-Sided Cougar Courses Root Access"; //Shortcut for Cougar Courses because lazy
  string DoD = "Department of Defense Direct Comm-Link"; //Shortcut for DoD because lazy
  string DDOS = "DDoS - Packet Magic"; //Magic!
  string NSA = "NSA Override.exe"; //Overide executable
  string login; //Stores the user's logon (password, lol security is a joke)
  string compare; //Compares the user's input to the encrypted, salted, and hashed password file
  string input; //Stores input for the executable to run
  string command; //Check
  string input2; //Check
  ifstream fin; //File read in
  ofstream fout; //File read out
  ////////////////////////////////////////////////////////

  //Hides text input for password and gets system time
  termios oldt;
  tcgetattr(STDIN_FILENO, &oldt);
  termios newt = oldt;
  newt.c_lflag &= ~ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  cout << endl << endl;
  cout << "[NETW:/1: 3-A3:54I] Initialization: " << datetime << endl;
  cout << "[SYSTEM] Booting up internal mainframe... Please wait..." << endl << endl;
  usleep(5000000);
  cout << "[SYSTEM] *-*UNAUTHORIZED*-* PLEASE ENTER [NETW://A-1] MAXIMUM SECURITY ACCESS CODE TO ACCESS [3-A3:54I] MAINFRAME" << endl;
  getline (cin,login);
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  
  fin.open("crypt.dat");
  fin >> compare;

  while(fin)
    {      
      if (login == compare)
	{
	  authorization =  true;
	  fin.close();
	}
      fin >> compare;
    }
  fin.close();

  cout << "****************";
  cout << "\n[SYSTEM] VERIFYING ACCESS CODE..." << endl;
  usleep(9000000);

  if (authorization == false)
  {
    cout << "[SYSTEM SECURITY] AN INVALID/UNAUTHORIZED ACCESS CODE WAS ENTERED. SYSTEM ENTERING LOCKDOWN..." << endl << endl;
    usleep(3000000);
    cout << "[SYSTEM SECURITY] ERROR: SYSTEM LOCKED DOWN DUE TO DETECTED BREACH OF THE MAINFRAME. [3-A3] LEVEL AUTHORITIES HAVE BEEN NOTIFIED." << endl << endl;
    usleep(7000000);
    cout << "[SYSTEM SECURITY] AWAITING ADMINISTRATIVE LOCKDOWN OVERRIDE..." << endl;
    usleep(2147483647);
    return 0;
  }

  else if (authorization == true)
  {
    cout << "[SYSTEM] VERIFIED" << endl;
    usleep(5000000);
    cout << "[SYSTEM] MATCHING RECORDS..." << endl;
    usleep(6000000);
    cout << "[SYSTEM] DECRYPTING MAINFRAME MASTER ACCESS INDICES..." << endl;
    usleep(5000000);
    cout << "[SYSTEM] CONSTRUCTING ADDITIONAL PYLONS..." << endl;
    usleep(3000000); 
    cout << "[SYSTEM] *-*AUTHORIZED*-* SUPER USER ACCESS ACCEPTED. ACCESSING THE MAINFRAME.." << endl << endl << endl << endl;
    usleep(1500000);
  
      cout << "[3-A3:54I Mainframe] Welcome, Super User" << "Please select a master executable to run: " << endl << endl << endl;
      cout << "-----------------------------------------------------" << endl; 
      cout << "                     Executables                     " << endl;
      cout << "-----------------------------------------------------" << endl;
      cout << "1. " << hack << endl << endl;
      cout << "2. " << CC << endl << endl;
      cout << "3. " << DoD << endl << endl; 
      cout << "4. " << DDOS << endl << endl;
      cout << "5. " << NSA << endl << endl;
      cout << "-----------------------------------------------------" << endl << endl << endl;
 
      do
	{     
	  cout << "Run> ";
	  //cin.ignore(50,'\n');
	  getline(cin, input);

	  if (input == "Root Hack.exe" || input == "1")
	    {
	      cout << "Root Hack.exe initializing... Please wait..." << endl << endl;
	      usleep(5000000);
	      cout << "Welcome, Super User" << endl;
	      cout << "Enter a command: ";
	      cin >> command;
	  
	      if (command == "Hack the NSA" || "Hack into the NSA")
		{
		  cout << endl;
		  cout << "NSA_Hack_booter.exe.cmd starting... " << endl;
		  usleep(6000000);
		  cout << "DDoSing NSA security... Standby... " <<endl;
		  usleep(8000000);
		  cout << "Successful" << endl;
		  usleep(2000000);
		  cout << "Overriding firewall... " << endl;
		  usleep(7000000);
		  cout << "ERROR_VAR_FUNCTION_RUN_OVERRIDE... " << endl;
		  usleep(4000000);
		  cout << "EXECUTING OVERRIDE VAR_42E.EXE... " << endl;
		  usleep(9000000);
		  cout << "VAR_42E.EXE OVERRIDE SUCCESSFUL" << endl << endl;
		  usleep(2000000);
		  cout << "NSA_Backdoor>";
		  cin.ignore(1000,'\n');
		  getline (cin,input2);
		  cout << "Rooting into direct Executive comm link..." << endl;
		  usleep(9000000);
		  usleep(9000000);
		  cout << endl;
		  cout << "Success" << endl << endl;
		  cout << "Welcome, President Trump" << endl;
		  cout << "Issue Executive Order: ";
		  getline (cin,input2);
		  cout << "Confirm " << "'" << input2 << "'" << " ? " << "(Y/N)" << endl;
		  cin >> input2;
		  cout << endl;
		  usleep(3000000);
		  cout << "Executive order initiated. May God bless this country." << endl << endl;
		  usleep(2000000);
		  cout << "Cleaning up traces..." << endl;
		  usleep(4000000);
		  cout << "Purging -X:/%AppData%/Local/Temp" << endl;
		  usleep(2000000);
		  cout << "Purging -X:/%AppData%/Local/Logs" << endl;
		  usleep(2000000);
		  cout << "Purging -X:/%AppData%/Local/Traces" << endl;
                  usleep(2000000);
		  cout << "Purging -X:/%AppData%/Local/recently-used.xbel" << endl;
                  usleep(2000000);
		  cout << "Purging -X:/%AppData%/Roaming/trace_FilterInstaller.dat" << endl;
                  usleep(2000000);
		  cout << "Purging -X:/%AppData%/Roaming/trace_FilterInstaller.txt-CRT.meta" << endl;
                  usleep(2000000);
		  cout << "Purging -X:/%AppData%/Roaming/WB.cfg" << endl;
                  usleep(2000000);
		  cout << "Purging -X:/%AppData%/Roaming/JP2K CS6 Prefs" << endl;
                  usleep(2000000);
		  cout << "Purging -X:/%AppData%/LocalLow/wbk9969.tmp" << endl;
                  usleep(2000000);
		  cout << "Purging -X:/%AppData%/LocalLow/Temp" << endl;
                  usleep(2000000);
		  usleep(5000000);
		  cout << "Done. Exiting..." << endl << endl;
		}
	      /*
		else if (command = "placeholder")
		{
		executive:
		}
	      */
	    }
	  else if (input == "Server-Sided Cougar Courses Root Access")
	    {
	      cout << "It in progress after 5 months :o." << endl;
	    }
	  else if (input == "Department of Defense Direct Comm-Link")
	    {
	      //
	    }
	  else if (input == "DDoS - Packet Magic")
	    {
	      //
	    }
	  else if (input == "NSA Override.exe")
	    {
	      //
	    }
	  else
	    {
	      inputInvalid = true;
	      cout << "Sorry, that executable doesn't exist. Please Try Again." << endl << endl;
	    }
	}while(inputInvalid == true);

  return 0;
  }
}
