#include "palindromeQueueMethod.h"
#include <iostream>

using std::cout;
using std::endl;

Queue::Queue()
{
	front = -1;
	rear = -1;
	count = 0;
}

void Queue::enqueue(const char &c)
{
	if (isFull())
	{
		cout << "Error(Queue Overflow): Queue is full, can not enqueue character \"" << c << "\".\n";
	}
	else if (isEmpty())
	{
		front++;
		rear++;
		ar[rear] = c;
		count++;
		cout << "Successfully added character \"" << c << "\" to the queue.\n";
	}
	else
	{
		if (rear == MAX - 1) //If rear is at the last index in array, insert new element at the beginning of the array using a clever mod algorithm
		{
			rear = (rear + 1) % MAX; //Ex: (4 + 1) == 5. 5 % MAX(5) == 0 --> ar[rear == 0]
		}
		else
		{
			rear++;
		}
		count++;
		ar[rear] = c;
		cout << "Successfully added character \"" << c << "\" to the queue.\n";
	}
}

void Queue::dequeue()
{
	if (isEmpty())
	{
		cout << "Error(Queue Underflow): Queue is empty, can not dequeue a character.\n";
	}
	else
	{
		if (front == MAX - 1)
		{
			front = (front + 1) % MAX;
			count--;
			//cout << "Successfully removed character \"" << c << "\" from the queue.\n";
		}
		else
		{
			front++;
			count--;
			//cout << "\nSuccessfully removed character \"" << c << "\" from the queue.\n";
		}
	}
}

bool Queue::isFull()
{
	if (count == MAX)
	{
		return true;
	}
	return false;
}

bool Queue::isEmpty()
{
	if (count == 0)
	{
		return true;
	}
	return false;
}

void Queue::displayAll()
{
	if (isEmpty())
	{
		cout << "The queue is currently empty.\n";
	}
	else
	{
		//If the front/first element of the queue comes before the rear element (chronological queue), simply iterate through the queue until we reach the rear element.
		if (front <= rear)
		{
			for (int i = front; i <= rear; i++) //Move down the queue, starting from top
			{
				cout << ar[i];
			}
		}
		else
		{
			//If the current position of the front/first element in the queue is past the rear/last element in the queue (unchronological)
			//Output the following elements until we reach the end of the array. Set the iterator to 0 afterwards then output elements until we reach the rear/last element. Simulates a circular.
			for (int i = front; i <= MAX - 1; i++)
			{
				cout << ar[i];
			}
			for (int i = 0; i <= rear; i++) //Move down the queue, starting from top
			{
				cout << ar[i];
			}
		}
	}
}
