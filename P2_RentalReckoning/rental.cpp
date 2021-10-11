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

	// Declaration of own variables
	double amount = 0;
	int dist = ODO_END - ODO_START;

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
	else if (MONTH<1 || MONTH>12) { //What if MONTH is a decimal number?
		cout << "---" << endl;
		cout << "The month number must be in the range 1 through 12." << endl;
	}
	else {
		//Computation
		
		//Base
		if (LUXURY=="y") {
			amount += DAYS * dailyLux;
		}
		else {
			amount += DAYS * dailyBase;
		}
		//Mile charge
		if (dist<=100) {
			amount += dist * rateInit;
		}
		else if (dist>100 && dist <= 500) {
			amount += 100 * rateInit;
			if (3 < MONTH < 12) {
				amount += (dist - 100) * rateMidNonWinter;
			}
			else {
				amount += (dist - 100) * rateInit;
			}
		}
		else {
			amount += 100 * rateInit;
			if (3 < MONTH < 12) {
				amount += 400 * rateMidNonWinter;
			}
			else {
				amount += 400 * rateInit;
			}
			amount += (dist - 500) * rateLong;
		}

		cout << "---" << endl;
		cout << "The rental charge for " << NAME << " is $" << amount << endl;
	}
}