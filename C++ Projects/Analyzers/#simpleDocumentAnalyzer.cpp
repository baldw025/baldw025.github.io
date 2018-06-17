/****************************
We have an input (data) file that has numerous amounts of words.
We will create functions that will account for the longest/shortest word per letter 
and count how many times a word begins with a letter. We will then have a "fancy" UI that will
allow a user to call any of the appropriate functions (letter counter, word table).
*****************************/

#include <iostream> //Somethin' somethin' input output stream. If you want a somewhat useful and interactive program, include it.
#include <iomanip> //Gotta manipulate the input output stream. Those set widths, y'know.
#include <fstream> //File stream. A stream of files. Soggy soggy files picked out of the local fish stream.
#include <cstdlib> //C Standard Library. I could never find a local library like this in my town.
#include "myStrCharFunc.h" //Our custom c-string header file. That does custom things to strings, without the string's consent.
using namespace std; //The namespace needs medical attention. It has a standard std.

const int SIZE = 26; //Global Constant that represents the number of letters in alphabet
const int MAX = 30; //Global constant that will act as our maximum word length
typedef char cstr[MAX]; //Creating a custom alias of cstr in terms of char

//Struct with members that account for an indices shortest, longest word along with repetition count.
struct wordyMcWordFace
{
  int count;
  cstr shortest;
  cstr longest;
};

void initializeArray(wordyMcWordFace ar[]);
void readFile(wordyMcWordFace ar[]);
void processWord(wordyMcWordFace ar[], cstr word);
void printInfoOnOneLetter(wordyMcWordFace ar[]);
void printInfoOnAllLetters(wordyMcWordFace ar[]);

int main()
{
  wordyMcWordFace ar[SIZE]; //Our array that will store information regarding each letter of the alphabet, ex: longest and shortest 'A' word and how many times a word begins with 'A' and etcetera 
  int input; //Stores the user's input in regards to the UI
  bool invalid; //A boolean that will track the user's incompetence, I mean, if the user's input is good or bad.

  initializeArray(ar); //Calls the function that will initialize all the indices of our array with a comparable long, short length and word count.
  readFile(ar); //Calls the function that will read all content from our defined "project2.dat" file. This function will also call our "processWord()" function that will check how long/short a word is, log it, then increase the appropriate letter counter in respect to what the current word begins with.
  //Somethin' like that, 'nam sayin'.

  //This do while loop will display a "user interface" to the user asking them which action they'd like to perform. If "1" is selected, we will print out a full table analysis regarding all letters and words in the document. If "2" is selected we will ask the user for a letter they'd like to analyze, and then
  //we will output how many times that a word began with that letter and what its longest and shortest words were, if applicable. If "3" is selected, we will terminate the program. If a number that != 1 - 3 is selected, we will continue to ask them to input a valid number selection. It happens and it sucks.
  do{
    invalid = false;

    cout << "____________________________________________________" << endl //52
	 << setw(36) << "Please Make a Selection" << endl
	 << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl
	 << "1. Show Information for All Letters in the Document" << endl
	 << "2. Show Information for One User-Defined Letter" << endl
	 << "3. Exit this program" << endl
	 << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl;
    cout << "> "; cin >> input;

    if (!cin) //If cin fails (refuses to work because it is FUBAR and needs to be cleared) due to user-negligence that throws the program into an infinite loop (user inputting a char or string or some other weirdness instead of an integer), we need to fix it by:
      {
	cin.clear(); //This will clear the fail state of cin, allowing it to properly read input again instead of throwing us into an infinite loop if above condition were to happen.
	cin.ignore(99, '\n'); //We want to ignore whatever else the user may have entered (up to 99 characters) and then start on a new line so we don't have their above mentioned weirdness in our cin buffer.
      }

    switch(input)
      {
      case 1: printInfoOnAllLetters(ar); //Calls the function that will print out a full table analysis regarding all letters and words in the document.
	break;
      case 2: printInfoOnOneLetter(ar); //Calls the function that will ask the user to input a letter to analyze and outputs an analysis on said letter.
	break;
      case 3: cout << "\nThank you for using this program. Exiting...\n"; //Terminate the program
	break;
      default: cout << "\nPlease enter a number selection ranging from 1 - 3. Please. P l e a s e." << endl; //Ask the user to input a valid selection choice because it's too hard to select a number 1 - 3. If only the world was a perfect place.
	invalid = true; //Sets the user's incompetence to true, which makes this loop again because that's how this do-while works, m'kay.
	break;
      }
  }while(invalid == true); //Above
    
  return 0;
}

/**********************************************************
This function will initialize our struct-based array
by setting each indices count and comparable short/long
variables to something, well, comparable with other strings.
**********************************************************/
void initializeArray(wordyMcWordFace ar[])
{
  //Starting at the first index of our array and ending at the last index, go through all the indices and set their character  counter to 0, initialize a temporary short and long string to compare later strings with. 
  for(int i = 0; i < SIZE; i++)
    {
      ar[i].count = 0;
      myStrcpy(ar[i].shortest, "xxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
      myStrcpy(ar[i].longest, "");
    }
}

/**********************************************************
This function will read content from our hard-coded data
file and then proceed to call the function that will process
each individual word in said data file.
**********************************************************/
void readFile(wordyMcWordFace ar[])
{
  ifstream fin; //Our variable that will be used to read into the file
  cstr word; //Our variable that will store the current read word from the file
  
  fin.open("project2.dat"); //Stating which file to look for and open
  
  if(!fin) //If the file does not exist, say so, then exit code 1.
    {
      cout << "The file can not open or does not exist. Hecking fix it, guy." << endl;
      exit(1); 
    }
  else //If the file DOES exist, store the current read word into cstr-based variable "word". Clever naming huh
    {
      fin >> word;

      //While there is still content to read in the file, call the function that will process said word, then read the next word, process, next word, in continuum, until there is no more content to read.
      while(fin)
	{
	  processWord(ar, word); //Calls the function that will analyze the current read word and determine said word's length, see if it is the longest or shortest word of its type, and then send me into a state of depression because oh my goodness coding it was a horror story.
	  fin >> word; //Read the next word in the file, if applicable
	}
    }

  fin.close(); //Close the file in stream, like a "good programmer"
}

/**********************************************************
This function. This freaking function. Wow. This function
will analyze the current passed word from the "readFile"
function. This is where we will account for its beginning letter
count, whether said word is the shortest or longest of its letter-type
among other horrid war crimes.
**********************************************************/
void processWord(wordyMcWordFace ar[], cstr word)
{
  char firstLetter = word[0]; //Our holy grail, we want to get the first letter of the passed word so we can easily do some checks later down the line. You'll see. Trust me.
  int stringLength; //Stores the length of the passed string
  int shortest; //Stores the length of the shortest index string
  int longest; //Stores the length of the longest index string

  //Type cast all the things because it makes things ez pz
  //Checks if the current passed string begins with a lowercase letter, converts it to upper if true. 
  //Why upper you ask? Because I find them easier to work with and remember their ascii values easily. (A)65 - 90(Z) end nicely too (0 and 5) as opposed to (a)97 - 122(z) (wtf). Yeah, I could just add 32 but no thanks.
  if(firstLetter >= 'a' && firstLetter <= 'z')
    {
      firstLetter = myToUpper(firstLetter);
    }

  //This section calls functions that will get and locally store the longest and shortest values of an index in respect to the current word passed. 
  //Ex. If the word passed begins with 'C' (67), get the member information from index 2 (67(C) - 65(A)) of our struct-based array and locally store them here for comparison
  shortest = myStrlen(ar[(int)firstLetter - 65].shortest);
  longest = myStrlen(ar[(int)firstLetter - 65].longest);
  stringLength = myStrlen(word);
  
  //Increases the count in respect to the current letter and its position in the array index
  ar[(int)firstLetter - 65].count++;
  
  //If the current word is longer than the current stored longest word, copy and store the longer word into the proper array index, which is in respect to the letter said word begins with
  if(stringLength > longest)
    {
      myStrcpy(ar[(int)firstLetter - 65].longest, word);
    }

  //If the current word is shorter than the current stored shortest word, copy and store the shorter word into the proper array index, which is in respect to the letter said word begins with
  if(stringLength < shortest)
    {
      myStrcpy(ar[(int)firstLetter - 65].shortest, word);
    }

  /*//Dev Testing/Debugging
  cout << "How many letters that start with (" << firstLetter << "): " << ar[4].count << endl;
  cout << "String Length: " << stringLength << endl;
  cout << "Longest: " << ar[4].longest << endl;
  cout << "Shortest: " << ar[4].shortest << endl;
  */
}

/**********************************************************
This function will ask the user to input a letter to obtain
information on (A - Z). We will then say if a word begins
with said letter and say how many times a word began with
the letter. Say otherwise if a word doesn't begin with the
user's letter. 
**********************************************************/
void printInfoOnOneLetter(wordyMcWordFace ar[])
{
  char userInput; //Stores the user's input on which letter to search for

  do
    {
      cout << "\nWhich letter would you like to check for?: "; //Prompt shown to user
      cin >> userInput; //Storing the user's input into our input-based variable
      userInput = myToUpper(userInput); //Converts the user's input to uppercase. Why? I stated why in processWord. It makes everyone's lives easier :^) Don't worry, it doesn't break if they input an uppercase letter. That's already handled in my function.

    }while(userInput < 'A' || userInput > 'Z');
  
  if(ar[(int)userInput - 65].count != 0)
    {
      cout << "-----------------------------------------------------------------------------------\n"
	   << "Words beginning with the letter '" << userInput << "' were found in the current file. (Frequency: " << ar[(int)userInput - 65].count << ")\n"
	   << "-----------------------------------------------------------------------------------\n\n";
    }
  else
    {
      cout << "--------------------------------------------------------------------------------------\n"
	   << "Words beginning with the letter '" << userInput << "' were not found in the current file. (Frequency: " << ar[(int)userInput - 65].count << ")\n"
	   << "--------------------------------------------------------------------------------------\n\n";
    }
}

/**********************************************************
This function will output ALL the information we have
gathered regarding all content in the file. Which is essentially
just outputting all the crap we have stored in the array indices.
I even made it into a nice a e s t h e t i c table. Cheers.
**********************************************************/
void printInfoOnAllLetters(wordyMcWordFace ar[])
{
  cout << endl; //An endboi

  //Starting at the first array index, going to the last index, output a line/letter with letter's information such as frequency and longest/shortest word.
  for(int i = 0; i < SIZE; i++)
    {
      cout << char('A' + i) << "| " << "Frequency: " << ar[i].count << "(";
      
      //Output one small starboi in respect to the letter's frequency
      for(int star = 0; star < ar[i].count; star++)
	{
	  cout << "*";
	}
      
      //If a word did not begin with a letter, override the line saying so. No ugly null outputs thanks
      if(ar[i].count == 0)
	{
	  cout << "-) " << "No words began with this letter" << endl;
	  cout << "¯  ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl;
	}
      //Else, if a word began with the letter, say what the longest and shortest words of said letter are
      else
	{
	  cout << ") " << "|Longest Word: " << ar[i].longest << "| |Shortest Word: " << ar[i].shortest << "|" << endl;
	  cout << "¯  ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl;
	}
    }
}