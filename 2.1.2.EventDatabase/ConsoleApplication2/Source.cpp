#include <iostream>
#include <string>
#include "queuetemplate.h"
#include "classdec.h"
#include <fstream>

using namespace std;
//CSV database holding base entries
const string DatabaseLocation = "EventDatabase.csv";
//Function declarations
bool ImportDatabase(Event EventList[]);
void NumberInput(int& Input);
void DisplayEventList(Event EventList[]);
void AddToTicketQueue(Event EventList[], const int EventNumber);
void RemoveFromTicketQueue(Event EventList[], const int EventNumber);
void SearchTicketQueue(Event EventList[], const int EventNumber);
void ReplaceEvent(Event EventList[], const int EventNumber);

int main() {
	//Variables used for tracking user input & current selection, as well as the storage container
	int Input = 1;
	int EventNumber = 0;
	Event EventList[10];
	//Data loaded from CSV file to populate queues
	if (ImportDatabase(EventList)) cout << "Database import successful!\n\n";
	else cout << "Database import failed!\n\n";
	//Begin the first menu - input 0 to exit
	while (Input != 0) {
		//Renders table of queues
		DisplayEventList(EventList);
		//User prompted for queue selection
		cout << "\nPlease select an event: ";
		NumberInput(Input);
		//Queue selection remembered, for use throughout the selection pathway
		EventNumber = Input - 1;
		cout << "Event: '" << EventList[EventNumber].GetName() << "' selected!\n";
		
		//Begin submenu for specific queue
		while (Input != 0 && Input != 9) {
			//Options displayed to the user
			cout << "\nOptions available:\n1 : Add person to the ticket queue\n2 : Display & remove first person in ticket queue\n3 : Search for person by 'Surname'\n8 : Reset event\n9 : Go back\n0 : Exit\n";
			NumberInput(Input);
			//Allows for continuous use of the submenu, until exited
			switch (Input)
			{
				//Add customer to back of queue
				case 1: AddToTicketQueue(EventList, EventNumber); break;
				//Remove customer from front of queue
				case 2: RemoveFromTicketQueue(EventList, EventNumber); break;
				//Intiate search of queue for specific surname
				case 3: SearchTicketQueue(EventList, EventNumber); break;
				//Rename the event & clear the queue
				case 8: ReplaceEvent(EventList, EventNumber); break;
				//Returns to previous menu
				case 9: break;
				//Exits the application
				case 0: break;
				default: cout << "\nNo selection found!\n";
			}
		}
	}
}

bool ImportDatabase(Event EventList[]) {
	//Declare & define temp variables for tracking
	string tempname = "";
	string tempnumber = "";
	int Counter = 0;

	//Load data file
	ifstream EventDatabase;
	EventDatabase.open(DatabaseLocation);

	if (EventDatabase.is_open()){
		while (!EventDatabase.eof()) {
			//Pull first instance in the line of data until comma, insert into event name
			getline(EventDatabase, tempname, ',');
			tempname.erase(find(tempname.begin(), tempname.end(), '\n'));
			EventList[Counter].ChangeName(tempname);
			//For each item after the first, customer data of form "name,number," drawn from the stream
			//and imported. When end of line reached, end loop to start populating next event.
			while (EventDatabase.peek() != '\n' && !EventDatabase.eof()) {

				getline(EventDatabase, tempname,',');
				getline(EventDatabase, tempnumber,',');
				EventList[Counter].AddCustomer(tempname, stoi(tempnumber));				
			}
			Counter++;
		}
		//Close file connection & return with confirmation of data load
		EventDatabase.close();
		return true;
	}
	else return false;
}


void NumberInput(int& Input) {
	//Function validates input of expected type integer
	string InputString;
	bool Valid = false;
	while (!Valid) {
		Valid = true;
		getline(cin, InputString);
		int Length = InputString.length();
		for (int i = 0; i < Length; i++) {
			if (!isdigit(InputString[i])) Valid = false;
		}
		//If data not present, or not of type integer, user prompted to try again.
		if (!Valid  || Length < 1) cout << "Invalid input! Please try again.\n";
		//If correct format, convert string data type to integer
		else Input = stoi(InputString);
	}
}

void DisplayEventList(Event EventList[]) {
	//Generates basic table of the events and numbers in the event queue
	cout << "Number in Queue\t|\tEvent Name\n---------------------------------------------\n";
	//Cycles through each event and outputs those that are active
	for (int i = 0; i < 10; i++) {
		if (EventList[i].Active()) {
			cout << "\t" << EventList[i].GetQueueLength() << "\t|\t" << EventList[i].GetName() << "\n";
		}
	}
}

void AddToTicketQueue(Event EventList[], const int EventNumber) {
	//Declare & intialise variables for input by user
	string Surname = "";
	char Confirm = 'N';
	int PhoneNumber = 0;
	//Repeat input stage if user does not confirm details are correct
	while (Confirm != 'Y' && Confirm != 'y') {
		cout << "Please enter the following details of the new person:\nSurname:";
		getline(cin, Surname);
		cout << "\nPhone number:";
		NumberInput(PhoneNumber);
		cout << "\nYou have entered:\nSurname: " << Surname << "\nPhone Number: " << PhoneNumber << "\nIs this correct? (Y/N): ";
		cin >> Confirm;
		cin.ignore(1000, '\n');
	}
	//Add customer information to queue item
	if (EventList[EventNumber].AddCustomer(Surname, PhoneNumber)) {
		cout << "\nNew person added!";
	}
	//If list full, inform the user
	else cout << "Waiting list for this event is full!";
}

void RemoveFromTicketQueue(Event EventList[], const int EventNumber) {
	//Create temp class to store returned values
	Customer Person;
	//Check if queue is empty
	if (!EventList[EventNumber].RemoveCustomer(Person)) cout << "Error: The Queue is empty!";
	//If not empty, display surname & number from the operation above
	else cout << "\nThe next person in the queue is:\nSurname: " << Person.GetSurname() << "\nPhone Number: " << Person.GetPhoneNumber();
}

void SearchTicketQueue(Event EventList[], const int EventNumber) {
	//Declare & intialised search term & queue placement
	string SearchName = "";
	int Result = 0;
	//Prompt user for the surname of the customer
	cout << "Please enter a Surname to be searched: ";
	getline(cin, SearchName);
	//Value returned in terms of queue order; if 0, user not found in queue
	Result = EventList[EventNumber].NameSearch(SearchName);
	if (Result == 0) cout << "Customer name not found!";
	else cout << "Customer is #" << Result << " in the queue!";
}
void ReplaceEvent(Event EventList[], const int EventNumber) {
	
	string NewName = "";
	//Event queue cleared
	EventList[EventNumber].EmptyQueue();
	//User prompted for a new name to the event
	cout << "Old name: " << EventList[EventNumber].GetName() << ".\nPlease enter a new name for the event: ";
	getline(cin, NewName);
	EventList[EventNumber].ChangeName(NewName);
	cout << "\nEvent name updated!";
}