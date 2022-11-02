/*
Matt Burton
csc1720
01/19/21
~/csc1720/programs/prog1/main.cpp

Read input text from a document and counter the characters, vowels, sentences, wordiest sentence, and track the wordiest sentence using the counterType class

to compile use 
	g++ -Wall main.cpp counterType.cpp

to run use 
	./a.out<FILE_NAME_HERE.txt
*/
#include "counterType.h"
#include <stdio.h>
#include <ctype.h>
#include <iostream>
using namespace std;

void printStats(counterType chars, counterType vowels, counterType sentences, counterType wordsInSentence, counterType mostWordsInSentence, counterType wordySenetenceNum);

int main()
{
	counterType chars, vowels, sentences, wordsInSentence, mostWordsInSentence, wordySentenceNum;
	char a;

   while (cin.get(a))
	{	
		chars.incrementCounter();

		switch(a)
		{
			case 'a':
			case 'A':
			case 'e':
			case 'E':
			case 'i':
			case 'I':
			case 'o':
			case 'O':
			case 'u':
			case 'U':
				vowels.incrementCounter();
				break;
			case '.':
					sentences.incrementCounter();
					wordsInSentence.setCounter(1);
				break;
			case ' ':
				wordsInSentence.incrementCounter();
				break;
		}

		if (wordsInSentence.getCounter() > mostWordsInSentence.getCounter())
		{
			mostWordsInSentence.setCounter(wordsInSentence.getCounter());
			wordySentenceNum.setCounter(sentences.getCounter());
		}

	}
	printStats(chars, vowels, sentences, wordsInSentence, mostWordsInSentence, wordySentenceNum);
	return 0;
}

void printStats(counterType chars, counterType vowels, counterType sentences, counterType wordsInSentence, counterType mostWordsInSentence, counterType wordySentenceNum)
{	
   wordySentenceNum.incrementCounter();
	mostWordsInSentence.decrementCounter();

	cout << "Number of chars: " << chars.getCounter() << endl;
	cout << "Number of vowels: " << vowels.getCounter() << endl;
	cout << "Number of sentences: " << sentences.getCounter() << endl;
	cout << "Sentence with most words: #" << wordySentenceNum.getCounter() << endl;
	cout << "Number of words in longest sentence: " << mostWordsInSentence.getCounter() << endl;


}
