#include <iostream>
using namespace std;

string justLetters(string s)
{
    string result = "";
    for (int k = 0; k != s.size(); k++)
    {
        if (islower(s.at(k)))
            result += s.at(k);
        if (isupper(s.at(k)))
            result += tolower(s.at(k));
    }
    return result;
}

int main()
{
    cout << justLetters("CS 31's 1st lecture was Sep. 27.") << endl;
}