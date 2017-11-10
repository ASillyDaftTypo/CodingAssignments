/*Software Development AC51002 (16/17)
Assignment 2
Application 2 - Phone bill generator
John McGouran

The main assumptions in this application are as follows:

1) The rates the user pays are:
	- £0.15/minute for mobile.
	- £0.08/minute for landlines.

2) Discounts rates are fractal and are set at the following rates:
	- Under 100 minutes grants no discount.
	- Between 100 and 200 minutes grants the user 5% discount on these minutes.
	- Between 200 and 300 minutes grants the user 10% discount on these minutes.
	- Any minutes over 300 are granted a 15% discount.

3) The user will input the correct characters when prompted (although filtering has been added.)
4) The user can read English.

The application prompts the user for the type of bill that they are calculating (mobile or landline),
then asks the user for their minutes usage. They must confirm that the input has been read correctly
before proceeding.
The application then places the data in a class and performs the nessecary calculations for the discount
breakpoints and stores these in a 2D array.
The total is returned to the user, then prompted if they would like to see a breakdown of the costs. If
the user chooses to do so, it calls another member that builds a table showing the costs and the total.

*/


#include <iostream>
#include <iomanip> //Required to allow for 2 decimal place precision
#include <string>
#include <sstream> //Required to sanitise user input when prompted for an integer
using namespace std;

//Assumed price rates and discounts declared as constants
const float current_mobile_rate = 0.15;
const float current_landline_rate = 0.08;
const float discount_level_one = 0.95;
const float discount_level_two = 0.90;
const float discount_level_three = 0.85;

class Bill {
	private:
		//Private members hold the filtered user input and the calculated values.
		int minutes;
		double bill[4][2];
		double total_price;
		string bill_type;
		float rate;
	public:
		//Public members of the class to call input and calculations.
		Bill();
		void set_total_minutes(int);
		void generate_bill();
		void set_rate(string);
		double get_total();
		void display_costs();
};

Bill::Bill() {
	//Initialise members of the Bill class.
	minutes = 0;
	total_price = 0;
	total_price = 0;
	bill_type = "";
	rate = 0;
}

void Bill::set_total_minutes(int x) {
	minutes = x; //Inputs the users minutes into the class
}

void Bill::set_rate(string phone_type) {
	//Reads the users phone type selection and sets the appropriate rate.
	bill_type = phone_type;
	if (bill_type == "Mobile") rate = current_mobile_rate;
	else rate = current_landline_rate;
}

void Bill::generate_bill() {

	if (minutes > 100) {
		bill[0][0] = 100; //Sets value to maxmimum, as they have more than required for this field

		bill[0][1] = bill[0][0] * rate; //Calculate price for these minutes.
		total_price = bill[0][1]; //Add price to total.

		if (minutes > 200) {
			bill[1][0] = 100; //Sets value to maxmimum, as they have more than required for this field.

			bill[1][1] = bill[1][0] * rate * discount_level_one; //Calculate price for these minutes, with the appropriate discount.
			total_price = total_price + bill[1][1]; //Add price to total.

			if (minutes > 300) {

				bill[2][0] = 100; //Sets value to maxmimum, as they have more than required for this field

				bill[2][1] = bill[2][0] * rate * discount_level_two; //Calculate price for these minutes, with the appropriate discount.
				total_price = total_price + bill[2][1]; //Add price to total.

				bill[3][0] = minutes - 300; //Sets the value to the remaining minutes
				bill[3][1] = bill[3][0] * rate * discount_level_three; //Calculate price for these minutes, with the appropriate discount.
				total_price = total_price + bill[3][0]; //Add price to total.
			}
			else {
				bill[2][0] = minutes - 200; //Sets the value to the remaining minutes
				bill[2][1] = bill[2][0] * rate * discount_level_two; //Calculate price for these minutes, with the appropriate discount.
				total_price = total_price + bill[2][1]; //Add price to total.
			}
		}
		else {
			bill[1][0] = minutes - 100; //Sets the value to the remaining minutes
			bill[1][1] = bill[1][0] * rate * discount_level_one; //Calculate price for these minutes, with the appropriate discount.
			total_price = total_price + bill[1][1]; //Add price to total.
		}
	}
	else {
		bill[0][0] = minutes; //Sets the value to the remaining minutes
		bill[0][1] = bill[0][0] * rate; //Calculate price for these minutes.
		total_price = bill[0][1]; //Add price to total.
	}
}

double Bill::get_total() {
	return total_price; //Allows total price of bill to be retrieved.
}

void Bill::display_costs() {
	//Function creates a table displayed in the command window displaying a breakdown of the costs.
	cout << "\n\n" << bill_type << " bill for this month is: \nRate: \234" << rate << "/min\nMinutes\t\tDiscount\tPrice (\234)\n----------------------------------------------------\n";
	cout << bill[0][0] << "\t\t|\t0%\t|\t" << bill[0][1] << "\n";
	if (minutes > 100) {
		cout << bill[1][0] << "\t\t|\t" << 100-(discount_level_one*100) << "%\t|\t" << bill[1][1] << "\n";
		if (minutes > 200) {
			cout << bill[2][0] << "\t\t|\t" << 100-(discount_level_two*100) << "%\t|\t" << bill[2][1] << "\n";
			if (minutes > 300) {
				cout << bill[3][0] << "\t\t|\t" << 100-(discount_level_three*100) << "%\t|\t" << bill[3][1] << "\n";
			}
		}
	}
	cout << "\t\t\t\t Total: \234 " << total_price;
}

int get_minutes() {
	//Declare local variables.
	char minutes_confirm = 'N';
	string minutes_input = "";
	int minutes = 0;
	//Sanitise user input to ensure only a positive integer is passed through the 'cin' operator. Repeats until valid input is confirmed by the user.
	while (minutes_confirm != 'Y') {
		cout << "\nPlease enter the total number of minutes used this month:";
		cin >> minutes_input;
		stringstream convert(minutes_input);
		convert >> minutes;
		minutes = abs(minutes);
		cout << "\nInput reads: " << minutes << " Minutes.\nIs this correct?(Y/N): ";
		cin >> minutes_confirm;
	}
	return minutes;
}

string get_phone_type(){
	string phone_type = "";
	//Prompts user for phone type - repeats until valid input received.
	cout << "Please select a mode of calculation (Landline/Mobile): ";
	cin >> phone_type;
	while (phone_type != "Landline" && phone_type != "Mobile") {
		cout << "\nPlease select a valid mode (Landline/Mobile):";
		cin >> phone_type;
	}
	return phone_type;
}

int main() {
	//Variables declared and initialised for the main function.
	char breakdown = 'N';
	int minutes = 0;
	double total = 0;
	string phone_type = "";
	Bill CurrentBill;

	phone_type = get_phone_type(); //Calls function to obtain phone type from the user.
	minutes = get_minutes(); //Calls function to obtain quantity of minutes from the user.
	CurrentBill.set_rate(phone_type); //Calls member to set the phone bill type
	CurrentBill.set_total_minutes(minutes); //Adds the minutes to the class
	CurrentBill.generate_bill(); //Calls the member to perform the actual calculations

	//Displays the total cost to the user.
	total = CurrentBill.get_total();
	cout << setprecision(2) << fixed << "\n\nYour total bill is: \234" << total;
	//Prompts user if they would like more details of the bill.
	cout << "\n\nWould you like a breakdown of costs?(Y/N): ";
	cin >> breakdown;
	while (breakdown != 'N' && breakdown != 'Y') { //Checks user input and repeats until valid.
		cout << "\nPlease input a valid selection: ";
		cin >> breakdown;
	}
	if (breakdown == 'Y') CurrentBill.display_costs(); //Displays the table with costs.

}