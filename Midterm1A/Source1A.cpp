#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main()
{
    string line;
    getline(cin, line);
    int len = static_cast<int>(line.size());
    int count = 0;
    for (int i = 0; i < len - 1; i++)
    {
        if (isupper(line.at(i)) && islower(line.at(i + 1)))
        {
            count++;
        }
    }
    cout << count << endl;
}