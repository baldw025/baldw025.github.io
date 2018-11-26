#pragma once

typedef char el_t;

class Stack
{
private:
	struct StackNode
	{
		el_t element;
		StackNode *next;
	};

	StackNode *top;
public:
	Stack(); //Def.Constructor
	~Stack(); //Destructor
	void push(el_t);
	void pop(el_t &);
	void getTop(el_t &) const;
	void displayAll() const;
	bool isEmpty() const;
};
