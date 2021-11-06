#include <iostream>
#include <cstring>
#include <cassert>
#include<cctype>
using namespace std;

const int MAX_CHARS = 90;
/*
void runtest(const char ciphertext[], const char crib[])
{
	cout << "====== " << crib << endl;
	bool result = decrypt(ciphertext, crib);
	cout << "Return value: " << result << endl;
}
*/

struct Word
{
	int Length;
	int Loc;
};

struct SentenceForm
{
	int Length;
	Word Words[MAX_CHARS / 2];
};

SentenceForm findForm(const char sentence[])
{	// Construct summary of sentence shape
	int n = strlen(sentence);
	int i = 0;
	int count = 0;
	int wordCount = 0;
	Word forms[MAX_CHARS / 2];			//Contains each word
	while (i < n)
	{
		while (!isalpha(sentence[i]))	//Pass all non alphabetical characters
		{
			i++;
		}
		Word tmpWord;
		tmpWord.Loc = i;
		count = 0;
		while (isalpha(sentence[i]))	//Count consecutive alphabetical characters
		{
			count++;
			i++;
		}
		tmpWord.Length = count;
		forms[wordCount] = tmpWord;
		wordCount++;
	}
	SentenceForm result;				//Contains array of words, and amount of words.
	result.Length = wordCount;
	for (int i = 0; i < wordCount; i++)
	{
		result.Words[i] = forms[i];
	}
	return result;
}

int formMatch(const char cipherline[], const char crib[])
{	// returns start word of form match or -1 if no match


	return -1;
}

char* formcheck(const char cipherline[], const char crib[])	// FIXME: datatype
{ // Return pointer to first instance of a form fit of crib in a line of ciphertext
	int nl = strlen(cipherline);
	int nc = strlen(crib);
	if (nc > MAX_CHARS)
	{
		return nullptr;
	}

	Word sentenceFormCipher[MAX_CHARS / 2];
	SentenceForm sentenceFormCrib = findForm(crib);
	// Construct summary of crib sentence shape


	return nullptr;
}

int main()
{
	/*
	cout.setf(ios::boolalpha); // output bools as "true"/"false"

	runtest("Hirdd ejsy zu drvtry od.\nO'z fodvtrry.\n", "my secret");
	runtest("Hirdd ejsy zu drvtry od.\nO'z fodvtrry.\n", "shadow");
	*/
	formcheck("asdsa", "123!@cow ea8ts --assgrass");
	SentenceForm form = findForm("123!@cow ea8ts --assgrass");
	cout << "Number of words: " << form.Length << endl;
	cout << "Word lengths:" << endl;
	for (int i = 0; i < form.Length; i++)
	{
		cout << form.Words[i].Length << endl;
	}
}