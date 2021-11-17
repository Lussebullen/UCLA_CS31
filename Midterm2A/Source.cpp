// The next line avoids a VC++ issue; it's harmless for Xcode and g31
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cctype>
#include <cassert>
using namespace std;

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AT THE END OF THE hide FUNCTION

int hide(char s[], char ch)
{
    int n = strlen(s);
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (!isupper(s[i]) && !isdigit(s[i]))
        {
            count++;
            s[i] = ch;
        }
    }
    return count;
}

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AT THE START OF THE hide FUNCTION

int main()
{
    char text[100] = "I'm UPSET that on Nov. 16th, 2021, my 2 brand-new BMW M850is were stolen!!";
    assert(hide(text, '*') == 53);
    assert(strcmp(text, "I***UPSET*********N****16****2021*****2***********BMW*M850****************") == 0);

    strcpy(text, "#%@!");
    assert(hide(text, 'x') == 4);
    assert(strcmp(text, "xxxx") == 0);

    strcpy(text, "CS31");
    assert(hide(text, '?') == 0);
    assert(strcmp(text, "CS31") == 0);

    strcpy(text, "");
    assert(hide(text, '-') == 0);
    assert(strcmp(text, "") == 0);

    cout << "All tests succeeded" << endl;
}