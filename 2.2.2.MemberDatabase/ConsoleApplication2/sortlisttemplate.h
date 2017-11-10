#ifndef SORTLISTTEMPLATE_H
#define SORTLISTTEMPLATE_H
#include "sortlist.h"
#include "member.h"
#include <string>

template <class Type>
sortlist<Type>::~sortlist()
{
	delete[] Element;
}

template <class Type>
void sortlist<Type>::SetArray(Type sortarray[])
{

	for (int index = 0; index < ArraySize; index++)

		Element[index] = sortarray[index];

}

template <class Type>
void sortlist<Type>::GetArray(Type sortarray[])
{

	for (int index = 0; index < ArraySize; index++)

		sortarray[index] = Element[index];
}

template <class Type>
void sortlist<Type>::Swap(Type& A, Type& B)
{
	Type Temp = A;
	A = B;
	B = Temp;
}

template <class Type>
void sortlist<Type>::Split(const int First, const int Last, int& Pos)
{
	int Left, Right;  // Markers for searching from left and right
	Type Pivot;  // Pivot element

	Pivot = Element[First];
	Left = First;
	Right = Last;
	while (Left < Right)   // While markers have not met
	{
		// Search from the right for element <= Pivot

		//Added obtain compare ID to Right member & Pivot member
		while (Element[Right].GetCompareID() > Pivot.GetCompareID())
			Right = Right - 1;

		// Search from the left for element > Pivot

		//Added obtain compare ID to Left member & Pivot member
		while ((Left < Right) && (Element[Left].GetCompareID() <= Pivot.GetCompareID()))
			Left = Left + 1;

		// If markers have not met, interchange elements

		if (Left < Right)
			Swap(Element[Left], Element[Right]);
	};

	// Searches complete; now place pivot in correct place

	Pos = Right;
	Element[First] = Element[Pos];
	Element[Pos] = Pivot;
}

template <class Type>
void sortlist<Type>::Quicksort(const int First, const int Last)
// Sorts portion of array X between X[First] and X[Last]
{
	int Pos;     // Final position of pivot

	if (First < Last)           // List has at least two elements
	{
		Split(First, Last, Pos);      // Split into two sublists
		Quicksort(First, Pos - 1);   // Sort left sublist
		Quicksort(Pos + 1, Last);     // Sort right sublist
	}
	// else list has 0 or 1 elements and needs no sorting
}

template <class Type>
void sortlist<Type>::Quicksort()
{
	Quicksort(0, ArraySize - 1);
}
#endif
