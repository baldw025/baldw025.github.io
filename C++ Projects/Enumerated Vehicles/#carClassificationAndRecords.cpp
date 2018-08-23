/*************************
This program will use enumerated classes to store vehicle information, such as VIN, make, model, color, year, mileage, and a general bearing of their direction.
Also simulates a car's position while navigating through city blocks. Fun stuff!
It's car stuff. Short throw dipsticks and stickers for bhp gains.
**************************/
#include <iostream>
using namespace std;

enum direc {NORTH, EAST, SOUTH, WEST}; //a variable of direction can store NORTH, EAST, SOUTH or WEST

class Car   //declare a class called Car
{
  private:  //attributes(data members) are declared private or public?
  string VIN;
  string make;  //What is the data type of the make of a car?
  string model;
  string color;
  int year;  //What is the data type of the year of a car?
  int mileage;
  direc direction;  //What is the data type of this?
  int X;  //X location of a car. e.g. 5
  int Y;  //Y location of a car. e.g. 8  

  public:  //attributes(data members) are declared private or public?
  //list prototypes here
  Car(string v, string mk, string md, string c, int yr);  //prototype of the constructor
  string getModel();  //prototype of getModel
  string getMake();
  void goForward(int blks);
  int getMileage();
  direc getDirection();
  int getX();
  int getY();
  void turnRight();
  void turnLeft();
  string getColor();
  int getYear();
};

//Constructor//
///////////////////////////////////////////////////////////////
Car::Car(string v, string mk, string md, string c, int yr) //mk is the make of a car, yr is the year of a car
{
  //set the attributes, VIN, make, model, color and year to the parameter values
  VIN = v;
  make = mk;
  model = md;
  color = c;
  year = yr;
  //set mileage to 0 - brand new car
  mileage = 0;
  //a car faces North initially
  direction = NORTH;
  //a car is located at (0, 0) initially
  X = 0;
  Y = 0;
}

//Functions//
///////////////////////////////////////////////////////////////
string Car::getModel()
{
  //returns the model
  return model;
}

string Car::getMake()
{
  return make;
}

void Car::goForward(int blks)
{
  if(direction == NORTH)
    {
      Y += blks;
    }
  else if(direction == EAST)
    {
      X += blks;
    }
  else if(direction == SOUTH)
    {
      Y -= blks;
    }
  else if(direction == WEST)
    {
      X -= blks;
    }

  mileage += blks;
}

int Car::getX()
{
  //returns the X location
  return X;
}

int Car::getY()
{
  //returns the Y location
  return Y;
}

void Car::turnRight()
{
  if(direction < WEST)
    {
      direction = (direc)(direction + 1);
    }
  else // direction is WEST
    {
      direction = NORTH;  //If the car is facing WEST then turns right, which direction will it face?
    }
}

void Car::turnLeft()
{
  if(direction == NORTH)
    {
      direction = WEST;  //If the car is facing North then turns left, which direction will it face?
    }
  else
    {
      direction = (direc)(direction - 1);
    }
}

int Car::getMileage()
{
  return mileage; //return the mileage on a car
}

direc Car::getDirection()
{
  return direction;
}

string Car::getColor()
{
  return color;
}

int Car::getYear()
{
  return year;
}
///////////////////////////////////////////////////////////////

int main()
{
  string dir1;
  string dir2;

  Car c1("w12345", "Koenigsegg", "One:1", "Blue Mystichrome with Clear Carbon", 2017);

  cout << "Car Model: " << c1.getModel() << endl;
    
  cout << "The " << c1.getYear() << " " << c1.getMake() << " " << c1.getModel() << " (Body Color Finish: " << c1.getColor() << ")" << " is starting at coordinate " << "(" << c1.getX()<< "," << c1.getY() << ")" << endl;
  c1.goForward(3);
  cout << "The " << c1.getModel() << " is now at coordinate " << "(" << c1.getX()<< "," << c1.getY() << ")" << endl;
  c1.turnRight();
  c1.goForward(5);
  cout << "The " << c1.getModel() << " is now at coordinate " << "(" << c1.getX()<< "," << c1.getY() << ")" << endl;
  c1.turnRight();
  c1.goForward(7);
  cout << "The " << c1.getModel() << " is now at coordinate " << "(" << c1.getX()<< "," << c1.getY() << ")" << endl;
  c1.turnRight();
  c1.goForward(6);
  cout << "The " << c1.getModel() << " is now at coordinate " << "(" << c1.getX()<< "," << c1.getY() << ")" << endl;

  switch(c1.getDirection())
    {
    case 0: dir1 = "North";
      break;
    case 1: dir1 = "East";
      break;
    case 2: dir1 = "South";
      break;
    case 3: dir1 = "West";
      break;
    }

  cout << endl << "The " << c1.getMake() << " " << c1.getModel() << "'s" << " mileage is logged at " << c1.getMileage() << " miles and the vehicle is now facing " << dir1 << " at coordinate (" << c1.getX() << "," << c1.getY() << ")." << endl;

  cout << "************************************************************" << endl;

  Car c2("J12345", "BMW", "E92 M3", "Alpine White", 2013);

  cout << "Car Model: " << c2.getModel() << endl;
      
  cout << "The " << c2.getYear() << " " << c2.getMake() << " " << c2.getModel() << " (Body Color Finish: " << c2.getColor() << ")" << " is starting at coordinate " << "(" << c2.getX()<< "," << c2.getY() << ")" << endl;
  c2.goForward(5);
  cout << "The " << c2.getModel() << " is now at coordinate " << "(" << c2.getX()<< "," << c2.getY() << ")" << endl;
  c2.turnLeft();
  c2.goForward(1);
  cout << "The " << c2.getModel() << " is now at coordinate " << "(" << c2.getX()<< "," << c2.getY() << ")" << endl;
  c2.turnLeft();
  c2.goForward(2);
  cout << "The " << c2.getModel() << " is now at coordinate " << "(" << c2.getX()<< "," << c2.getY() << ")" << endl;
  c2.turnLeft();
  c2.goForward(4);
  cout << "The " << c2.getModel() << " is now at coordinate " << "(" << c2.getX()<< "," << c2.getY() << ")" << endl;
  c2.turnLeft();
  c2.goForward(10);
  cout << "The " << c2.getModel() << " is now at coordinate " << "(" << c2.getX()<< "," << c2.getY() << ")" << endl;

  switch(c2.getDirection())
    {
    case 0: dir2 = "North";
      break;
    case 1: dir2 = "East";
      break;
    case 2: dir2 = "South";
      break;
    case 3: dir2 = "West";
      break;
    }

  cout << endl << "The " << c2.getMake() << " " << c2.getModel() << "'s" << " mileage is logged at " << c2.getMileage() << " miles and the vehicle is now facing " << dir2 << " at coordinate (" << c2.getX() << "," << c2.getY() << ")." << endl;

  return 0;
}

//Test: (3,13) North 22 Milies
