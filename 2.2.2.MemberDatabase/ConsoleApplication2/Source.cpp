#include <iostream>
#include <string>
#include <fstream>
#include "member.h"
#include "sortlisttemplate.h"

using namespace std;

//CSV database holding base entries
const string DatabaseLocation = "MemberDatabase.csv";
//Fuction declarations
void NumberInput(int& Input, int OperationMode);
void NewMember(Member* sortarray, int& NumberOfMembers, int size);
void ViewLegacyMembers(Member* sortarray, int size);
void DisableMember(Member* sortarray, int size);
bool ValidName(string Name);
bool ValidDate(string Date);
void DisplayMember(Member* sortarray, int Location);
void CreateDateSearchBrackets(string CurrentDate, int AccountAge, string& LowerBracketDateSearchReference, string& UpperBracketDateSearchReference);
bool ImportDatabase(Member* sortarray, int& NumberOfMembers);

int main() {

	//Declare & initialise global variables
	int size = 10;
	int Input = -1;
	int NumberOfMembers = 0;

	//Declare array objects
	Member *sortarray;
	sortarray = new Member[size];
	sortlist<Member> testlist(size);

	//Attempt to import database
	if (ImportDatabase(sortarray,NumberOfMembers)) cout << "Database import successful!\n\n";

	//Perform a sort after database import
	testlist.SetArray(sortarray);
	testlist.Quicksort();
	testlist.GetArray(sortarray);

	cout << "Welcome to the societies membership tracking application.";
	while (Input != 0) {
		cout << "\n\nPlease select from the following options:\n\n1) Enroll a new member.\n2) View a list of legacy members.\n3) Disable a membership.\n0) Exit\n\nOption number:";
		NumberInput(Input, 0);


		switch (Input) {

		case 1: NewMember(sortarray, NumberOfMembers, size);
			break;
		case 2: ViewLegacyMembers(sortarray, size);
			break;
		case 3: DisableMember(sortarray, size);
			break;
		default: cout << "\nNo valid option selected!\n";

		}
		//Performs another sort at the end of each cycle
		testlist.SetArray(sortarray);
		testlist.Quicksort();
		testlist.GetArray(sortarray);

	}

	return 0;
}

void NumberInput(int& Input, int OperationMode) {
	//Function validates input of expected type integer
	string InputString = "";
	bool ValidInteger = false;
	//Loop through until valid integer
	while (!ValidInteger) {
		ValidInteger = true;
		//Prompt user for input
		cin.clear();
		//cin.ignore();
		getline(cin, InputString);
		int Length = InputString.length();


		//Check first character is number
		if (!isdigit(InputString[0])) ValidInteger = false;
		if (OperationMode == 0 && Length > 1) ValidInteger = false;

		if (OperationMode == 1 && Length > 1) {
			//If longer than one character, check each character left as a number
			for (int i = 1; i < Length; i++) {
				if (!isdigit(InputString[i])) ValidInteger = false;
			}
		}


		//If data not present, or not of type integer, user prompted to try again.
		if (!ValidInteger) cout << "Invalid input! Please try again: ";
		//If correct format, convert string data type to integer
		else Input = stoi(InputString);
	}
}

void NewMember(Member* sortarray, int& NumberOfMembers, int size) {

	//Declare & intialise variables to hold & convert input values
	string ForeName = "";
	string SurName = "";
	string JoinDate = "";
	bool ForeNameValid = false;
	bool SurNameValid = false;
	bool JoinDateValid = false;

	cout << "The following information is required:\n\n-Forename\n-Surname\n-Intended membership start date (DD/MM/YYYY)\n\nPlease enter the Forename: ";
	//Obtain valid forename from user(characters only)
	while (!ForeNameValid) {
		getline(cin,ForeName);
		if (ValidName(ForeName)) ForeNameValid = true;
		else cout << "\nName was invalid! Please try again: ";
	}
	cout << "\nPlease enter the Surname: ";
	//Obtain valid surname from user(characters only)
	while (!SurNameValid) {
		getline(cin, SurName);
		if (ValidName(SurName)) SurNameValid = true;
		else cout << "\nName was invalid! Please try again: ";
	}
	cout << "\nPlease enter the membership start date(DD/MM/YYYY): ";
	//Obtain valid date from the user
	while (!JoinDateValid) {
		getline(cin, JoinDate);
		if (ValidDate(JoinDate)) JoinDateValid = true;
		else cout << "\nDate was invalid! Please ensure DD/MM//YYYY format and try again: ";
	}
	//If all inputs are successfully validated, call member function to add to object
	if (ForeNameValid && SurNameValid && JoinDateValid && (NumberOfMembers < size)) {
		sortarray[NumberOfMembers].NewMember(ForeName, SurName, JoinDate, NumberOfMembers + 1);
		//Update member counter
		NumberOfMembers = NumberOfMembers + 1;
		cout << "\n\nNew member added! Member ID: " << NumberOfMembers << endl;
	}
	else cout << "\n\n Max number of members reached:" << NumberOfMembers << endl;
}

bool ValidName(string Name) {

	bool Valid = true;
	int Length = Name.length();
	//Check string was entered
	if (Length < 1) Valid = false;
	else {
		//Check no numbers were input
		for (int i = 0; i <= Length; i++) {
			if (isdigit(Name[i])) Valid = false;
		}
	}
	//Return validation check results
	return Valid;
}

bool ValidDate(string Date) {

	//Declate & intialise variables to support various format conversions
	bool Valid = true;
	string DayString = "";
	string MonthString = "";
	string YearString = "";
	int DateLength = Date.length();
	int Day = 0;
	int Month = 0;
	int Year = 0;

	//cout << "Length: " << DateLength;
	if (Date.length() != 10) Valid = false;
	else if (Date[2] != '/' && Date[5] != '/') Valid = false;
	else {
		//Get day into string
		DayString.append(Date, 0, 2);
		//Get month into string
		MonthString.append(Date, 3, 2);
		//Get year into string
		YearString.append(Date, 6, 4);
		//Check if values are integers; if so, place in int version of the variable
		if (isdigit(DayString[0]) && isdigit(DayString[1])) Day = stoi(DayString);
		else Valid = false; 
		if (isdigit(MonthString[0]) && isdigit(MonthString[1])) Month = stoi(MonthString);
		else Valid = false;
		if (isdigit(YearString[0]) && isdigit(YearString[1]) && isdigit(YearString[2]) && isdigit(YearString[3])) Year = stoi(YearString);
		else Valid = false;

		//If all are valid integers, check all valid values
		if (Day < 1 || Day > 31 || Month < 1 || Month >12 || Year < 1000 || Year > 3000) Valid = false;
		//If all are valid integers and above zero, proceed to check day is in month
		if (Valid) {
			
			//Reset check to false
			Valid = false;
			//Caveat for February
			if (Month == 2) {
				//Check leap year for 29, or 28 for standard
				if (Day <= 28 || ((Year % 4) == 0 && Day <= 29)) Valid = true;
			}
			//Algorithm uses modulus of month (normalised to 0) - results in a differential from 31, which is checked against entered day
			else if (Day <= (31 - ((Month-1) % 7) % 2)) Valid = true;
		}
	}

	return Valid;
}

void ViewLegacyMembers(Member* sortarray, int size) {

	//Declare & initialise variables for function
	bool CurrentDateValid = false;
	string CurrentDate = "";
	string CurrentDateFormatted = "";
	string LowerBracketDateSearchReference = "";
	string UpperBracketDateSearchReference = "";

	cout << "Please enter the current date: ";
	
	//Prompt user for date & ensure valid
	while (!CurrentDateValid) {
		getline(cin,CurrentDate);
		if (ValidDate(CurrentDate)) CurrentDateValid = true;
		else cout << "\nDate was invalid! Please ensure DD/MM//YYYY format and try again: ";
	}


	cout << "\nGenerating report...\n";

	cout << "Long-standing members as of " << CurrentDate << ":\n\n50 Years+\n";
	
	cout << "Membership ID\t\tDate joined\t\tName\n";
	
	//Converts the date string of format DD/MM/YYYY into integer of format YYYYMMDD for ease of sorting
	//Year
	CurrentDateFormatted.append(CurrentDate, 6, 4);
	//Month
	CurrentDateFormatted.append(CurrentDate, 3, 2);
	//Day
	CurrentDateFormatted.append(CurrentDate, 0, 2);
	//Push values to other function to calculate the year bracket e.g. 2017... 50+yr results in Upper=1967, Lower=1000; 40+yr results in Upper=1977, Lower=1967
	CreateDateSearchBrackets(CurrentDateFormatted, 50, LowerBracketDateSearchReference, UpperBracketDateSearchReference);
	//Start iterating through records for those matching brackets
	for (int i = 0; i < size; i++) {
		//If member search string is within the range, call the display member function with the record location
		if (sortarray[i].GetCompareID() >= LowerBracketDateSearchReference && sortarray[i].GetCompareID() < UpperBracketDateSearchReference) {
			if(sortarray[i].GetActiveStatus()) DisplayMember(sortarray, i);
			
		}
	}

	//Repeat the process for each year bracket
	cout << "\n\n40 Years+ \n";
	cout << "Membership ID\t\tDate joined\t\tName\n";
	CreateDateSearchBrackets(CurrentDateFormatted, 40, LowerBracketDateSearchReference, UpperBracketDateSearchReference);
	for (int i = 0; i < size; i++) {
		if (sortarray[i].GetCompareID() >= LowerBracketDateSearchReference && sortarray[i].GetCompareID() < UpperBracketDateSearchReference) {
			if (sortarray[i].GetActiveStatus()) DisplayMember(sortarray, i);
			
		}
	}
	cout << "\n\n30 Years+ \n";
	cout << "Membership ID\t\tDate joined\t\tName\n";
	CreateDateSearchBrackets(CurrentDateFormatted, 30, LowerBracketDateSearchReference, UpperBracketDateSearchReference);
	for (int i = 0; i < size; i++) {
		if (sortarray[i].GetCompareID() >= LowerBracketDateSearchReference && sortarray[i].GetCompareID() < UpperBracketDateSearchReference) {
			if (sortarray[i].GetActiveStatus()) DisplayMember(sortarray, i);
			
		}
	}
	cout << "\n\n20 Years+ \n";
	cout << "Membership ID\t\tDate joined\t\tName\n";
	CreateDateSearchBrackets(CurrentDateFormatted, 20, LowerBracketDateSearchReference, UpperBracketDateSearchReference);
	for (int i = 0; i < size; i++) {
		if (sortarray[i].GetCompareID() >= LowerBracketDateSearchReference && sortarray[i].GetCompareID() < UpperBracketDateSearchReference) {
			if (sortarray[i].GetActiveStatus()) DisplayMember(sortarray, i);
			
		}
	}
	cout << "\n\n10 Years+ \n";
	cout << "Membership ID\t\tDate joined\t\tName\n";
	CreateDateSearchBrackets(CurrentDateFormatted, 10, LowerBracketDateSearchReference, UpperBracketDateSearchReference);
	for (int i = 0; i < size; i++) {
		if (sortarray[i].GetCompareID() >= LowerBracketDateSearchReference && sortarray[i].GetCompareID() < UpperBracketDateSearchReference) {
			if (sortarray[i].GetActiveStatus()) DisplayMember(sortarray, i);
			
		}
	}
	cout << "\n\n0 Years+ \n";
	cout << "Membership ID\t\tDate joined\t\tName\n";
	CreateDateSearchBrackets(CurrentDateFormatted, 0, LowerBracketDateSearchReference, UpperBracketDateSearchReference);
	for (int i = 0; i < size; i++) {
		if (sortarray[i].GetCompareID() >= LowerBracketDateSearchReference && sortarray[i].GetCompareID() < UpperBracketDateSearchReference) {
			if (sortarray[i].GetActiveStatus()) DisplayMember(sortarray, i);
			
		}
	}
	
}

void DisableMember(Member* sortarray, int size) {

	//Declare & intialise variables to support function
	int Input = 0;
	char Confirmation = 'N';
	int Counter = 0;
	bool Found = false;
	cout << "\nPlease enter the member ID of the membership that to be set inactive: ";
	//Get valid number from the user
	NumberInput(Input, 1);
	cout << "\nSearching...\n";
	//While not at the end of records & not found, do search
	while (Counter < size && Found == false) {
		//If match found
		if (sortarray[Counter].GetMemberID() == Input) {
			cout << "\nMatch found!\n";
			cout << "Membership ID\t\tDate joined\t\tName\n";
			//Pipe to function to display member details
			DisplayMember(sortarray, Counter);
			cout << "\nIs this the member you wish to set as inactive? (Y/N): ";
			//Obtain confirmation
			cin >> Confirmation;
			if (Confirmation == 'Y' || Confirmation == 'y') {
				//If user confirms, acknowledge and set the member as inactive; found set to false to end loop on next iteration
				Found = true;
				sortarray[Counter].SetInactive();
				cout << "\nMembership set as inactive!\n";
			}
			//Irrelevant, however user appreciates not being entirely wrong...
			else cout << "\nResuming search for alternatives...\n";

		}
		Counter++;
	}
	//If ID not in the system, inform the user
	if (Found == false) cout << "\nMember not found in the system!\n" << endl;;
}

void DisplayMember(Member* sortarray, int Location) {
	//Output member details to screen
	cout << sortarray[Location].GetMemberID() << "\t\t\t" << sortarray[Location].GetMemberJoinDate() << "\t\t" << sortarray[Location].GetMemberForeName() << " " << sortarray[Location].GetMemberSurName() << endl;

}

void CreateDateSearchBrackets(string CurrentDate, int AccountAge, string& LowerBracketDateSearchReference, string& UpperBracketDateSearchReference) {

	int Year = 0;
	string YearString = "";
	//Change bracket values to initial CurrentDate reference
	UpperBracketDateSearchReference = CurrentDate;
	LowerBracketDateSearchReference = CurrentDate;
	//Extract the year from current date
	Year = stoi(YearString.append(CurrentDate, 0, 4));
	//Calculate the year accounts to be created before
	Year = Year - AccountAge;
	//Change start year of upper range of the bracket
	UpperBracketDateSearchReference.replace(0, 4, to_string(Year));
	//If this is for 50+ year members, give since 1000AD
	if (AccountAge == 50) Year = 1000;
	//Otherwise, subtract 10 from the upper year bracket to give latest year (relational to current year)
	else Year = Year - 10;
	//Apply this year change to the lower bracket to give earliest year
	LowerBracketDateSearchReference.replace(0, 4, to_string(Year));
	
}

bool ImportDatabase(Member* sortarray, int& NumberOfMembers) {


	//Declare & define temp variables for tracking
	string tempforename = "";
	string tempsurname = "";
	string tempjoindate = "";
	string tempmemberid = "";
	int Counter = 0;

	//Load data file
	ifstream MemberDatabase;
	MemberDatabase.open(DatabaseLocation);

	if (MemberDatabase.is_open()) {
		while (!MemberDatabase.eof()) {
			//While next character is not end of line & not end of file
			while (MemberDatabase.peek() != '\n' && !MemberDatabase.eof()) {
				//Pull details into variables
				getline(MemberDatabase, tempforename, ',');
				getline(MemberDatabase, tempsurname, ',');
				getline(MemberDatabase, tempjoindate, ',');
				getline(MemberDatabase, tempmemberid, '\r');
				//Import details into member object
				sortarray[Counter].NewMember(tempforename, tempsurname, tempjoindate, stoi(tempmemberid));
				Counter++;
			}
			
		}
		//Close file connection & return with confirmation of data load
		MemberDatabase.close();
		//Update number of members to new value
		NumberOfMembers = Counter;
		return true;
	}
	else return false;

}