#ifndef SORTLIST_H
#define SORTLIST_H
#include <iostream>
using namespace std;

template <class Type>
class sortlist
{
private:
	Type *Element;
	int ArraySize;
	void Swap(Type& A, Type& B);
	void Split(const int First, const int Last, int& Pos);
	void Quicksort(const int First, const int Last);
public:
	sortlist(int arraysize = 10) : ArraySize(arraysize),
		Element(new Type[arraysize]) {}
	~sortlist();
	void SetArray(Type sortarray[]);
	void GetArray(Type sortarray[]);
	void Quicksort();
};
#endif
