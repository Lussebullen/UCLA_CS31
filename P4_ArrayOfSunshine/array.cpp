#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int reduplicate(string a[], int n)
{
	if (n < 0) // Handle degenerate cases
	{
		return -1;
	}

	for (int i = 0; i < n; i++)
	{	// for each element in array, add to itself
		a[i] += a[i];
	}
	return n;
}

int locate(const string a[], int n, string target)
{
	if (n < 0)	// Handle degenerate cases
	{
		return -1;
	}

	for (int i = 0; i < n; i++) 
	{
		if (a[i] == target)
		{
			return i;
		}
	}
	return -1;
}

int locationOfMax(const string a[], int n)
{
	if (n < 1)   // <1 for this one, as negatives not allowed
	{			 // and 0 would mean no value is examined.
		return -1;
	}

	int maxLoc = 0;
	for (int i = 0; i < n; i++)
	{
		if (a[i] > a[maxLoc]) // for smallest index only, update on strict inequality
		{
			maxLoc = i;
		}
	}
	return maxLoc;
}

int circleLeft(string a[], int n, int pos)
{
	if (n < 0 || pos < 0 || pos >= n)	//Degenerate cases
	{
		return -1;
	}
	if (n == 1)		//Only one element, nothing happens.
	{
		return 1;
	}
	string tmpString = a[pos];
	for (int i = pos; i < n - 1; i++)
	{
		a[pos] = a[pos + 1];
	}
	a[n - 1] = tmpString;
	return pos;
}

int enumerateRuns(const string a[], int n)
{
	if (n < 0)	// Handle degenerate cases
	{
		return -1;
	}
	if (n == 0)	// Handle 0 case as next part automatically starts with count 1.
	{
		return 0;
	}
	int count = 1;
	for (int i = 0; i < n - 1; i++)
	{
		if (a[i] != a[i + 1])
		{
			count++;
		}
	}
	return count;
}

int flip(string a[], int n)
{
	if (n < 0)	// Handle degenerate cases
	{
		return -1;
	}
	// Run through first half of array and swapping each element
	// with its corresponding element on the right. 
	string tmpString;
	for (int i = 0; i < n/2; i++)
	{
		tmpString = a[i];
		a[i] = a[n - 1 - i];
		a[n - 1 - i] = tmpString;
	}
	return n;
}

int locateDifference(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 < 0 || n2 < 0)	// Handle degenerate cases
	{
		return -1;
	}
	int maxIndex = min(n1,n2);	// Stop when end of smaller array reached
	int count = 0;
	for (int i = 0; i < maxIndex; i++)
	{
		if (a1[i] == a2[i])
		{
			count++;
		}
	}
	return count;
}

int subsequence(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 < 0 || n2 < 0)	// Handle degenerate cases
	{
		return -1;
	}
	if (n2 == 0)		// Empty list case
	{
		return 0;
	}
	int j = 0;
	for (int i = 0; i < n1; i++)
	{
		if (a1[i] == a2[j])
		{	// if match found increment through a2 to check if full array is there
			j++;
		}
		else 
		{	// reset for mismatch
			j = 0;
		}
		if (j == n2)
		{	// if full array is there return the index at which it started.
			return i - n2 + 1;
		}
	}
	return -1;
}

int locateAny(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 < 0 || n2 < 0)	// Handle degenerate cases
	{
		return -1;
	}
	for (int i = 0; i < n1; i++)
	{
		for (int j = 0; j < n2; j++)
		{
			if (a1[i] == a2[j])
			{
				return i;
			}
		}
	}
	return -1;
}

int separate(string a[], int n, string separator)
{
	if (n < 0)	// Handle degenerate cases
	{
		return -1;
	}
	// Rearrangement
	int i = 0;
	int j = n - 1;
	while (i < j) 
	{
		if (a[i] > separator && a[j] < separator)
		{	//Swap values
			string tmpString = a[i];
			a[i] = a[j];
			a[j] = tmpString;
			i++;
			j--;
		}
		else if (a[i] > separator)
		{	// decrement j till valid swap value is found
			j--;
		}
		else if (a[j] < separator)
		{	// increment i until valid swap value is found
			i++;
		} 
		else
		{	// both values in correct spot, in/decrement both
			i++;
			j--;
		}
	}

	// Return value computation
	for (int k = 0; k < n; k++)
	{
		if (a[k] >= separator)
		{
			return k;
		}
	}
	return n;
}

int main()
{
	// Test reduplicate
	string c[4] = { "ma", "can", "tu", "do" };
	assert(reduplicate(c, 4) == 4 && c[0] == "mama" && c[3] == "dodo");
	string stuff[6] = { "mahi", "bon", "cous", "", "tar", "mur" };
	assert(reduplicate(stuff, 3) == 3 && stuff[1] == "bonbon" && stuff[5] == "mur");
	assert(reduplicate(c, 0) == 0 && c[0] == "mama");
	assert(reduplicate(c, -5) == -1 && c[0] == "mama");

	// Test locate
	string h[7] = { "moana", "mulan", "ariel", "tiana", "", "belle", "elsa" };
	assert(locate(h, 7, "belle") == 5);
	assert(locate(h, 7, "elsa") == 6);
	assert(locate(h, 7, "ariel") == 2);
	assert(locate(h, 2, "ariel") == -1);
	assert(locate(h, 0, "") == -1);
	assert(locationOfMax(h, 7) == 3);
	string k[7] = { "moana", "mulan", "ariel", "tiana", "", "ariel", "elsa" };
	assert(locate(k, 7, "ariel") == 2);
	assert(locate(k, -1, "ariel") == -1);
	assert(locate(k, 7, "Ariel") == -1);

	// Test locationOfMax
	string h1[5] = { "5","1","7","9","4" };
	assert(locationOfMax(h1, 5) == 3);
	assert(locationOfMax(h1, 0) == -1);
	assert(locationOfMax(h1, -4) == -1);
	h1[1] = "9";
	assert(locationOfMax(h1, 5) == 1);

	// Test circleLeft
	string g[4] = { "moana", "mulan", "belle", "raya" };
	assert(locateDifference(h, 4, g, 4) == 2);
	assert(circleLeft(g, 4, 1) == 1 && g[1] == "belle" && g[3] == "mulan");
	assert(circleLeft(g,0,1) == -1);
	assert(circleLeft(g, -1, 1) == -1);
	assert(circleLeft(g, 2, 3) == -1);
	assert(circleLeft(g, 3, -1) == -1);
	assert(circleLeft(g, 2, 1) == 1 && g[1] == "belle" && g[0] == "moana");
	assert(circleLeft(g, 2, 0) == 0 && g[0] == "belle" && g[1] == "moana");

	// Test enumerateRuns
	string d[5] = { "mulan", "mulan", "mulan", "belle", "belle" };
	assert(enumerateRuns(d, 5) == 2);
	string d1[9] = {"belle", "merida", "raya", "raya", "tiana", "tiana", "tiana", "raya", "raya"};
	assert(enumerateRuns(d1, 9) == 5);
	assert(enumerateRuns(d1, 2) == 2);
	assert(enumerateRuns(d1, 0) == 0);
	assert(enumerateRuns(d1, -9) == -1);

	// Test flip
	string f[3] = { "tiana", "ariel", "raya" };
	assert(locateAny(h, 7, f, 3) == 2);
	assert(flip(f, 3) == 3 && f[0] == "raya" && f[2] == "tiana" && f[1]=="ariel");
	assert(flip(f, 1) == 1 && f[0]=="raya" && f[2] == "tiana" && f[1] == "ariel");
	assert(flip(f, 0) == 0 && f[0] == "raya" && f[2] == "tiana" && f[1] == "ariel");
	assert(flip(f, -5) == -1 && f[0] == "raya" && f[2] == "tiana" && f[1] == "ariel");

	//Test locateDifference
	string roles[6] = { "merida", "raya", "", "belle", "moana", "elsa" };
	string group[5] = { "merida", "raya", "elsa", "", "belle" };
	assert(locateDifference(roles, 6, group, 5) == 2);
	assert(locateDifference(roles, 2, group, 1) == 1);
	assert(locateDifference(roles, 0, group, 1) == 0);
	assert(locateDifference(roles, -2, group, 1) == -1);
	assert(locateDifference(roles, 2, group, -1) == -1);

	// Test subsequence
	string e[4] = { "ariel", "tiana", "", "belle" };
	assert(subsequence(h, 7, e, 4) == 2);
	string names[10] = { "moana", "mulan", "raya", "tiana", "merida" };
	string names1[10] = { "mulan", "raya", "tiana" };
	assert(subsequence(names, 5, names1, 3) == 1);
	string names2[10] = { "moana", "tiana" };
	assert(subsequence(names, 4, names2, 2) == -1);
	assert(subsequence(names, 4, names2, -2) == -1);
	assert(subsequence(names, -4, names2, 2) == -1);
	string empty[1] = {};
	assert(subsequence(names, 5, empty, 0) == 0);
	assert(subsequence(names, 0, empty, 0) == 0);
	assert(subsequence(names, 2, names1, 3) == -1);

	// Test locateAny
	string set1[10] = { "elsa", "merida", "tiana", "mulan" };
	assert(locateAny(names, 6, set1, 4) == 1);  
	string set2[10] = { "belle", "ariel" };
	assert(locateAny(names, 6, set2, 2) == -1);
	assert(locateAny(names, -6, set1, 4) == -1);
	assert(locateAny(names, 6, set1, -4) == -1);
	assert(locateAny(names, 6, set1, 4) == 1);
	string set3[1] = { "mulan" };
	assert(locateAny(set1, 4, set3, 1) == 3);

	// Test separate
	assert(separate(h, 7, "elsa") == 3);
	string cast[6] = { "elsa", "ariel", "mulan", "belle", "tiana", "moana" };
	string cast2[4] = { "mulan", "tiana", "ariel", "raya" };
	assert(separate(cast, 6, "merida") == 3 && cast[0]=="elsa" && cast[1]=="ariel" && cast[2]=="belle" && cast[3]=="mulan");
	assert(separate(cast2, 4, "raya") == 2 && cast2[0]=="mulan" && cast2[1]=="ariel" && cast2[2]=="tiana");
	assert(separate(cast,-1,"cow") == -1);
	assert(separate(cast, 6, "zebra") == 6);
	assert(separate(cast, 0, "zebra") == 0);


	cout << "All tests succeeded" << endl;
}