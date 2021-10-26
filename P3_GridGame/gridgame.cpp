#include <iostream>
#include "grid.h"
#include <cassert>
using namespace std;

const int MAX_CONSECUTIVE_INTEGERS = 2;
const char CARDINAL_DIRECTIONS[4] = {'N', 'E', 'S', 'W'};

// Used to iterate through plan to determine if plan portions are of correct form.
bool processPlanPortion(string plan, int& startIndex, int n)
{	// Takes only all upper case plans
	// Returns whether or not there is a plan portion starting at startIndex in string.
	int i = 0;
	while (i <= MAX_CONSECUTIVE_INTEGERS && i + startIndex < n)
	{
		if (plan.at(i + startIndex)=='R' || plan.at(i + startIndex)=='L')
		{
			startIndex += i+1;
			return true;
		}
		else if (!isdigit(plan.at(i + startIndex)))
		{
			return false;
		}
		i++;
	}
	return false;
}

int numericalDir(char dir)
{
	switch (dir)
	{
	case 'N':
		return 0;
		break;
	case 'E':
		return 1;
		break;
	case 'S':
		return 2;
		break;
	case 'W':
		return 3;
		break;
	}
}

// Returns desired steps in direction from plan portion, and updates dir. Only uppercase plan.
int parsePlanPortion(string plan, int& startIndex, int n, char& dir)
{	
	// Stops when index passes length of string.
	if (startIndex >= n)
	{
		return 0;
	}

	// Find # of digits in front of turn letter.
	int digits = 0;
	while (!isalpha(plan.at(startIndex + digits)))
	{
		digits++;
	}
	
	// Turn letter in plan portion
	char turn = toupper(plan.at(startIndex + digits));

	// Gets the numerical mapping of given direction and changes accoring to turn letter
	int numericalDirection = numericalDir(dir);
	if (turn == 'R') {
		numericalDirection++;
	}
	else 
	{
		numericalDirection += 3; // same as -- in modulo 4, but avoids potential negatives.
	}

	// Sets dir to be the updated direction using a cyclic indexing with modulo
	dir = CARDINAL_DIRECTIONS[numericalDirection % 4];

	// Get desired amount of steps
	int steps = 0;
	if (digits == 0)
	{
		startIndex++;
	}
	if (digits == 1)
	{
		steps = plan.at(startIndex + digits - 1) - '0'; // convert char to int
		startIndex += 2;
	}
	if (digits == 2)
	{
		steps += plan.at(startIndex + digits - 1) - '0';			// 10^0 position
		steps += 10 * (plan.at(startIndex + digits - 2) - '0'); // 10^1 position
		startIndex += 3;
	}
	return steps; // FIXME: test 
}

// Moves one step in direction dir if possible and returns true
// else returns false if wall or out of bounds.
bool moveDirection(int& r, int& c, char dir, int dist)
{
	switch (dir)
	{
	case 'N':
		if (r <= 1 || isWall(r - 1,c))
		{
			return false;
		}
		r -= dist;
		return true;
		break;
	case 'E':
		if (c >= getCols() || isWall(r, c + 1))
		{
			return false;
		}
		c += dist;
		return true;
		break;
	case 'S':
		if (r >= getRows() || isWall(r + 1, c))
		{
			return false;
		}
		r += dist;
		return true;
		break;
	case 'W':
		if (c <= 1 || isWall(r, c - 1))
		{
			return false;
		}
		c -= dist;
		return true;
		break;
	}
}

// Checks if position is in valid square and inside given bounds. 
bool validPosition(int r, int c)
{
	if (r < 1 || r > getRows() || c < 1 || c > getCols())
	{
		return false;
	}

	if (isWall(r, c))
	{
		return false;
	}

	return true;
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

	// Check plan by valid portions
	int planPortionStart = 0;

	// If string contains incorrect plan portions return false, else true. 
	while (planPortionStart < planLength)
	{
		if (!processPlanPortion(plan, planPortionStart, planLength))
		{
			return false;
		}
	}

	return true;
}

int determineSafeDistance(int r, int c, char dir, int maxSteps)
{
	// Set direction letter to uppercase
	dir = toupper(dir);

	// Handle invalid cases
	if (dir != 'N' && dir != 'E' && dir != 'S' && dir != 'W')
	{
		return -1;
	}
	if (!validPosition(r,c) || maxSteps < 0)
	{
		return -1;
	}
	
	// Attemps moveDirection until no longer possible.
	// Returns amount of successful moves. 
	int count = 0;
	while (count < maxSteps)
	{
		if (!moveDirection(r, c, dir, 1))
		{
			return count;
		}
		count++;
	}

	return count;
}

int obeyPlan(int sr, int sc, int er, int ec, char dir, string plan, int& nsteps)
{
	// Handles invalid inputs
	dir = toupper(dir);
	if (!validPosition(sr, sc) || !validPosition(er, ec) || !hasCorrectForm(plan))
	{
		return 2;
	}
	if (dir != 'N' && dir != 'E' && dir != 'W' && dir != 'S')
	{
		return 2;
	}

	// Convert plan to upper case
	const int planLength = static_cast<int>(plan.size());
	for (int i = 0; i < planLength; i++)
	{
		plan.at(i) = toupper(plan.at(i));
	}

	int startIndex = 0;
	char newDir = dir;
	int steps = 0;
	int safeSteps = 0;

	while (startIndex < planLength)
	{
		steps = parsePlanPortion(plan, startIndex, planLength, newDir);
		safeSteps = determineSafeDistance(sr, sc, dir, steps);

		nsteps += safeSteps;

		// car hits wall
		if (safeSteps < steps)
		{
			return 3;
		}

		// car moves desired steps
		moveDirection(sr, sc, dir, steps);
		dir = newDir;
	}

	if (sc == ec && sr == er)
	{
		return 0;
	}

	return 1; // FIXME: all
}

int main()
{
	// Testing section

	// Test processPlanPortion
	// Negative cases
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

	// Test hasCorrectForm
	// Negative cases
	assert(!hasCorrectForm("1Lx"));
	assert(!hasCorrectForm("L2"));
	assert(!hasCorrectForm("1Rx2L"));
	assert(!hasCorrectForm("144R"));
	assert(!hasCorrectForm("1R+2L"));
	assert(!hasCorrectForm("N144"));
	assert(!hasCorrectForm("w2+n3"));
	assert(!hasCorrectForm("0LL000L"));
	assert(!hasCorrectForm("rLl5l5r12l35rR000l"));

	// Positive cases
	assert(hasCorrectForm("5rL00L0R09R7L"));
	assert(hasCorrectForm("42l"));
	assert(hasCorrectForm("2R1r"));
	assert(hasCorrectForm("rLl5l5r12l35rR00l"));
	assert(hasCorrectForm(""));
	assert(hasCorrectForm("LL2R02LR0r2L1R"));
	assert(hasCorrectForm("LL2R2r2L1R"));
	assert(hasCorrectForm("LL2R3r2L"));
	assert(hasCorrectForm("LL3R"));

	// Test parsePlanPortion
	int lastStringIndex = 0;
	char dir = 'N';
	string plan = "5RL00L0R09R7L";
	assert(parsePlanPortion(plan, lastStringIndex, static_cast<int>(plan.length()), dir) == 5);
	assert(dir == 'E');
	assert(lastStringIndex == 2);
	assert(parsePlanPortion(plan, lastStringIndex, static_cast<int>(plan.length()), dir) == 0);
	assert(dir == 'N');
	assert(lastStringIndex == 3);
	assert(parsePlanPortion(plan, lastStringIndex, static_cast<int>(plan.length()), dir) == 0);
	assert(dir == 'W');
	assert(lastStringIndex == 6);
	assert(parsePlanPortion(plan, lastStringIndex, static_cast<int>(plan.length()), dir) == 0);
	assert(dir == 'N');
	assert(lastStringIndex == 8);
	assert(parsePlanPortion(plan, lastStringIndex, static_cast<int>(plan.length()), dir) == 9);
	assert(dir == 'E');
	assert(lastStringIndex == 11);
	assert(parsePlanPortion(plan, lastStringIndex, static_cast<int>(plan.length()), dir) == 7);
	assert(dir == 'N');
	assert(lastStringIndex == 13);

	lastStringIndex = 0;
	dir = 'N';
	plan = "";
	assert(parsePlanPortion(plan, lastStringIndex, static_cast<int>(plan.length()), dir) == 0);
	assert(dir == 'N');
	assert(lastStringIndex == 0);

	plan = "LL3R";
	assert(parsePlanPortion(plan, lastStringIndex, static_cast<int>(plan.length()), dir) == 0);
	assert(dir == 'W');
	assert(lastStringIndex == 1);
	assert(parsePlanPortion(plan, lastStringIndex, static_cast<int>(plan.length()), dir) == 0);
	assert(dir == 'S');
	assert(lastStringIndex == 2);
	assert(parsePlanPortion(plan, lastStringIndex, static_cast<int>(plan.length()), dir) == 3);
	assert(dir == 'W');
	assert(lastStringIndex == 4);

	setSize(3, 4);      // make a 3 by 4 grid
	setWall(1, 4);      // put a wall at (1,4)
	setWall(2, 2);      // put a wall at (2,2)
	if (!isWall(3, 2))  // if there's no wall at (3,2)  [there isn't]
		setWall(3, 2);  //    put a wall at (3,2)
	//draw(3, 1, 3, 4);   // draw the grid, showing an S at (3,1) start
						//    position, and an E at (3,4) end position

	// Test moveDirection

	int r = 3;
	int c = 1;
	assert(moveDirection(r, c, 'N', 1));
	assert(r == 2 && c == 1);
	assert(moveDirection(r, c, 'N', 1));
	assert(r == 1 && c == 1);
	assert(!moveDirection(r, c, 'N', 1));
	assert(r == 1 && c == 1);
	assert(!moveDirection(r, c, 'W', 1));
	assert(r == 1 && c == 1);
	assert(moveDirection(r, c, 'E', 1));
	assert(r == 1 && c == 2);
	assert(moveDirection(r, c, 'E', 1));
	assert(r == 1 && c == 3);
	assert(!moveDirection(r, c, 'E', 1));
	assert(r == 1 && c == 3);
	assert(moveDirection(r, c, 'S', 1));
	assert(r == 2 && c == 3);
	assert(moveDirection(r, c, 'S', 1));
	assert(r == 3 && c == 3);
	assert(!moveDirection(r, c, 'S', 1));
	assert(r == 3 && c == 3);
	assert(!moveDirection(r, c, 'W', 1));
	assert(r == 3 && c == 3);
	assert(moveDirection(r, c, 'E', 1));
	assert(r == 3 && c == 4);
	assert(!moveDirection(r, c, 'E', 1));
	assert(r == 3 && c == 4);
	assert(!moveDirection(r, c, 'S', 1));
	assert(r == 3 && c == 4);

	// Test determineSafeDistance

	r = 3;
	c = 1;
	assert(determineSafeDistance(r, c, 'N', 10) == 2);
	assert(r == 3 && c == 1);
	assert(determineSafeDistance(r, c, 'W', 10) == 0);
	assert(determineSafeDistance(r, c, 'S', 10) == 0);
	assert(determineSafeDistance(r, c, 'E', 10) == 0);
	assert(determineSafeDistance(r, c, 'N', 0) == 0);
	assert(determineSafeDistance(r, c, 'N', 1) == 1);
	assert(determineSafeDistance(0, 0, 'W', 10) == -1);
	assert(determineSafeDistance(r, c, 'W', -1) == -1);
	assert(determineSafeDistance(3, 2, 'W', 10) == -1);
	assert(determineSafeDistance(-1, -1, 'W', 10) == -1);
	assert(determineSafeDistance(r, c, 'w', 10) == 0);
	assert(determineSafeDistance(r, c, 'f', 10) == -1);
	assert(determineSafeDistance(r, c, ' ', 10) == -1);
	assert(determineSafeDistance(r, c, '1', 10) == -1);

	// New test grid
	setSize(25, 30);    
	setWall(1, 4);      
	setWall(2, 2);      
	setWall(1, 5);
	setWall(2, 8);
	setWall(8, 2);
	setWall(20, 21);
	//draw(20, 1, 17, 14);   

	assert(determineSafeDistance(20, 1, 'e', 29) == 19);
	assert(determineSafeDistance(20, 1, 'w', 29) == 0);
	assert(determineSafeDistance(20, 1, 'S', 29) == 5);
	assert(determineSafeDistance(20, 1, 'n', 29) == 19);
	assert(determineSafeDistance(20, 1, 'e', 10) == 10);
	assert(determineSafeDistance(10, 21, 'e', 29) == 9);
	assert(determineSafeDistance(10, 21, 'W', 29) == 20);
	assert(determineSafeDistance(10, 21, 's', 29) == 9);

	// Test obeyPlan
	setSize(6, 6);
	setWall(1, 4);
	setWall(2, 2);
	setWall(1, 5);
	setWall(2, 6);
	setWall(6, 2);
	setWall(2, 5);
	setWall(1, 3);
	setWall(4, 3);
	setWall(5, 4);
	//draw(1, 1, 6, 3);

	int sc = 1;
	int sr = 1;
	int er = 6;
	int ec = 3;
	plan = "2l1R2L1r1r";
	dir = 's';
	int nsteps = 0;
	assert(obeyPlan(sr, sc, er, ec, dir, plan, nsteps) == 0);
	assert(nsteps == 7);

	string planList[7] = { "2l1R2L1r1r" , "2l5R3r3l", "2l3R1L" , "3r2L", "2l5R3r3l2r" , "3r", "2l2l1r"};
	char dirList[7] = {'s', 's', 'S' , 'E', 's', 'w', 's'};
	int validity[7] = {0, 0, 1, 3, 3, 3, 1};
	int stepList[7] = {7, 13, 6, 1, 13, 0, 5};
	int cumulativeSteps = 7;
	for (int i = 0; i < 7; i++)
	{
		char dir = dirList[i];
		assert(obeyPlan(sr, sc, er, ec, dir, planList[i], nsteps) == validity[i]);
		cumulativeSteps += stepList[i];
		assert(cumulativeSteps == nsteps);
	}

	// test invalid starting pos, ending pos, and direction.
	nsteps = 7;
	dir = 's';
	assert(obeyPlan(2, 2, er, ec, dir, "2l1R2L1r1r", nsteps) == 2);
	assert(nsteps == 7);
	assert(obeyPlan(2, 1, 4, 3, 's', "2l1R2L1r1r", nsteps) == 2);
	assert(nsteps == 7);
	assert(obeyPlan(1, 1, 3, 3, 'f', "2l1R2L1r1r", nsteps) == 2);
	assert(nsteps == 7);
	assert(obeyPlan(-1, 1, 3, 3, 'f', "2l1R2L1r1r", nsteps) == 2);
	assert(nsteps == 7);
	assert(obeyPlan(1, 0, 3, 3, 'f', "2l1R2L1r1r", nsteps) == 2);
	assert(nsteps == 7);
	assert(obeyPlan(1, 1, 7, 3, 'f', "2l1R2L1r1r", nsteps) == 2);
	assert(nsteps == 7);
	assert(obeyPlan(1, 1, 3, 9, 'f', "2l1R2L1r1r", nsteps) == 2);
	assert(nsteps == 7);

	cerr << "All tests succeeded" << endl;
	// End of testing section
}
