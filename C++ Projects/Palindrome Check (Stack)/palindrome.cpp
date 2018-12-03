#include "palindrome.h"

#include <iostream>

using std::cout;
using std::endl;

Stack::Stack()
{
	top = -1;
}

//Iteratively pops all elements from our stack for when the user decides to check another string during the same program run.
void Stack::deleteStackContents()
{
	if (!isEmpty())
	{
		for (int i = top; i > -1; i--)
		{
			pop();
		}
	}
}
void Stack::push(const char &c)
{
	top++;
	characterList.insert(characterList.begin() + top, c);
}

void Stack::pop()
{
	if (isEmpty())
	{
		cout << "Error(Stack Underflow): Stack is empty, can not pop data from stack.\n";
	}
	else
	{
		characterList.erase(characterList.begin() + top);
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

bool Stack::isPalindrome(const string &str)
{
	bool palindrome = false;

	for (int i = 0; i < top/2; i++)
	{
		if (characterList[top - i] == characterList[i])
		{
			palindrome = true;
		}
		else
		{
			palindrome = false;
			break;
		}
	}
	if (str.length() == 0 || str.length() == 1)
	{
		palindrome = true;
	}

	if (palindrome == true)
	{
		cout << "\"" << str << "\" is a palindrome!\n";
		return palindrome;
	}
	else
	{
		cout << "\"" << str << "\" is not a palindrome!\n";
		return palindrome;
	}
}

void Stack::deleteStack()
{
	deleteStackContents();
}

void Stack::print()
{
	if (isEmpty())
	{
		cout << "The stack is currently empty. Nothing to print.\n";
	}
	for (int i = top; i >= 0; i--)
	{
		cout << i << endl;
	}
}
