#include "balancedDelimiterCheck.h"
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

//Calculates and decides if a user-defined string has an equal (balanced) number of matching delimiters: { } ( ) [ ]. If not balanced, we tell the user why.
bool Stack::isProperlyBalanced(const string &str)
{
	char currentChar = NULL;
	int left = 0; //A, uh, "fix" for lone right delimiters. Left and right will increase by one each time a left or right delimiter is found, decrease by one if a matching pair is found. I'm tired.
	int right = 0;

	if (int(str.length()) == 0)
	{
		cout << "Error: User-defined string is empty. Nothing to check.\n";
		return false;
	}
	
	deleteStackContents(); //Clears out contents of stack for next balance check operation

	/*While iterating through the user's string, a switch will push any found delimiters (cases) to our stack for future balance comparison
	When a case is true, push left delimiters to stack, compare right delimiters to top of stack. Report results afterwards.*/
	for (int i = 0; i < int(str.length()); i++)
	{
		switch (str[i])
		{
		case '{':
		case '(':
		case '[':
			left++;
			currentChar = str[i];
			push(currentChar);
			break;
		case '}':
		case ')':
		case ']':
			right++;
			currentChar = str[i];
			if (isEmpty())
			{
			}
			/*
			Following else-if statement is based on finding the "opposite/closing" delimiter of current delimiter through the use of ASCII decimals.
			"(" (40) + 1 == ")" (41)
			"[" (91) + 2 == "]" (93)
			"{" (123) + 2 == "}" (125)
			*/
			else if (currentChar == char(characterList[top]) + 1 || currentChar == char(characterList[top]) + 2 && !isEmpty())
			{
				pop();
				left--;
				right--;
			}
			break;
		default:
			break;
		}
	}
	if (!isEmpty() && currentChar != char(characterList[top]))
	{
		cout << "Unbalanced Delimiters: Delimiter Mismatch.\n";
		return false;
	}
	if (left != 0 && right != 0)
	{
		cout << "Unbalanced Delimiters: Missing left and right delimiter(s).\n";
		return false;
	}
	if (isEmpty() && right != 0)
	{
		cout << "Unbalanced Delimiters: Missing left delimiter(s).\n";
		return false;
	}
	if (isEmpty() && left != 0 || !isEmpty())
	{
		cout << "Unbalanced Delimiters: Missing right delimiter(s).\n";
		return false;
	}
	if (currentChar == NULL) //Only true if we never enter the for-loop
	{
		cout << "The user-defined string contains no delimiters.\n";
		return false;
	}
	if (isEmpty() && left == 0 && right == 0)
	{
		cout << "Delimiters are balanced.\n";
		return true;
	}
	return false;
}