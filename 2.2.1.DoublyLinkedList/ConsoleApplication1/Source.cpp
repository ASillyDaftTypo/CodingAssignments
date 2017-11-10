#include <iostream>
#include "listtemplate.h"

using namespace std;

void NumberInput(int& Input);

int main() {
	//Declare list object
	list<int> List;

	int Input = 1;
	//Prompt user for number & get their input
	cout << "Enter sequence of integers, 0 to finish" << endl;
	NumberInput(Input);
	//Obtain numbers while usre does not input 0
	while (Input != 0)
	{
		//Insert the valid integer into the list
		List.Insert(Input);
		//Get next number
		NumberInput(Input);
	}

	//Print list forwards, starting from the head
	cout << "Int list (forward): " << List << endl;
	//Print list backwards, starting from the tail
	cout << "Int list (backward): " << List.printreverse() << endl;

	// Now start deleting
	while (!List.Empty())
	{
		cout << "Enter number to delete from list" << endl;
		NumberInput(Input);

		// Delete chosen integer;

		if (List.Delete(Input)) cout << "Deletion of : '" << Input << "' successful!" << endl;
		else cout << "Value: '" << Input << "' not found in list!" << endl;

		// Display list to check that deletion worked

		cout << "List: " << List << endl;
		if (List.Empty()) cout << "List is empty! Closing...";
	} 
	return 0;
}


void NumberInput(int& Input) {
	//Function validates input of expected type integer
	string InputString = "";
	bool ValidInteger = false;
	bool ValidSign = false;
	//Loop through until valid integer
	while (!ValidInteger) {
		ValidInteger = true;
		ValidSign = true;
		//Prompt user for input
		getline(cin, InputString);
		int Length = InputString.length();
		//Check if sign used for first char
		if (InputString[0] != '-' && InputString[0] != '+') ValidSign = false;
		//Check first character is either number, sign or other
		if ((!isdigit(InputString[0]) && !ValidSign)) ValidInteger = false;
		if (Length > 1) {
			//If longer than one character, check each character left as a number
			for (int i = 1; i < Length; i++) {
				if (!isdigit(InputString[i])) ValidInteger = false;
			}
		}
		//If data not present, or not of type integer, user prompted to try again.
		if (!ValidInteger || Length < 1) cout << "Invalid input! Please try again.\n";
		//If correct format, convert string data type to integer
		else Input = stoi(InputString);
	}
}