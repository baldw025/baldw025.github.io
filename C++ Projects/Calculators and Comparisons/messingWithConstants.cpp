/*****
This program will get a user's info and the radius of a circle. The program will then output the area and circumference of the circle and the user's info.
*****/

#include <iostream> //Input output for cin, cout
#include <iomanip> //Defines manipulator flags for the namespace
using namespace std; //Sets the namespace to standard

int main()

{
 std::cout << std::setprecision(2) << std::fixed;

 const float PI = 3.14;
 int age; //Will store the user's age
 float gpa; //Will store the user's GPA as a float
 string gender; //Will store the users gender as a character
 float area; //Will store the final solved area as a float
 float circumference; //Will store the final solved circumference as a float
 float diameter; //Will store a backend calculated diamter
 float radius; //Will store the user's inputted radius as a possible float
 string name; //Will store the user's name as a string
 float radius_squared; //A messy storage of the radius squared

 //Asks for the user's information then stores in the above variables
 cout << "Hello! Please input your first name: " <<endl;
 cin >> name;
 cout << "Now enter your gender. Enter 'Male' for Male or 'Female' for Female: " <<endl;
 cin >> gender;
 cout << "Thank you, now, please enter your age: " <<endl;
 cin >> age;
 cout << "Please enter your Grade Point Average: " <<endl;
 cin >> gpa;
 cout << "Fantastic. Now, please give me a radius of a circle. I will then calculate its circumference and area: " <<endl;
 cin >> radius;

 //Does math for the circle
 diameter = radius * 2;
 circumference = PI * diameter;
 radius_squared = radius * radius;
 area = PI * radius_squared;

 cout << "Hello " <<name;
 cout << "! ";
 cout << " You are a " <<age; 
 cout << " year old " <<gender;
 cout << " with a grade point average of " <<gpa;
 cout << ". The area of your circle is " <<area;
 cout << " and the circumference of it is " <<circumference <<endl;
 return 0;
}
