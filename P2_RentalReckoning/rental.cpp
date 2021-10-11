// Code for Project 2
	// Rental reckoning

#include <iostream>
#include <string>
using namespace std;

int main() {
	// Input variable declaration
	int ODO_START;
	int ODO_END;
	int DAYS;
	int MONTH;
	string NAME;
	string LUXURY;

	// Declaration of given constants
	int dailyBase = 43;
	int dailyLux = 71;
	double rateInit = 0.27;
	double rateMidNonWinter = 0.21;
	double rateLong = 0.17;

	// Declaration of own variables
	double amount = 0;

	// Input section
	cout << "Odometer at start: ";
	cin >> ODO_START;
	cout << "Odometer at end: ";
	cin >> ODO_END;
	cout << "Rental days: ";
	cin >> DAYS;
	cin.ignore(10000, '\n');
	cout << "Customer name: ";
	getline(cin, NAME);
	cout << "Luxury car? (y/n): ";
	cin >> LUXURY;
	cout << "Month (1=Jan, 2=Feb, etc.): ";
	cin >> MONTH;

	//Output section
	if (ODO_START < 0) {
		cout << "---" << endl;
		cout << "The starting odometer reading must not be negative." << endl;
	}
	else if (ODO_END<ODO_START) {
		cout << "---" << endl;
		cout << "The ending odometer reading must be at least as large as the starting reading." << endl;
	}
	else if (DAYS<1) {
		cout << "---" << endl;
		cout << "The number of rental days must be positive." << endl;
	}
	else if (NAME=="") {
		cout << "---" << endl;
		cout << "You must enter a customer name." << endl;
	}
	else if (LUXURY!="y" && LUXURY!="n") {
		cout << "---" << endl;
		cout << "You must enter y or n." << endl;
	}
	else if (MONTH<1 || MONTH>12) {
		cout << "---" << endl;
		cout << "The month number must be in the range 1 through 12." << endl;
	}
	else {
		cout << "---" << endl;
		cout << "The rental charge for customer is $" << amount << endl;
	}

	

}