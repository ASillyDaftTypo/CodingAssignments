#ifndef CLASSDEC_H
#define CLASSDEC_H
#include <string>
#include "queue.h"
using namespace std;

class Customer {
private:
	string Surname;
	int PhoneNumber;
public:
	Customer();
	~Customer();
	void AddSurname(string);
	void AddPhoneNumber(int);
	string GetSurname();
	int GetPhoneNumber();
};

class Event {
private:
	//Queue created using the template Queue to allow queue array of the class type
	queue<Customer> Queue;
	string Name;
	bool IsActive;
public:
	Event();
	~Event();
	//Functions to allow interogation & manipulation of data in the class
	bool Active();
	string GetName();
	int GetQueueLength();
	bool AddCustomer(string, int);
	bool RemoveCustomer(Customer&);
	void EmptyQueue();
	void ChangeName(string);
	int NameSearch(string);
};

Customer::Customer() {
	Surname = "";
	PhoneNumber = 0;
}

Customer::~Customer(){}

void Customer::AddSurname(string Name) {
	Surname = Name;
}
void Customer::AddPhoneNumber(int Number) {
	PhoneNumber = Number;
}
string Customer::GetSurname() {
	return Surname;
}
int Customer::GetPhoneNumber() {
	return PhoneNumber;
}

Event::Event(){
	IsActive = true;
}

Event::~Event(){}

bool Event::Active() {
	return IsActive;
}
string Event::GetName() {
	return Name;
}
int Event::GetQueueLength() {
	//Interogates the queue class for the current length of the queue
	return Queue.GetQueueLength();
}
bool Event::AddCustomer(string Surname, int PhoneNumber) {
	//Creates a temporary customer class
	Customer Person;
	//Assigns elements to the temporary class, from function input
	Person.AddSurname(Surname);
	Person.AddPhoneNumber(PhoneNumber);
	//Attempts to add the customer class to the array
	if (Queue.Add(Person)) return true;
	else return false;
}

bool Event::RemoveCustomer(Customer &Person) {
	//Removes the first customer on the list and returns the information to calling function
	if (Queue.Remove(Person)) return true;
	else return false;
}

void Event::EmptyQueue() {
	//Cycles through the queue & clears it
	while (!Queue.Empty()) {
		Customer Person;
		Queue.Remove(Person);
	}
}
void Event::ChangeName(string NewName) {
	Name = NewName;
}

int Event::NameSearch(string SearchName) {
	//Create temporary array for the queue items
	Customer List[10];
	//Import the queue into the temporary list
	Queue.SearchContents(List);
	//Cycle through the array of classes to find a member function that matches the user input
	for (int i = 0; i < Queue.GetQueueLength(); i++) {
		//If match is found, value returned, expressed in terms of the index+1 (as counter starts at 0)
		if (List[i].GetSurname() == SearchName) return i+1;
	}
	return 0;
}

#endif