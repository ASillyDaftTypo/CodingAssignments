/*Software Development AC51002 (16/17)
Assignment 3
Distinct Character & Word Counter
John McGouran

This application examines a user specified file for the frequency of distinct characters supported in the ASCII table.
A table of the results is then displayed for the user within the console window, showing the frequency, along with them
being sorted in numeric order, in accordance to their ASCII decimal number.

The main assumptions in this application are as follows:

1) The file input is readable in plain text (e.g. .txt format).
2) The file contents are all supported by the ASCII table.
3) For the word count to be accurate, the file input will contain at least one word and are separated by the space character.


Logic flowchart of application process:


_________________	___________	SUCCESS	 _____________	Calls Examine_Characters _________________	NO	 _____________________		______________________	YES _________________
| User prompted |-->|File open|--------->|Reads first|-------------------------->|Does character |------>|Assign object to	 |----->|Character is space	 |----->|Increment word |
| for input     |	|attempted|			 |character	 |		   /|\				 |have an object?|		 |character - counter|		|and previous		 |		|count			|
|_______________|	|_________|			 |___________|			|				 |_______________|		 |in this object 	 |		|character not space?|		|_______________|
						|								________|____					|				 |changes to 1		 |		|____________________|			|
						|FAIL							|Read next	|					|YES			 |___________________|		   /|\			|				|
				_______\|/___________					|character	|			_______\|/_________										|			|NO				|
				|Error message		|					|___________|			|Increment objects|-------------------------------------|		___\|/_______		|
				|displayed			|						   /|\				|counter		  |												|End of file|<------|	
				|				    |							|				|_________________|											NO	|reached?	|	
				|___________________|							|-------------------------------------------------------------------------------|___________|
						|																																|						
						|																																|YES			
				_______\|/____			_____________											_______________________								___\|/___			
				|Application |			|Report		|								YES			|Are objects in order?|	Calls Order_Characters		|Close	|			
				|closes		 |<---------|generated	|<------------------------------------------|	Default: No		  |<----------------------------|file	|			
				|____________|			|___________|										  /||_____________________|								|_______|
																					NO		 /						|																						
																			 (In order:Yes) /						|NO																		
																					_______|______				___\|/________					
																					|Errors found|		YES		|Select first|												
																					|during loop?|------------->|object		 |
																					|____________|				|____________|
																				   /|\			_____________				|
																				YES	|			|			|				|
																			________|______	NO	|Next object|		_______\|/________
																			|End of object|---->|___________|------>|Is object larger|
																			|array list?  |						NO	|than next?		 |		
																			|_____________|<------------------------|________________|
																				   /|\				_____________			|
																					|				|Swap values|			|YES			
																					|---------------|with next	|<----------|
																									|___________|

*/


//Standard libraries included for user input, strings & file stream access.
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//Class declaration for holding each character.
class Character {
private:
	//Variables hold the type of character and the number of them found during the process.
	int total;
	char type;
public:
	Character();
	void incrementTotal();
	void setType(char);
	void swapOrder(int, Character Tracker[]);
	char getType();
	int getTotal();
};
//Function declarations - definitions found below main().
void Examine_Character(char inputCharacter, char previousCharacter, int &wordCount, int &numberOfType, Character Tracker[]);
void Order_Characters(int numberOfType, Character Tracker[]);
void Report(int numberOfType, int wordCount, Character Tracker[]);

int main() {
	//Global variables declared & defined with default values.
	string filePath = "";
	char inputCharacter = ' ';
	int numberOfType = 0;
	int wordCount = 1;
	char previousCharacter = '_';
	ifstream inputFile;
	//Initialising an array of objects - quantity will support up to all characters in the ASCII table. (Not dynamic :( )
	Character Tracker[256];

	//Prompts the user to input the filepath for the input file.
	cout << "\nPlease enter the full filepath for the file to be examined\n(e.g. C:\\Users\\Admin\\my_file.txt): \n\n";
	cin >> filePath;

	//Attempts to open the file and begin the operation if successful.
	inputFile.open(filePath);
	if (inputFile.is_open()) {
		cout << "\nInput file opened!\n";
		//Extracts the first character from the file.
		inputCharacter = inputFile.get();
		cout << "\nPerforming extraction from input file...\n";
		while (!inputFile.eof()) {
			//Pipes variables to external function - last three are returned by reference (Tracker array implicitly).
			Examine_Character(inputCharacter, previousCharacter, wordCount, numberOfType, Tracker);
			//Holds the character for the next loop to compare against.
			previousCharacter = inputCharacter;
			//Extracts next character for next loop.
			inputCharacter = inputFile.get();

		}
		//Closes file once extraction is complete
		inputFile.close();
		cout << "\nInput file closed!\n";
		//Pipes variables to function to sort the object values by their ASCII decimal value.
		cout << "\nOrdering results...\n";
		Order_Characters(numberOfType, Tracker);
		//Calls function to generated a table of the results.
		cout << "\nGenerating report...\n";
		Report(numberOfType, wordCount, Tracker);

	}
	//If file not found, display an error message to the user.
	else { cout << "\nFile not found!\n"; }
	cout << "\nDone!\n";
	return 0;
}
//Function examines a character and either assigns it to an unassigned object, or increments the count of an object if one already has the same character stored.
//Also discerns if the character indicates that a new word has been reached.
void Examine_Character(char inputCharacter, char previousCharacter, int &wordCount, int &numberOfType, Character Tracker[]) {
	//Tracks if character has been assigned an object yet.
	bool characterMatched = false;
	//Initiate loop for the total number of objects currently in-use.
	for (int i = 0; i <= numberOfType; i++) {
		//If object exists for the current character, increment the total.
		if (inputCharacter == Tracker[i].getType()) {
			Tracker[i].incrementTotal();
			characterMatched = true;
		}
	}
	//If no match was found, assign the next object in the array to the character and notify the application that another is in-use by incrementing the counter.
	if (characterMatched == false) {
		numberOfType++;
		Tracker[numberOfType].setType(inputCharacter);
		Tracker[numberOfType].incrementTotal();
	}
	//If character is a space, and the previous character is also not a space, assume next will begin a new word.
	if (inputCharacter == ' ' && previousCharacter != ' ') { wordCount++; }

}
//Function examines the character stored in an object and if it has a higher ASCII value than the next, it calls a class member to
//swap their values, placing them in ascending order. This repeats in a loop until no swaps are made.
void Order_Characters(int numberOfType, Character Tracker[]) {
	//Ensure that there are enough distinct characters found to perform a sort.
	if (numberOfType > 2){
		//Sets end-condition for the bubble sort.
		bool ordered = false;
		//Repeats until end-condition met.
		while (ordered == false) {
			//Counter to track if all objects are in correct order.
			int badAttempts = 0;
			for (int i = 0; i < numberOfType; i++) {
				//If the next character is lower in the ASCII table than current, calls class member function to swap their values.
				if (Tracker[i].getType() > Tracker[i + 1].getType()) {
					badAttempts++;
					Tracker[i].swapOrder(i + 1, Tracker);
				}
			}
			//If loop has succeeded with no swaps performed, objects can be assumed to be in order.
			if (badAttempts == 0) {	ordered = true;	}
		}
	}
}
//Function creates a table inside the console window for the user with the statistics of the characters found. Also displays a total word count.
void Report(int numberOfType, int wordCount, Character Tracker[]) {
	//Header format for the report.
	cout << "\n\n---------------------------------\n|Character\t|# of Character |\n---------------------------------\n";
	//Loop for each object in use and displays the result on screen.
	for (int i = 0; i <= numberOfType; i++) {
		cout << "|\t" << Tracker[i].getType() << "\t|\t" << Tracker[i].getTotal() << "\t|\n";
	}
	//Footer for the report table including the word count.
	cout << "---------------------------------\n|Word Count\t:\t" << wordCount << "\t|\n---------------------------------";

}
//Constructor for the character class - sets a default value for both variables used.
Character::Character() {
	total = 0;
	type = ' ';
}
//Allows the total amount counted for a character to be incremented.
void Character::incrementTotal() {
	total++;
}
//Allows object to have a character assigned to it.
void Character::setType(char a) {
	type = a;
}
//Used by sort function - swaps the values of variables between two objects of this class.
void Character::swapOrder(int i, Character Tracker[]) {
	swap(total, Tracker[i].total);
	swap(type, Tracker[i].type);
}
//Returns the character stored in the object.
char Character::getType() {
	return type;
}
//Returns the count of the character type stored in the object.
int Character::getTotal() {
	return total;
}