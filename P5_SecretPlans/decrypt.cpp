#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <cstring>
#include <cassert>
#include<cctype>
using namespace std;

const int MAX_CHARS = 90;			// Max amount of chars in a line
const int MAXSIZE = 90 * 71 + 1;	// Max amount of input characters including '\0'

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

	for (int i = 0; i < n; i++)
	{	// to lower case
		cribstring[i] = tolower(cribstring[i]);
		cipherstring[i] = tolower(cipherstring[i]);
	}
	
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		if (strchr(original, cribstring[i]) == NULL && strchr(key, cipherstring[i]) == NULL)
		{	// input original letters at their corresponding index, and key letters at same index, we now have a mapping.
			original[cipherstring[i] - 'a'] = cribstring[i];
			key[cipherstring[i] - 'a'] = cipherstring[i];
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

bool lineMatch(char cribcontinuous[], char cipherline[])
{

}

bool decrypt(const char ciphertext[], const char crib[])
{
	// FIXME: Include error handling
	
	SentenceForm cribForm = findForm(crib);
	
	char cribcontinuous[MAX_CHARS];						//only letters in string after calling combineWords				
	combineWords(crib, cribcontinuous);	
	for (int i = 0; i < strlen(cribcontinuous); i++)	// Turn lower case
	{	
		cribcontinuous[i] = tolower(cribcontinuous[i]);
	}

	SentenceForm cipherForm;
	cipherForm = findForm(ciphertext);					//FIXME: Do this per line
	
	int words = cribForm.Length;						// # of words in crib to check	
	IntVector matches = formMatch(cipherForm, cribForm);

	char ciphercpy[MAX_CHARS];							// non const version of ciphertxt for pointer references
	strcpy(ciphercpy, ciphertext);
	for (int i = 0; i < strlen(ciphercpy); i++)			// Turn lower case
	{
		ciphercpy[i] = tolower(ciphercpy[i]);
	}

	for (int i = 0; i < matches.Length; i++)			// Try all possible matches
	{	

		int wordNumber = matches.Values[i];				// word# for first matching word
		int matchStartIndex = cipherForm.Words[wordNumber].Loc;
		int matchEndIndex = cipherForm.Words[wordNumber + words - 1].Loc +
			cipherForm.Words[wordNumber + words - 1].Length;

		char* matchStart = &ciphercpy[matchStartIndex];					// Pointer to start of where string matches
		char cipherMatch[MAX_CHARS] = {};								// Initialize so concaternate works
		strncat(cipherMatch,matchStart,matchEndIndex-matchStartIndex);	//copy over the matching portion to a new string.

		char cipherMatchContinuous[MAX_CHARS] = {};
		combineWords(cipherMatch, cipherMatchContinuous);
		cout << "Ciph: " << cipherMatchContinuous << endl;

		// Check for whether decryption possible
		// Arrays to hold original and key letter pairs
		char original[26];
		char key[26];
		original[25] = '\0';
		key[25] = '\0';
		bool decrypted = findKey(cribcontinuous,cipherMatchContinuous, original, key);
		cout << "Decrypted: " << decrypted << endl;
		cout << "Val: " << original << endl;
		cout << "Key: " << key << endl;
		if (decrypted)
		{
			for (int i = 0; i < strlen(ciphercpy); i++)
			{
				if (isalpha(ciphercpy[i]) && strchr(key, ciphercpy[i]) != NULL)
				{
					ciphercpy[i] = toupper(original[ciphercpy[i] - 'a']);
				}
			}
			cout << ciphercpy << endl;
			return true;
		}
		
	}

	return false;
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
	//cout << "crib" << endl;
	for (int i = 0; i < form.Length; i++)
	{
		//cout << form.Words[i].Length << endl;
	}
	//cout << "ciph" << endl;
	for (int i = 0; i < formciph.Length; i++)
	{
		//cout << formciph.Words[i].Length << endl;
	}
	IntVector matches = formMatch(formciph, form);
	for (int i = 0; i < matches.Length; i++)
	{
		//cout << "Match at word: ";
		//cout << matches.Values[i] << endl;
	}
	//decrypt("aba fd sa ifdsaaaa ay aysaufd fd  ifd 87 aa!bb!)hbbsasdd33j", "123!@cow ea8ts --assgrass");
	decrypt("F gspt fe! zyxZYXzyx--Abca abCa    bdefg## $$dsptrqtj6437 wvuWVUwvu","   hush???hUSh---     --- until    NovemBER !!  ");
}