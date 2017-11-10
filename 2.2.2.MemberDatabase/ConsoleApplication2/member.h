#ifndef MEMBER_H
#define MEMBER_H
#include <string>
#include <algorithm>
using namespace std;


class Member
{
public:
	Member();
	~Member();
	//Provides a method to set details of a new member record
	void NewMember(string foreName, string surName, string joinDate, int memberID);
	//Provides a method to extract the details to display them
	int GetMemberID() const;
	bool GetActiveStatus() const;
	string GetMemberSurName() const;
	string GetMemberForeName() const;
	string GetMemberJoinDate() const;
	string GetCompareID() const;
	//Allows the record to be set inactive
	void SetInactive();
	

private:
	//Declare variables the recoord will hold
	string ForeName;
	string SurName;
	string JoinDate;
	int MemberID;
	bool IsActive;
	string CompareIdentifier;
	//Functions only used within the member class itself
	int ConvertIncomingDate(string joinDate);
	string CreateCompareID(int joinDate, string surName, string foreName);

};

Member::Member()
{
	//Set all values to defaults upon creation
	ForeName = "";
	SurName = "";
	JoinDate = "";
	MemberID = 0;
	CompareIdentifier = "";
	IsActive = false;
}

Member::~Member()
{
}

void Member::NewMember(string foreName, string surName, string joinDate, int memberID) {
	//Apply the provided details to the member record
	ForeName = foreName;
	SurName = surName;
	JoinDate = joinDate;
	MemberID = memberID;
	//Create search identifier
	CompareIdentifier = CreateCompareID(ConvertIncomingDate(joinDate), surName, foreName);
	//Set item to be active
	IsActive = true;
}

int Member::ConvertIncomingDate(string joinDate) {

	//Converts the date string of format DD/MM/YYYY into integer of format YYYYMMDD for ease of sorting
	string tempdate = "";
	//Year
	tempdate.append(joinDate, 6, 4);
	//Month
	tempdate.append(joinDate, 3, 2);
	//Day
	tempdate.append(joinDate, 0, 2);
	//Converts string to integer and returns it to the calling function in the new format
	return stoi(tempdate);

}

string Member::CreateCompareID(int joinDate, string surName, string foreName) {

	//Function creates string of format "YYYYMMDD<SurName>_____<whitespace until unified value>_____<ForeName>"
	//This will allow easy comparison for sort algorithm

	string tempcompareID = "";
	//Ensure all characters are of same case
	transform(foreName.begin(), foreName.end(), foreName.begin(), tolower);
	transform(surName.begin(), surName.end(), surName.begin(), tolower);
	//Add date to start of string
	tempcompareID.append(to_string(joinDate));
	//Add surname after date
	tempcompareID.append(surName);
	//Assume longest surname is max 700; add whitespace for each unused character
	int surNameLength = surName.length();
	for (int i = 700; i <= surNameLength; i--) {
		tempcompareID.append(" ");
	}
	//Add forename to end of compare string
	tempcompareID.append(foreName);

	//Return the full compare string to be stored
	return tempcompareID;
}

string Member::GetCompareID() const{
	return CompareIdentifier;
}

void Member::SetInactive() {
	IsActive = false;
}

int Member::GetMemberID() const {
	return MemberID;
}

string Member::GetMemberSurName() const {
	return SurName;
}

string Member::GetMemberForeName() const {
	return ForeName;
}

string Member::GetMemberJoinDate() const {
	return JoinDate;
}

bool Member::GetActiveStatus() const {
	return IsActive;
}
#endif