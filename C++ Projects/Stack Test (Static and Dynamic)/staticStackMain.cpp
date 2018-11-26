#include "staticStack.h"
#include <iostream>

#define print(sent) cout << sent << endl //memes

using std::endl;
using std::cout;

int main()
{
	Stack s;
	character c;

	print("Initial stack contents:");
	s.displayAll();
	s.pop(c);
	s.push('a');
	print("Stack contents after pushing a: ");
	s.displayAll();
	print("");

	s.push('b');
	print("Stack contents after pushing b:");
	s.displayAll();
	print("");

	s.push('c');
	s.push('d');
	s.push('e');
	s.push('f');
	s.push('g');
	print("Stack contents after pushing c-g:");
	s.displayAll();
	print("");

	s.pop(c);
	print("Popping element: " << c);
	print("Stack contents after popping one element:");
	s.displayAll();
	print("");

	s.pop(c);
	print("Popping element: " << c);
	print("Stack contents after popping another element:");
	s.displayAll();
	print("");

	s.pop(c);
	s.pop(c);
	s.pop(c);
	print("Stack contents after popping 3 more elements:");
	s.displayAll();
	print("");

	s.pop(c);
	s.push('a');
	s.push('b');
	print("Final stack contents:");
	s.displayAll();

	return 0;
}