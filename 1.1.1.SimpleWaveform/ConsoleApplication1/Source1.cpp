/*Software Development AC51002 (16/17)
Assignment 2
Application 1 - Waveform
John McGouran

The main assumptions in this application are as follows:

1) The wave is not a true triangle wave. In the example given, the start and endpoint of each graph trough have an additional
	character. Additionally, there is no requirement for the waveform to have a constant period, instead allowing the wave height
	to define the period of the wave. This invalidates the status of it being a real waveform, making it dificult to represent
	using a formula. If a true triangle wave was to be used, it could be simply generated using the formula:

		y = (A/P) * (P - abs(x % (2*P) - P) )

	Where:
		-y is the horizontal co-ordinate in this vertical graph, represented by total line length
		-x is the vertical co-ordinate, represented by the line number
		-A is the amplitude, represented by the requested wave height
		-P is the period, not currently represented in the code as it is dynamic.

	Due to the above, the graph must be represented in two parts:
		1) y = x
		2) y = 2A-x

	Where:
		1) Is the incremental function.
		2) Is the declining function.

	The functions are concatenated, using the amplitude as the divider, then repeated for each requested waveform.

2) The user will input integer numbers when requested for a quantity and wave height.
3) The user will not enter a value that exceeds the width of the console window. If the user requires a larger graph space,
	typing 'mode x', where x is a number greater than 80, into a command window, will expand the width according to the value.
	The user can then navigate to the executable and run it in this larger environment.
4) The user can read English.
	
*/




#include <iostream>
#include <time.h>
using namespace std;

const int MILLISECONDS = 50; //Loop delay as a visual aid.

void delay() {
	//Function for delaying loop speed.
	clock_t goal = MILLISECONDS + clock();
	while (goal > clock());
}

void render_graph(int wave_quantity = 0, int wave_height = 0, char allow_growth = 'N'){
	//Function to create the graph using the user input from main().
	for (int wave_number = 0; wave_number < wave_quantity; wave_number++) {
		//Loop repeats for each instance of the wave that was requested.
		for (int incr_line = 1; incr_line < wave_height; incr_line++) {
			//Defines the wave segment for the incremental wave.
			delay(); //Calls function to delay the loop.
			cout << "\n";

			for (int incr_fill = 0; incr_fill < incr_line; incr_fill++) {
				//Fills the wave segment to the required height.
				delay(); //Calls function to delay the loop.
				cout << "*";
			}
		}
		for (int decl_line = wave_height; decl_line > 0; decl_line--) {
			//Defines the wave segment for the declining wave.
			delay(); //Calls function to delay the loop.
			cout << "\n";

			for (int decl_fill = decl_line; decl_fill > 0; decl_fill--) {
				//Fills the wave segment to the required height.
				delay(); //Calls function to delay the loop.
				cout << "*";
			}
		}
		if (allow_growth == 'Y') wave_height = wave_height + 1; //Switch to enable growth in the waveform.
	}
}

int main(){

	int wave_height = 0;		//Variables declared and defined to default values.
	int wave_quantity = 0;
	char allow_growth = 'N';

	cout << "This application generates a triangle waveform, represented vertically in the form of the asterisk character(*).";
	cout << "\nYou may select the size of the wave generated and the quantity generated.";
	cout << "\nIn addition, you may select whether the wave grows from its initial size.";
	//User information on the applications purpose and usage.
	cout << "\n\nPlease enter the height of the waveform: ";
	cin >> wave_height;
	//Prompts the user for the requested height of the wave.
	cout << "\n\nNow please enter the quantity of waves desired: ";
	cin >> wave_quantity;
	//Prompts the user for the requested quantity of waves.
	cout << "\n\nWould you like the waveform to grow?(Y/N): ";
	cin >> allow_growth;
	//Prompts the user if they would like to see growth.
	while (allow_growth != 'N' && allow_growth != 'Y'){
		//Filter to ensure that only N or Y can be input to the application for growth selection. User is prompted until a valid value is input.
		cout << "\nPlease enter a valid selection(Y/N): ";
		cin >> allow_growth;
	}
	render_graph(wave_height, wave_quantity, allow_growth); //Calls function to create the graph in the console window.
}