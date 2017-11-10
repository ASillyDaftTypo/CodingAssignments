#include <iostream>
#include <string>
using namespace std;

//Function declarations
void GetInput(string& InputNumberString, int& Length);
int AddToArray(int Array[100], string InputNumberString, int StartPos, int& Length, bool& IsNegative);
int ExtractNumberFromArray(int Array[100], int StartPos, int Length);

int main()
{
	//Declaration & intialisation of global variables
	int NumberSet[100];
	int FirstNumber = 0, SecondNumber = 0, FirstLength = 0, SecondLength = 0;
	string InputNumberString = "";
	bool FirstIsNegative = false, SecondIsNegative = false;

	//Prompt user for integer input. Validation performed & submitted to the array
	cout << "Please enter an integer number less than 50 characters in length:";
	GetInput(InputNumberString, FirstLength);
	AddToArray(NumberSet, InputNumberString, 0, FirstLength, FirstIsNegative);

	//Repeat the process for the second integer.
	cout << "\nPlease enter a second integer number less than 50 characters in length to be subtracted from the first:";
	GetInput(InputNumberString, SecondLength);
	AddToArray(NumberSet, InputNumberString, FirstLength + 1, SecondLength, SecondIsNegative);

	//Pull both number from the array for processing
	FirstNumber = ExtractNumberFromArray(NumberSet, 0, FirstLength);
	SecondNumber = ExtractNumberFromArray(NumberSet, FirstLength + 1, SecondLength);
	
	//Re-sign integers if input as negative
	if (FirstIsNegative) FirstNumber = -FirstNumber;
	if (SecondIsNegative) SecondNumber = -SecondNumber;

	//The actual calculation with result returned to user
	cout << "\n\nThe result is: " << FirstNumber - SecondNumber << endl;
	return 0;
}

void GetInput(string& InputNumberString, int& Length)
{
	//Validation flag declared and initialised
	bool Valid = true;

	//Input from user processed to determine if it is of integer type only
	getline(cin,InputNumberString);
	Length = InputNumberString.length();
	for (int i =0; i < Length; i++){
		if (!isdigit(InputNumberString[i]) && InputNumberString[i] != '-' && InputNumberString[i] != '+')  Valid = false;
	}

	//If data was actually input, and is of integer type only, and is less than 50 characters in length, validation passes, otherwise, repeat
	while (!Valid || !(Length > 1 && Length < 50)) {
		cout << "\nPlease enter a valid integer number!:";
		Valid = true;
		getline(cin, InputNumberString);
		Length = InputNumberString.length();
		for (int i = 0; i < Length; i++) {
			if (!isdigit(InputNumberString[i]) && InputNumberString[i] != '-' && InputNumberString[i] != '+')  Valid = false;
		}
	}
}

int AddToArray(int Array[100], string InputNumberString, int StartPos, int& Length, bool& IsNegative)
{
	//Index for input string declared & intialised
	int InputStartPos = 0;
	//If string containing the integers is negative, discard the first character, set IsNegative flag to true, increment the start position by one, and decrease the overall length by one to compensate
	if (InputNumberString[0] == '-'  || InputNumberString[0] == '+') {
		if (InputNumberString[0] == '-') IsNegative = true;
		Length--;
		InputStartPos++;
	}
	//Cycle through each character in the string & adds to an array element
	for (int i = 0; i < Length; i++){
		Array[StartPos+i] = InputNumberString[InputStartPos+i];
	}
	return 0;
}

int ExtractNumberFromArray(int Array[100], int StartPos, int Length){
	//Temporary string for storage declared and intialised as blank
	string temp = "";
	//Cycle through the array, using index for start location of integer in the array & length used for end point
	for (int i = StartPos; i < StartPos + Length; i++){
		//Append used to allow a simple method to recreate the integer format
		temp.append(1,Array[i]);
	}
	//Resultant string is converted to an integer and returned
	return stoi(temp);
}