#include <iostream>
#include "grid.h"
#include <cassert>
using namespace std;

const int MAX_CONSECUTIVE_INTEGERS = 2;

bool processPlanPortion(string plan, int& startIndex, int n)
{	// Takes only all upper case plans
	// Returns whether or not there is a plan portion starting at startIndex in string.
	int i = 0;
	while (i <= MAX_CONSECUTIVE_INTEGERS && i + startIndex < n)
	{
		if (plan.at(i)=='R' || plan.at(i)=='L')
		{
			startIndex += i+1;
			return true;
		}
		else if (!isdigit(plan.at(i)))
		{
			return false;
		}
		i++;
	}
	return false;
}

// The three following functions are mandatory.
bool hasCorrectForm(string plan)
{
	const int planLength = static_cast<int>(plan.size());

	// Convert all to upper case
	for (int i = 0; i < planLength; i++)
	{
		plan.at(i) = toupper(plan.at(i));
	}

	// check plan by valid portions
	int planPortionStart = 0;

	while (planPortionStart < planLength)
	{
		if (!processPlanPortion(plan, planPortionStart, planLength))
		{
			return false;
		}
	}
	//FIXME: Determine whether last plan is included here, just return true?

	return true; // FIXME: all
}

int determineSafeDistance(int r, int c, char dir, int maxSteps)
{
	return 0; // FIXME: all
}

int obeyPlan(int sr, int sc, int er, int ec, char dir, string plan, int& nsteps)
{
	return 0; // FIXME: all
}

int main()
{
	// Testing section
	/*
	setSize(3, 4);      // make a 3 by 4 grid
	setWall(1, 4);      // put a wall at (1,4)
	setWall(2, 2);      // put a wall at (2,2)
	if (!isWall(3, 2))  // if there's no wall at (3,2)  [there isn't]
		setWall(3, 2);  //    put a wall at (3,2)
	draw(3, 1, 3, 4);    // draw the grid, showing an S at (3,1) start
					   //    position, and an E at (3,4) end position
	*/

	// negative cases processPlanPortion
	int startIndex = 0;
	startIndex = 0;
	assert(!processPlanPortion("69l", startIndex, 3));
	assert(startIndex == 0);
	startIndex = 0;
	assert(!processPlanPortion("1r", startIndex, 2));
	assert(startIndex == 0);
	startIndex = 0;
	assert(!processPlanPortion("100l", startIndex, 4));
	assert(startIndex == 0);
	startIndex = 0;
	assert(!processPlanPortion("12", startIndex, 2));
	assert(startIndex == 0);
	startIndex = 0;
	assert(!processPlanPortion("1", startIndex, 1));
	assert(startIndex == 0);
	startIndex = 0;
	assert(!processPlanPortion("12R", startIndex, 2));
	assert(startIndex == 0);
	startIndex = 0;
	assert(!processPlanPortion("1w", startIndex, 1));
	assert(startIndex == 0);
	assert(!processPlanPortion("12r", startIndex, 3));
	assert(startIndex == 0);
	startIndex = 0;
	assert(!processPlanPortion("1w", startIndex, 2));
	assert(startIndex == 0);
	
	// positive cases processPlanPortion
	startIndex = 0;
	assert(processPlanPortion("69L", startIndex, 3));
	assert(startIndex == 3);
	startIndex = 0;
	assert(processPlanPortion("1R", startIndex, 2));
	assert(startIndex == 2);
	startIndex = 0;
	assert(processPlanPortion("R", startIndex, 1));
	assert(startIndex == 1);
	startIndex = 0;
	assert(processPlanPortion("L", startIndex, 1));
	assert(startIndex == 1);
	startIndex = 0;
	assert(processPlanPortion("1L", startIndex, 2));
	assert(startIndex == 2);
	startIndex = 0;
	assert(processPlanPortion("69L", startIndex, 10));
	assert(startIndex == 3);
	cerr << "All tests succeeded" << endl;

	// End of testing section
}
