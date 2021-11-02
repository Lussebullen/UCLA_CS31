#include <iostream>
#include <string>
using namespace std;

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AT THE END OF THE box FUNCTION

void box(string s, int interval)
{
    int len = static_cast<int>(s.size());
    for (int i = 0; i < interval; i++)
    {
        int k = i;
        while (k < len) 
        {
            cout << s.at(k);
            k += interval;
        }
        cout << endl;
    }
}

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AT THE START OF THE box FUNCTION

int main()
{
    cout << "======= Test 1:" << endl;
    box("abcdef @3xwvutsrq", 5);
    cout << "======= Test 2:" << endl;
    box("#", 3);
    cout << "======= Test 3:" << endl;
    box("", 5);
    cout << "======= Test 4:" << endl;
    box("ababababababab", 2);
    cout << "======= Test 5:" << endl;
    box("ababababababab", 0);
    cout << "======= Test 6:" << endl;
    box("ababababababab", -2);
    cout << "All tests completed" << endl;
}