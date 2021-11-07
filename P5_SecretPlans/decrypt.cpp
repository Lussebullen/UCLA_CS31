#define _CRT_SECURE_NO_DEPRECATE
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

struct IntVector
{
	int Length;
	int Values[MAX_CHARS / 2];
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

IntVector formMatch(SentenceForm cipherForm, SentenceForm cribForm)
{	// returns start word of form match or -1 if no match
	int n_cipher = cipherForm.Length;
	int n_crib = cribForm.Length;
	int i = 0;
	int j = 0;
	int matchLocations[MAX_CHARS / 2];
	int count = 0;
	while (i < n_cipher)
	{
		if (cipherForm.Words[i + j].Length != cribForm.Words[j].Length)
		{
			i++;
			j = 0;
		}
		j++;
		if (j == n_crib)
		{	// all word shapes matched, ADD check if simple cipher form
			matchLocations[count] = i;
			count++;
			i++;
			j = 0;
		}
	}
	IntVector matches;
	matches.Length = count;
	for (int i = 0; i < count; i++)
	{
		matches.Values[i] = matchLocations[i];
	}
	return matches;
}
bool findKey(int n, int matchWords[], int cribWords[], const char ciphertext[], const char crib[])
{		// FIXME: Doesnt handle different case, i.e. a/A
	for (int i = 0; i < n; i++)
	{
		int locMatch = matchWords[i];
		int locCrib = cribWords[i];
		int j = 0;
		while (isalpha(crib[locCrib + j]))
		{
			if (crib[locCrib + j] != ciphertext[locMatch + j])
			{
				return false;
			}
		}

	}
	return true; //FIXME
}

void combineWords(SentenceForm form, const char sentence[], char target[])
{	// Combines the sentence form from sentence into a single word, and copies it to target.
	int n = form.Length;				// # of words

	char continuous[MAX_CHARS];			//only letters in string
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		int j = 0;
		while (form.Words[i].Loc + j < MAX_CHARS && isalpha(sentence[form.Words[i].Loc + j]))
		{
			continuous[count] = sentence[form.Words[i].Loc + j];
			count++;
			j++;
		}
		j = 0;
	}
	continuous[count] = '\0';

	strcpy(target, continuous);
}

bool decrypt(const char ciphertext[], const char crib[])
{
	// FIXME: Include error handling
	SentenceForm cribForm = findForm(crib);
	SentenceForm cipherForm;
	
	cipherForm = findForm(ciphertext);	//FIXME: Do this per line
	IntVector matches = formMatch(cipherForm, cribForm);

	char ciphercpy[MAX_CHARS];
	strcpy(ciphercpy, ciphertext);
	char cribcpy[MAX_CHARS];
	strcpy(cribcpy, crib);
	char cribcontinuous[MAX_CHARS];		//only letters in string
	int words = cribForm.Length;		// # of words in crib to check

	combineWords(cribForm, crib, cribcontinuous);
	cout << cribcontinuous << endl;
	
	for (int i = 0; i < matches.Length; i++)
	{	// Try all possible matches
		int matchWords[MAX_CHARS / 2];				// Holds starting indexes for words in specific match
		int wordNumber = matches.Values[i];			// word# for first matching word
		for (int j = 0; j < words; j++)
		{
			matchWords[j] = cipherForm.Words[j + wordNumber].Loc;
		}
		//findKey(words, matchWords, cribWords, ciphertext, crib);		// FIXME: make key function
		
	}

	return true; //FIXME
}

int main()
{
	/*
	cout.setf(ios::boolalpha); // output bools as "true"/"false"

	runtest("Hirdd ejsy zu drvtry od.\nO'z fodvtrry.\n", "my secret");
	runtest("Hirdd ejsy zu drvtry od.\nO'z fodvtrry.\n", "shadow");
	*/
	SentenceForm form = findForm("123!@cow ea8ts --assgrass");
	SentenceForm formciph = findForm("aba fd sa ifdsaaaa ay aysaufd fd  ifd 87 aa!bb!)hbbsasdd33j");
	cout << "crib" << endl;
	for (int i = 0; i < form.Length; i++)
	{
		cout << form.Words[i].Length << endl;
	}
	cout << "ciph" << endl;
	for (int i = 0; i < formciph.Length; i++)
	{
		cout << formciph.Words[i].Length << endl;
	}
	IntVector matches = formMatch(formciph, form);
	for (int i = 0; i < matches.Length; i++)
	{
		cout << "Match at word: ";
		cout << matches.Values[i] << endl;
	}
	decrypt("aba fd sa ifdsaaaa ay aysaufd fd  ifd 87 aa!bb!)hbbsasdd33j", "123!@cow ea8ts --assgrass");
}