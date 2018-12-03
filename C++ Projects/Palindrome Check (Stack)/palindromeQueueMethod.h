#pragma once
#include <vector>

const int MAX = 5;

class Queue
{
private:
	char ar[MAX];
	int front;
	int rear;
	int count;

public:
	Queue();
	void enqueue(const char &);
	void dequeue();
	bool isFull();
	bool isEmpty();
	void displayAll();
};