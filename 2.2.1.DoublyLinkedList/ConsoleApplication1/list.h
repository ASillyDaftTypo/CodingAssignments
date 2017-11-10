#ifndef LIST
#define LIST
#include <iostream>
using namespace std;

// Template list with moderate functionality

template <class Type> class list
{
protected:
	class Node
	{
	public:
		Type Element;
		//Added previous to allow second link
		Node *Previous;
		Node *Next;

		Node() : Next(nullptr) {}
		//Added previous node to initialisation list - renamed variables to be suitable
		Node(Type Data, Node *PNode = nullptr, Node *NNode = nullptr) :
			Element(Data), Previous(PNode), Next(NNode) {}
	};

	Node *Head;
	Node *Tail;
public:
	list();
	virtual ~list();
	list(const list& Orig);
	list<Type>& operator=(const list& Orig);
	bool operator==(const list& Orig);
	virtual bool Empty() const;
	virtual bool Insert(const Type& NewElement);
	virtual bool Delete(const Type& DelElement);
	void print(ostream& OutStream) const;
	//Added function to return reverse of list
	string printreverse();

};
template <class Type> ostream& operator<< (ostream& OutStream,
	const list<Type>& OutList);
#endif
