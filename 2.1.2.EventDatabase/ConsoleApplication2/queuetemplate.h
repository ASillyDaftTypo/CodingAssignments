#ifndef QUEUETEMPLATE_H
#define QUEUETEMPLATE_H
#include "queue.h"


// Constructor

template <class Type>
queue<Type> ::queue(int queuesize) :
	QueueSize(queuesize),
	Contents(new Type[queuesize + 1]),
	Front(0), Back(0)
{}

// Destructor

template <class Type>
queue<Type> :: ~queue()
{
	delete[] Contents;
}

// Tests

template <class Type>
bool queue<Type> ::Empty() const
{
	return (Front == Back) ? true : false;
}

template <class Type>
bool queue<Type> ::Full() const
{
	return ((1 + Back) % (QueueSize + 1) == Front) ? true : false;
}

// Remove and Add

template <class Type>
bool queue<Type> ::Remove(Type& FrontElement)
{
	if (Empty())
		return false;
	else
	{
		FrontElement = Contents[Front];
		Front = (Front + 1) % (QueueSize + 1);
		return true;
	}
}

template <class Type>
bool queue<Type> ::Add(const Type& NewElement)
{
	if (Full())
		return false;
	else
	{
		Contents[Back] = NewElement;
		Back = (Back + 1) % (QueueSize + 1);
		return true;
	}
}

template <class Type>
int queue<Type>::GetQueueLength() {
	int QueueLength = 0;
	//Determine the length of the queue by comparison of the Front & Back pointers
	if (Front > Back) QueueLength = (QueueSize - (Front - Back));
	else QueueLength = (Back - Front);

	return QueueLength;
}

template <class Type>
void queue<Type>::SearchContents(Type SearchContents[]) {
	//Create temporary pointer for the function to act as an active pointer
	int TempFront = Front;
	int Counter = 0;
	//Using same algorithm as remove, export the queue items, in order, to another
	//array of the class type. Allows for interogation of the class method inside the
	//member class itself.
	while (TempFront != Back) {
		SearchContents[Counter] = Contents[Front];
		TempFront = (TempFront + 1) % (QueueSize + 1);
		Counter++;
	}

	
}

#endif
