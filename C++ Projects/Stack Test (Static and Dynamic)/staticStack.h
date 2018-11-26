#pragma once

const int MAX = 5;
typedef char character; //hahahehahhahahshahhahahahahaa

class Stack
{
private:
	character ar[MAX];
	int top;
public:
	Stack(); //Def. Constructor
	void push(character); //Add to stack
	void pop(character &); //Remove from stack
	bool isEmpty(); //Check if stack is empty
 	bool isFull(); //Check if stack is full
	void displayAll(); //Display contents of the stack
};
