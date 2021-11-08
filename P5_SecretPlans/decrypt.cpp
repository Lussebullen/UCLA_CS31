#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <cstring>
#include <cassert>
#include<cctype>
using namespace std;

const int MAX_CHARS = 90;			// Max amount of chars in a line
const int MAXLINES = 71;
const int MAXSIZE = MAX_CHARS * MAXLINES + 1;	// Max amount of input characters including '\0'

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
	Word forms[MAX_CHARS / 2];									// Contains each word
	while (i < n)
	{
		while (sentence[i] != '\0' && !isalpha(sentence[i]))	// Pass all non alphabetical characters
		{
			i++;
		}
		Word tmpWord;
		tmpWord.Loc = i;
		count = 0;
		while (sentence[i] != '\0' && isalpha(sentence[i]))		// Count consecutive alphabetical characters
		{
			count++;
			i++;
		}
		if (count > 0)											// Add the word to the array
		{
			tmpWord.Length = count;
			forms[wordCount] = tmpWord;
			wordCount++;
		}
		
	}
	SentenceForm result;										// Contains array of words, and amount of words.
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
		else
		{
			j++;
		}
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
bool findKey(char cribstring[], char cipherstring[], char original[], char key[])
{	
	int n = strlen(cribstring);
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		if (strchr(original, cribstring[i]) == NULL && strchr(key, cipherstring[i]) == NULL)
		{	// input original letters at their corresponding index, and key letters at same index, we now have a mapping.
			int index = cipherstring[i] - 'a';
			original[index] = cribstring[i];
			key[index] = cipherstring[i];
			count++;
		}
		else if (strchr(original, cribstring[i]) != NULL && strchr(key, cipherstring[i]) != NULL)
		{

		}
		else
		{
			return false;
		}
	}
	return true; //FIXME
}

void combineWords(const char sentence[], char target[])
{	// Combines the sentence form from sentence into a single word, and copies it to target.
	int n = strlen(sentence);
	char continuous[MAX_CHARS];			//only letters in string
	int count = 0;

	for (int i = 0; i < n; i++)
	{
		if (isalpha(sentence[i]))
		{
			continuous[count] = sentence[i];
			count++;
		}
	}
	continuous[count] = '\0';

	strcpy(target, continuous);
}

bool lineMatch(char cribcontinuous[], SentenceForm cribForm, char cipherline[], char original[], char key[])
{
	SentenceForm cipherForm;
	cipherForm = findForm(cipherline);						//FIXME: Do this per line

	int words = cribForm.Length;							// # of words in crib to check	
	IntVector matches = formMatch(cipherForm, cribForm);

	for (int i = 0; i < matches.Length; i++)				// Try all possible matches
	{

		int wordNumber = matches.Values[i];					// word# for first matching word
		int matchStartIndex = cipherForm.Words[wordNumber].Loc;
		int matchEndIndex = cipherForm.Words[wordNumber + words - 1].Loc +
			cipherForm.Words[wordNumber + words - 1].Length;

		char* matchStart = &cipherline[matchStartIndex];					// Pointer to start of where string matches
		char cipherMatch[MAX_CHARS] = {};									// Initialize so concaternate works
		strncat(cipherMatch, matchStart, matchEndIndex - matchStartIndex);	//copy over the matching portion to a new string.

		char cipherMatchContinuous[MAX_CHARS] = {};
		combineWords(cipherMatch, cipherMatchContinuous);

		// Check for whether decryption possible
		bool decrypted = findKey(cribcontinuous, cipherMatchContinuous, original, key);

		if (decrypted)
		{
			return true;
		}
	}
	return false;
}

bool decrypt(const char ciphertext[], const char crib[])
{
	// FIXME: Include error handling
	
	SentenceForm cribForm = findForm(crib);
	// If no crib, decryption impossible, false returned.
	if (cribForm.Length == 0)
	{
		return false;
	}
	
	// Turn crib words into contiguous string of lower case alphabetical characters
	char cribcontinuous[MAX_CHARS];							
	combineWords(crib, cribcontinuous);	
	for (int i = 0; i < strlen(cribcontinuous); i++)	
	{	
		cribcontinuous[i] = tolower(cribcontinuous[i]);
	}

	// non const lower case version of ciphertext for pointer references
	char ciphercpy[MAXSIZE];							
	strcpy(ciphercpy, ciphertext);
	for (int i = 0; i < strlen(ciphercpy); i++)			
	{
		ciphercpy[i] = tolower(ciphercpy[i]);
	}

	// Loop all lines in ciphertext
	int startIndex = 0;
	int endIndex = 0;
	int j = 0;
	for (int _ = 0; _ < MAXLINES; _++)
	{
		while (ciphertext[j] != '\0' && ciphertext[j] != '\n')
		{
			endIndex++;
			j++;
		}
		// Construct cipherline
		char cipherline[MAX_CHARS + 1];
		char* ptr = &ciphercpy[startIndex];
		strncpy(cipherline, ptr, endIndex - startIndex);
		cipherline[endIndex - startIndex] = '\0';

		// Check if cipherline can be decrypted with crib, if so return true
		
		// Arrays to hold original and key letter pairs, initialize with specific values to avoid undefined behaviour.
		char original[27] = "00000000000000000000000000";
		char key[27] = "00000000000000000000000000";

		bool decrypt = lineMatch(cribcontinuous, cribForm, cipherline, original, key);
		// If decryption possible replace letters using keypairs.
		if (decrypt)
		{
			for (int i = 0; i < strlen(ciphercpy); i++)
			{
				if (isalpha(ciphercpy[i]) && strchr(key, ciphercpy[i]) != NULL)
				{
					ciphercpy[i] = toupper(original[ciphercpy[i] - 'a']);
				}
			}
			// Remove possible obsolete newline //FIXME - is this necessary, inconsistent example
			if (ciphercpy[strlen(ciphercpy) - 1] == '\n')
			{
				ciphercpy[strlen(ciphercpy) - 1] = '\0';
			}
			cout << ciphercpy << endl;
			return true;
		}

		if (ciphertext[j] == '\0')
		{
			break;
		}
		j++;
		startIndex = j;
		endIndex = startIndex;
	}
	
	// If no line could be decrypted return false
	return false;
}

void runtest(const char ciphertext[], const char crib[])
{
	cout << "====== " << crib << endl;
	bool result = decrypt(ciphertext, crib);
	cout << "Return value: " << result << endl << endl;
}

int main()
{
	cout.setf(ios::boolalpha); // output bools as "true"/"false"

	runtest("Hirdd ejsy zu drvtry od.\nO'z fodvtrry.\n", "my secret");
	runtest("Hirdd ejsy zu drvtry od.\nO'z fodvtrry.\n", "shadow");
	runtest("Rswjo qgx Tmeuo sgjsy jds vqgf vo jds vqzf xbby.\nUdbyjo iqcju cg wybgj cg jds esjqiqo zqy\nXbg'j rsj jds jsrrsy jycn jds ucrsgj qrqyt.\nZU 31 cu zdqrrsgecge!","silent alarm");
	runtest(" a ", "    0L");
	runtest(" a ", "    0");   // degenerate case
	runtest("", "");	// Gives false as intended
	runtest("", "a");	// -||-
	runtest("a", "");	// degenerate case
	runtest("F gspt fe! zyxZYXzyx--Abca abCa    bdefg## $$dsptrqtj6437 wvuWVUwvu", "   hush???hUSh---     --- until    NovemBER !!  ");
	runtest("F gspt fe! zyxZYXzyx--Abca abCa    bdefg## $$dsptrqtj6437 wvuWVUwvu", "hush-hush until November 25, 2021");
	runtest("F gspt fe! zyxZYXzyx--Abca abCa    bdefg## $$dsptrqtj6437 wvuWVUwvu", "hush hush until november");
	// ASK ABOUT FINAL NEWLINE HANDLING
}