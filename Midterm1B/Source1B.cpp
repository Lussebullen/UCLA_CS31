#include <iostream>
#include <string>
using namespace std;

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AT THE END OF THE wedge FUNCTION

void wedge(string s)
{
    int len = static_cast<int>(s.size());
    for (int i = 0; i < len; i++)
    {
        for (int k = 0; k < len - i - 1; k++)
        {
            cout << '@';
        }
        if (s.at(i) == '@')
        {
            cout << '#';
        }
        else
        {
            cout << s.at(i);
        }
        cout << endl;
    }
}

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AT THE START OF THE wedge FUNCTION

int main()
{
    cout << "======= Test 1:" << endl;
    wedge("Wow!");
    cout << "======= Test 2:" << endl;
    wedge("CS@UCLA #1");
    cout << "======= Test 3:" << endl;
    wedge("");
    cout << "======= Test 4:" << endl;
    wedge("g");
}