// Code for Project 1
	// Report survey results

#include <iostream>
using namespace std;

//int main()  //Remove main
{
	//Removed variable declarations
	int numberSurveyed;
	int likeInPerson;
	int likeAtHome;

	cout << "How many students were surveyed? ";
	cin >> numberSurveyed//;	//Forget semicolon 
	cout << "How many of them prefer being at school in person? ";
	cin >> likeInPerson;
	cout << "How many of them would rather do school from home? ";
	cin >> likeAtHome;

	/*double*/ pctLikeInPerson = 100.0 * likeInPerson / numberSurveyed;	//Leave out type declaration
	double pctLikeAtHome = 100.0 * likeAtHome / numberSurveyed;

	cout.setf(ios::fixed);
	cout.precision(1);

	cout << endl;
	cout << pctLikeInPerson << "% prefer being at school in person." << endl;
	cout << pctLikeAtHome << "% prefer doing school from home." << endl;

	if /*(*/ likeInPerson > likeAtHome/*)*/ //Leave out parenthesis
		cout << "More students like being at school in person than doing school at home." << endl;
	else
		cout << "More students like doing school from home than being at school in person." << endl;
}