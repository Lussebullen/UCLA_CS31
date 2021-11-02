#include <iostream>
using namespace std;
#include <math.h>

bool isPalindrome(string str)
{
	int len = static_cast<int>(str.size());
	int n = len / 2;
	for (int i = 0; i < n; i++)
	{
		if (str.at(i) != str.at(len - 1 - i))
		{
			return false;
		}
	}
	return true;
}

int main()
{
	string str;
	cin >> str;
	cout << isPalindrome(str) << endl;
}