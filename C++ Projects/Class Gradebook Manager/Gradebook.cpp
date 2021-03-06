/*
This program will help manage a dynamic gradebook of students. It will keep track of students' names, id numbers, and four exam grades.
It will read in commands from a file that allows us to enroll a student, drop a student, upload a student's grades, search for a student, and display various results of the class.
Only a maximum of four exam grades are allowed.
*/

#include <iostream> //For displaying info to the buffer
#include <iomanip> //For manipulating the input output stream
#include <fstream> //For illegally streaming files
#include <vector> //For creating a dynamic vector of struct
#include <string> //For manipulating strings against their will

//Our struct with members in respect to students' information
struct Student
{
	std::string name; //FN LN
	long id; //StuID
	double grades[4]; //Array for four exam grades
	double averageGrade; //Stores the student's average grade from all 4 exams. Because we can.
};

/*Functions*/
void processFile(std::vector<Student> &students);
void enroll(const std::string &firstName, const std::string &lastName, const int &stuID, std::vector<Student> &students);
void display (const std::vector<Student> &students);
void searchByName(const std::vector<Student> &students, const std::string &keyword);
void drop(std::vector<Student> &students, const int &studentID);
void uploadGrades(std::vector<Student> &students, const int &studentID, const float &exam1, const float &exam2, const float &exam3, const float &exam4);
void printClassSummary(const std::vector<Student> &students);

//A clean main function is a happy function
int main()
{
	std::vector<Student> students; //Declare our vector of struct for our students. Always gets passed by reference.

	processFile(students); //Call the function that will read and analyze our external document. Pass our struct as an argument.

	return 0;
}

//Reads into our student information file and calls respective read commands
void processFile(std::vector<Student> &students)
{
	std::ifstream fin; //Salmon fin
	std::string firstName; //Stores a student's first name
	std::string lastName; //Stores a student's last name
	std::string command; //Stores the current read command to process
	std::string keyword; //Part of a name to pass and search for. Can be first name, last name, or full name
	long stuID; //Stores a student's id to later pass (Max 32-bit signed 2.147)
	float exam1, exam2, exam3, exam4; //Stores exam scores listed in external file

	fin.open("StudentsTrans.txt");
	{
		if(!fin)
		{
			std::cout << "The student gradebook can not be opened or does not exist.\n\n";
		}
		else
		{
			fin >> command;
			while(fin)
			{
				if(command == "enroll")
				{
					fin >> firstName >> lastName >> stuID;
					enroll(firstName, lastName, stuID, students); //Call the function that will attempt to enroll a student that isn't currently enrolled.
				}
				if(command == "display")
				{
					display(students); //Call the function that will display the entirety of the course gradebook.
				}
				if(command == "searchByName")
				{
					getline(fin, keyword); //Use getline so we can search for a first, last, or full name in our gradebook.
					searchByName(students, keyword); //Call the function that will search for a student and display the student's, or students', info.
				}
				if(command == "drop")
				{
					fin >> stuID;
					drop(students, stuID); //Call the function that will attempt to drop a student from the course if they are currently enrolled.
				}
				if(command == "uploadGrades")
				{
					fin >> stuID >> exam1 >> exam2 >> exam3 >> exam4;
					uploadGrades(students, stuID, exam1, exam2, exam3, exam4); //Call the function that will upload a student's exam grades. Also calculates and stores the students' grade average struct member.
				}
				if(command == "printClassSummary")
				{
					printClassSummary(students); //Call the function that will display the student with the highest grade in the class, lowest grade in the class, and the overall class average.
				}
				fin >> command;
			}
		}
		fin.close();
	}
}

//Adds a student's name and id to our vector of struct. Initializes their grade array indices to 0.
//Returns an error if a student already exists
void enroll(const std::string &firstName, const std::string &lastName, const int &stuID, std::vector<Student> &students)
{
	bool duplicate = false; //True if the passed student is already enrolled in the course.
	int i = 0; //For tracking vector indices
	std::string stuName = firstName + " " += lastName; //Concatenate student first and last name with a separating whitespace.

	//Checks if a user ID already exists. Triggers a duplicate flag if true.
	for(i; i != students.size(); i++)
	{
		if(students[i].id == stuID)
		{
			std::cout << "Error: " << stuName << " is already enrolled in this class.\n";
			duplicate = true;
		}
	}

	//If the current student is unique, (not enrolled) add them to our vector of struct by push back and set and initialize proper struct members.
	//Yes, it stores a concatenated name (FN + LN), as requested.
	if(!duplicate)
	{
		students.push_back(Student());
		students[i].name = stuName;
		students[i].id = stuID;
		students[i].averageGrade = 0.0;
		for(int x = 0; x < 4; x++)
		{
			students[i].grades[x] = 0.0;
		}
		std::cout << "Successfully enrolled " << stuName << " to the class.\n";
	}
}

//Displays a fancy table of all of our enrolled students' information. Scores are within a precision of 2. Also quickly calculates and outputs the student's exam score average.
void display(const std::vector<Student> &students)
{
	std::cout  << std::setw(41) << std::right << "___________\n" << std::setw(41) << std::right << "|Gradebook|\n" << "-------------------------------------------------------------------------\n" << std::left << std::setw(20) << "Student" << std::left << std::setw(13) << "ID" << std::left << std::setw(7) << "Exam1" << std::left << std::setw(7) <<  "Exam2" << std::left << std::setw(7) << "Exam3" << std::left << std::setw(7) << "Exam4" << std::left << std::setw(11) << "Final Grade\n"
			   << "-------------------------------------------------------------------------\n";
	for(int x = 0; x != students.size(); x++)
	{
		std::cout << std::left << std::setw(20) << students[x].name << std::left << std::setw(13) << students[x].id << std::left << std::setw(7) << std::showpoint << std::setprecision(2) << std::fixed << students[x].grades[0] << std::left << std::setw(7) << students[x].grades[1] << std::left << std::setw(7) << students[x].grades[2] << std::left << std::setw(7) << students[x].grades[3] << std::left << std::setw(11) << students[x].averageGrade << std::endl;
	}
	std::cout << std::endl << std::endl;
}

//Searches our vector of struct for any first, last, or full names that match a keyword/passed name.
//Prints out any found matches along with all matching students' info and grades.
void searchByName(const std::vector<Student> &students, const std::string &keyword)
{
	bool found = false;; //True if a matching first, last, or full name is found. Also used to prevent buffer output loop.

	std::cout << "Matches found for:" << keyword << "\n" << "-------------------------------------------------------------------------\n" << std::left << std::setw(20) << "Student" << std::left << std::setw(13) << "ID" << std::left << std::setw(7) << "Exam1" << std::left << std::setw(7) << "Exam2" << std::left << std::setw(7) << "Exam3" << std::left << std::setw(7) << "Exam4" << std::left << std::setw(11) << "Final Grade\n"
		<< "-------------------------------------------------------------------------\n";

	for (int i = 0; i != students.size(); i++)
	{
		std::string key = keyword.substr(0 + 1); //Fixes/Removes the leading whitespace caused by using getline with the current external file format. If it works, it works ¯\_(ツ)_/¯
		std::string firstName = students[i].name.substr(0, students[i].name.find(' ')); //First name substring of full name string stored in our vector of struct. Needed for first name condition check.
		std::string lastName = students[i].name.substr(students[i].name.find(' ') + 1); //Last name substring of full name string stored in our vector of struct. Needed for last name condition check.
		
		//If the passed first, last, or full name/"keyword" is found in our vector of struct, print the student's information and set our found flag to true.
		if (firstName == key || lastName == key || students[i].name == key)
		{
			found = true;
			std::cout << std::left << std::setw(20) << students[i].name << std::left << std::setw(13) << students[i].id << std::left << std::setw(7) << std::showpoint << std::setprecision(2) << std::fixed << students[i].grades[0] << std::left << std::setw(7) << students[i].grades[1] << std::left << std::setw(7) << students[i].grades[2] << std::left << std::setw(7) << students[i].grades[3] << std::left << std::setw(11) << students[i].averageGrade << std::endl;
		}
	}
	std::cout << std::endl << std::endl;

	//If the student's first, last, or full name wasn't found
	if (!found)
	{
		std::cout << "None. " << keyword << " is not currently enrolled in this class.";
		std::cout << std::endl << std::endl << std::endl;
	}
}

//AKA the Thanos Snap function
//Makes a student not feel so good as it checks if a student exists in our vector of struct before erasing them from existence. Display a success or error message afterwards.
void drop(std::vector<Student> &students, const int &studentID)
{
	bool found = false; //Conditional flag to ensure we are [s]snapping[/s] dropping a valid student. And to avoid an output loop.

	for (int t = 0; t != students.size(); t++)
	{
		if (students[t].id == studentID)
		{
			found = true;
			std::cout << "Successfully dropped student " << studentID << " (" << students[t].name << ") from this class.\n"; //Snapped
			students.erase(students.begin() + t); //Search for the proper index to erase since we can't assume we can always pop back the vector
		}
	}

	if (!found)
	{
		std::cout << "Error: Can not drop student " << studentID << " (Unknown) as they are not enrolled in this class.\n"; //Saved
	}
}

//Sets the indices of our struct's member array of student grades.
//Also checks if a student exists or not before we try uploading grades. Check if student ID exists
void uploadGrades(std::vector<Student> &students, const int &studentID, const float &exam1, const float &exam2, const float &exam3, const float &exam4)
{
	bool found = false; //Conditional flag to ensure we are uploading grades to a valid student. And to avoid an output loop.

	for (int i = 0; i != students.size(); i++)
	{
		if (students[i].id == studentID)
		{
			found = true;
			students[i].grades[0] = exam1;
			students[i].grades[1] = exam2;
			students[i].grades[2] = exam3;
			students[i].grades[3] = exam4;
			students[i].averageGrade = (exam1 + exam2 + exam3 + exam4) / 4;
			std::cout << "Successfully uploaded " << students[i].name << "'s grades.\n";
		}
	}

	if (!found)
	{
		std::cout << "Error: Can not upload grades for student " << studentID << " (Unknown) as they are not enrolled in this class.\n";
	}
}

//Calculates and displays the students with the highest and lowest grade along with the overall class average (Final grade)
void printClassSummary(const std::vector<Student> &students)
{
	int lowestIndex = 0; //Stores the index of the student with the lowest overall grade. Used for easy reference when displaying final results
	int highestIndex = 0; //Stores the index of the student with the highest overall grade. Used for easy reference when displaying final results
	double highestGrade = 0.00;
	double lowestGrade = 999.99;
	double classAverage = 0.0;

	for (int i = 0; i != students.size(); i++)
	{
		if (students[i].averageGrade > highestGrade)
		{
			highestGrade = students[i].averageGrade; //Log the student's index if they have the current highest grade. Set their grade to the current highest.
			highestIndex = i;
		}
		else if (students[i].averageGrade < lowestGrade) //Log the student's index if they have the current lowest grade. Set their grade to the current lowest.
		{
			lowestGrade = students[i].averageGrade;
			lowestIndex = i;
		}
		classAverage += students[i].averageGrade;
	}
	classAverage /= students.size(); //Compound division assignment for class average.

	std::cout << students[highestIndex].name << " has the highest final grade in the class. (" << students[highestIndex].averageGrade << ")\n"
		      << students[lowestIndex].name << " has the lowest final grade in the class. (" << students[lowestIndex].averageGrade << ")\n"
		      << "The classes' overall final grade average is: " << classAverage << std::endl << std::endl;
}