#ifndef LISTTEMPLATE_H
#define LISTTEMPLATE_H
#include "list.h"
//Added string include for reverse output function
#include <string>

// Constructor
template <class Type>
list <Type> ::list() : Head(nullptr)
{
}

// Destructor

template <class Type>
list <Type> :: ~list()
{
	Node *Temp;
	while (Head != nullptr)
	{
		Temp = Head;
		Head = Head->Next;
		delete Temp;
	}
}

// Copy constructor

template <class Type>
list <Type> ::list(const list& Orig)
{
	Node *Marker;
	Node *OrigMarker;


	OrigMarker = Orig.Head;
	if (OrigMarker == nullptr)
		Head = nullptr;
	else
	{
		Head = new Node(OrigMarker->Element, nullptr);
		Marker = Head;
		OrigMarker = OrigMarker->Next;
		while (OrigMarker != nullptr)
		{
			Marker->Next =
				new Node(OrigMarker->Element, nullptr);
			OrigMarker = OrigMarker->Next;
			Marker = Marker->Next;
		}
	}
}

// Assignment operator

template <class Type>
list<Type>& list<Type> :: operator=(const list& Orig)
{
	Node *Marker;
	Node *OrigMarker;

	// Check that we are not assigning
	// a variable to itself
	if (this != &Orig)
	{
		// First clear current list if any
		while (Head != nullptr)
		{
			Marker = Head;
			Head = Head->Next;
			delete Marker;
		}

		// Now build new copy

		OrigMarker = Orig.Head;
		if (OrigMarker == nullptr)
			Head = nullptr;
		else
		{
			Head = new Node(OrigMarker->Element, nullptr);
			Marker = Head;
			OrigMarker = OrigMarker->Next;
			while (OrigMarker != nullptr)
			{
				Marker->Next =
					new Node(OrigMarker->Element, nullptr);
				OrigMarker = OrigMarker->Next;
				Marker = Marker->Next;
			}
		}
	}
	return (*this);
}

// Tests

template <class Type>
bool list<Type> :: operator==(const list& Orig)
{
	Node *Marker, *OrigMarker;
	Marker = Head;
	OrigMarker = Orig.Head;
	while ((Marker != nullptr) && (OrigMarker != nullptr))
	{
		if (Marker->Element != OrigMarker->Element)
			return false;
		Marker = Marker->Next;
		OrigMarker = OrigMarker->Next;
	}
	if ((Marker != nullptr) || (OrigMarker != nullptr))
		return false;
	else
		return true;
}

// Empty

template <class Type>
bool list <Type> ::Empty() const
{
	return (Head == nullptr) ? true : false;
}

// Delete

template <class Type>
bool list <Type> ::Delete(const Type& DelElement)
{
	Node *Temp;
	//Added next node
	Node *Next;
	Node *Previous;
	if (Empty())
		return false;
	else if (Head->Element == DelElement)
	{
		Temp = Head;
		Head = Head->Next;
		//If list not empty, update head of next item to nullptr
		if (!Empty()) {
			Head->Previous = nullptr;
		}
		delete Temp;
		return true;
	}
	else if (Head->Next == nullptr)
		return false;
	else
	{
		Previous = Head;
		Temp = Head->Next;
		while ((Temp->Element != DelElement) &&
			(Temp->Next != nullptr))
		{
			Previous = Temp;
			Temp = Temp->Next;
		}
		if (Temp->Element == DelElement)
		{
			//Update tail of previous node to point at current nodes tail pointer location
			Previous->Next = Temp->Next;
			//If not at end of list, update head of next node to point at previous node
			if (Temp->Next != nullptr) {
				Next = Temp->Next;
				Next->Previous = Previous;
			}
			delete Temp;
			return true;
		}
		else  // list exhausted
			return false;
	}
}

// Insert (simple insert at beginning)

template <class Type>
bool list <Type> ::Insert(const Type& NewElement)
{
	//Check if list is currently empty
	if (Empty())  {
		//If list empty, create first node - both values nullptr
		Node *NewNode = new Node(NewElement, Head, Tail);
		//Set head as starting point of list
		Head = NewNode;
		//Update tail to point at new node
		Tail = NewNode;
	}
	//Else, find location for new value
	else {
		Node *Current = Head;

		if (Current->Element > NewElement) {

			Node *NewNode = new Node(NewElement, nullptr, Current);
			Current->Previous = NewNode;
			Head = NewNode;
		}
		else {
			bool LocationFound = false;
			while (LocationFound != true) {
				if (Current != nullptr) {
					if (Current->Element < NewElement) {
						Current = Current->Next;
					}
					else LocationFound = true;
				}
				else LocationFound = true;
			}
			//New node point to previous tail as its head, its tail is nullptr
			if (Current == nullptr) {
				Node *NewNode = new Node(NewElement, Tail, nullptr);
				//Assign previous nodes tail to point to new node
				Tail->Next = NewNode;
				//Update tail to point at new node
				Tail = NewNode;
			}
			else {
				Node *NewNode = new Node(NewElement, Current->Previous, Current);
				//Assign previous nodes tail to point to new node
				Node *TempNode = Current->Previous;
				TempNode->Next = NewNode;
				//Assign current node head to point at new node
				Current->Previous = NewNode;
			}
		}
	}

	return true;
}

template <class Type>
void list <Type> ::print(ostream& OutStream) const
{
	Node *Temp;
	Temp = Head;
	while (Temp)
	{
		OutStream << Temp->Element << " ";
		Temp = Temp->Next;
	}
}

template <class Type>
ostream& operator<<(ostream& OutStream,
	const list<Type>& OutList)
{
	OutList.print(OutStream);
	return OutStream;
}

//Unable to overload << operator twice for same class - resorting to string compilation & return to main program
template <class Type>
string list <Type> ::printreverse()
{
	Node *Temp;
	//Iterator now starts at the tail
	Temp = Tail;
	string tempstring = "";
	while (Temp)
	{
		//Same procedure - cycles through, however converts value to string and appends to temp string
		tempstring.append(to_string(Temp->Element) + " ");
		Temp = Temp->Previous;
	}
	//Returns the created temp string to main program
	return tempstring;
}
#endif
