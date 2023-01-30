#include <iostream>
#include "AHT.h"
#include "Repetition.h"
#include "Keys.h"
#include <fstream>
//
using namespace std;
//
void Compression(Keys* &keys, Repetition* rep, AHT* aht, char** codes, int& ic);
void Decopression(Keys* keys, char** codes, int ic);
//
int main()
{
	char** codes;
	int ic;
	codes = new char* [1000];
	AHT* aht = new AHT;
	//aht.PutData((char*)"test.txt");
	//aht.DisplayCode();
	Keys* keys = new Keys;
	Repetition* rep = new Repetition;
	//rep.proba();
	Compression(keys, rep, aht, codes, ic);
	Decopression(keys, codes, ic);

	return 0;
}
//
void Compression(Keys* &keys, Repetition* rep, AHT* aht, char** codes, int& ic)
{
	ifstream in("test.txt");
	char p = '\0';
	bool repetitionExit = false;
	int j = 0;
	int index = 0;
	char zaHuffmana[1000];
	int hr[1000];
	if (in.good()) {
		while (!in.eof()) {
			char c = in.get();
			if (c == -1)
				break;
			int i = rep->GenerateY(c);
			if(i > -1) 
				keys->PutCode(true, rep->GenerateCode(rep->yi[j]), rep->yi[j], rep->ximin1xi[j]);
			if (rep->isRepetition() && !repetitionExit)
			{
				repetitionExit = true;
				hr[j - 1] = 1;
				hr[j] = 0;
			}
			else {
				if (p != '\0') {
					if (repetitionExit) {
						repetitionExit = false;
					}
					else
					{
						aht->Encoding(p);
						zaHuffmana[index++] = p;
					}
				}
				hr[j] = 0;
			}
			p = c;
			j++;
		}
	}
	int numOfChar = j;
	aht->Encoding(p);
	zaHuffmana[index++] = p;
	in.close();
	for (int i = 0; i < index; i++) {
		keys->PutCode(false, aht->GetCode(zaHuffmana[i]), zaHuffmana[i]);
	}
	ifstream citaj("test.txt");
	int i = 0;
	j = 1;
	p = '\0';
	bool escape = false;
	ic = 0;
	char* ahtCode;
	repetitionExit = false;
	int numOfRep = 0;
	if (citaj.good()) {
		while (!citaj.eof())
		{
			char c = citaj.get();
			if (c == -1)
				break;
			
			if (rep->yi[i] < i && !repetitionExit)
			{
				codes[ic++] = (char*)"1";
				repetitionExit = true;
				codes[ic++] = keys->repetition[rep->yi[i]];
				numOfRep++;
			}
			else {
				if (p != '\0') {
					if (repetitionExit) {
						repetitionExit = false;
					}
					else {
						ahtCode = aht->GetCode(p);
						codes[ic++] = ahtCode;
					}
				}
			}
			i++;
			j++;
			p = c;
		}
	}
	citaj.close();
	codes[ic++] = aht->GetCode(p);
	int numOfBits = 0;
	for (int i = 0; i < ic; i++) {
		std::cout << codes[i];
		numOfBits+=strlen(codes[i]);
	}
	//std::cout << endl;
	//std::cout << endl;
	//std::cout << "Broj repeticija je " << numOfRep << endl;
	//std::cout << "Broj bitova je " << numOfBits << endl;
	//std::cout << "Broj karaktera je " << numOfChar << ", s' toga bez kompresije ukupan broj bitova bi bio " << numOfChar*8 << endl;
	//std::cout << endl;
	std::cout << endl;
}
void Decopression(Keys* keys, char** codes, int ic) {
	for (int i = 0; i < ic; i++) {
		if (!strcmp(codes[i], (char*)"1")) {
			i++;
			std::cout << keys->GetCharacter(true, codes[i]);
		}
		else {
			std::cout << keys->GetCharacter(false, codes[i])[0];
		}
	}
	std::cout << endl;
}