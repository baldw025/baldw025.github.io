#pragma once
#include <string>
#include <vector>

using std::cout;
using std::string;
using std::vector;

class Stack
{
private:
	int top; //Track top level element position in stack
	vector<char> characterList; //Using a vector in lieu of manual dynamic malloc methods because chief called and he said that ain't it. (Avoid memory leaks for now as this is a fairly lightweight program)
	void deleteStackContents();
public:
	Stack();
	void push(const char &);
	void pop();
	bool isEmpty();
	bool isPalindrome(const string &);
	void deleteStack();
	void print();
};
