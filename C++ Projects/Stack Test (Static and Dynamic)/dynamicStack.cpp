#include "dynamicStack.h"
#include <iostream>

#define print(sent) cout << sent << endl //memes

using std::cout;
using std::endl;

Stack::Stack()
{
	top = nullptr;
}

Stack::~Stack()
{
	if (isEmpty() == true)
	{
		print("[Empty] The stack is currently empty.\n");
	}
	else
	{
		while (top != nullptr)
		{
			StackNode *nodePointer;
			
			nodePointer = top;
			top = top->next;
			delete nodePointer;
		}
	}
}

void Stack::push(el_t c)
{
	StackNode *nodePointer;

	nodePointer = new StackNode; //Allocate memory for a new node
	nodePointer->element = c; //Set node data
	nodePointer->next = top; //Move next pointer to top
	top = nodePointer; //Point top to new node pointer
}

void Stack::pop(el_t &c)
{
	if (isEmpty() == false)
	{
		StackNode *nodePointer;

		c = top->element;
		nodePointer = top;
		top = top->next;
		delete nodePointer;
	}
	else
	{
		print("Error(Stack Underflow): Stack is empty, can not pop data from stack.\n");
		return;
	}
}

void Stack::getTop(el_t &c) const
{
	c = top->element;
}

void Stack::displayAll() const
{
	StackNode *nodePointer;

	nodePointer = top;

	if (isEmpty())
	{
		print("[Empty] The stack is currently empty.\n");
	}
	else
	{
		while (nodePointer != nullptr)
		{
			print(nodePointer->element);
			nodePointer = nodePointer->next;
		}
	}
}

bool Stack::isEmpty() const
{
	if (top == nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}