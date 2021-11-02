#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int reduplicate(string a[], int n)
{
	if (n < 0)
	{
		return -1;
	}

	for (int i = 0; i < n; i++)
	{
		a[i] += a[i];
	}
	return n;
}

int locate(const string a[], int n, string target)
{
	if (n < 0)
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
		if (a[i] > a[maxLoc]) // for smallest index only update on strict inequality
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
	if (n < 0)
	{
		return -1;
	}
	if (n == 0)
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
	if (n < 0)
	{
		return -1;
	}
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
	if (n1 < 0 || n2 < 0)
	{
		return -1;
	}
	int maxIndex = min(n1,n2);
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
	if (n1 < 0 || n2 < 0)
	{
		return -1;
	}
	int j = 0;
	for (int i = 0; i < n1; i++)
	{
		if (a1[i] == a2[j])
		{
			j++;
		}
		else 
		{
			j = 0;
		}
		if (j == n2)
		{
			return i - n2 + 1;
		}
	}
	return -1;
}

int locateAny(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 < 0 || n2 < 0)
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
	if (n < 0)
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
		{
			j--;
		}
		else if (a[j] < separator)
		{
			i++;
		} 
		else
		{
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
	string h[7] = { "moana", "mulan", "ariel", "tiana", "", "belle", "elsa" };
	assert(locate(h, 7, "belle") == 5);
	assert(locate(h, 7, "ariel") == 2);
	assert(locate(h, 2, "ariel") == -1);
	assert(locationOfMax(h, 7) == 3);

	string g[4] = { "moana", "mulan", "belle", "raya" };
	assert(locateDifference(h, 4, g, 4) == 2);
	assert(circleLeft(g, 4, 1) == 1 && g[1] == "belle" && g[3] == "mulan");

	string c[4] = { "ma", "can", "tu", "do" };
	assert(reduplicate(c, 4) == 4 && c[0] == "mama" && c[3] == "dodo");

	string e[4] = { "ariel", "tiana", "", "belle" };
	assert(subsequence(h, 7, e, 4) == 2);

	string d[5] = { "mulan", "mulan", "mulan", "belle", "belle" };
	assert(enumerateRuns(d, 5) == 2);

	string f[3] = { "tiana", "ariel", "raya" };
	assert(locateAny(h, 7, f, 3) == 2);
	assert(flip(f, 3) == 3 && f[0] == "raya" && f[2] == "tiana");

	assert(separate(h, 7, "elsa") == 3);

	cout << "All tests succeeded" << endl;
}