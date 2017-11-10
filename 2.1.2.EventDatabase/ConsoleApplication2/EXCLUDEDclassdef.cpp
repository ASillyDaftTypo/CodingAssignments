#include <string>
#include "classdec.h"
#include "queue.h"
using namespace std;

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



Event::Event()
{
	IsActive = false;
}

Event::~Event()
{
	//delete Queue;
}

bool Event::Active() {
	return IsActive;
}
string Event::GetName() {
	return Name;
}
int Event::GetQueueLength() {
	return QueueLength;
}
bool Event::AddCustomer(string Surname, int PhoneNumber) {
	Customer Person;
	Person.AddSurname(Surname);
	Person.AddPhoneNumber(PhoneNumber);
	if (Queue.Add(Person)) return true;
	else return false;
}





