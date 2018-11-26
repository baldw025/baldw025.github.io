#include "staticStack.h"
#include <iostream>

#define print(sent) cout << sent << endl //memes

using std::cout;
using std::endl;

Stack::Stack()
{
	top = -1;
}

void Stack::push(character c)
{
	if (isFull())
	{
		print("Error(Stack Overflow): Stack is full, can not push new data to stack.\n");
		return;
	}
	else
	{
		top++;
		ar[top] = c;
	}
}

void Stack::pop(character &c)
{
	if (isEmpty())
	{
		print("Error(Stack Underflow): Stack is empty, can not pop data from stack.\n");
		return;
	}
	else
	{
		c = ar[top];
		top--;
	}
}

bool Stack::isEmpty()
{
	if (top <= -1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Stack::isFull()
{
	if (top == MAX - 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Stack::displayAll()
{
	if (isEmpty())
	{
		print("[Empty] The stack is currently empty.\n");
	}
	else
	{
		for (int i = top; i >= 0; i--) //Move down the stack, starting from top
		{
			print(ar[i]);
		}
	}
}