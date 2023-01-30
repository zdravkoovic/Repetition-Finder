#include <iostream>
#include "AHT.h"
#include "Repetition.h"
#include "Keys.h"
#include <fstream>

using namespace std;

void PutString(Keys* keys, Repetition* rep, AHT* aht);

int main()
{
	AHT aht;
	//aht.PutData((char*)"test.txt");
	//aht.DisplayCode();
	Keys keys;
	Repetition rep;
	//rep.proba();
	PutString(&keys, &rep, &aht);

	return 0;
}

void PutString(Keys* keys, Repetition* rep, AHT* aht)
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
			if(/*rep->yi[j] >= j + 1*/ i > -1) 
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
	aht->Encoding(p);
	zaHuffmana[index++] = p;
	in.close();
	for (int i = 0; i < index; i++) {
		keys->PutCode(false, aht->GetCode(zaHuffmana[i]), zaHuffmana[i]);
		cout << zaHuffmana[i] << " ";
	}
	for (int i = 0; i < j; i++) {
		cout << hr[i] << " ";
	}
	cout << endl;
	ifstream citaj("test.txt");
	int i = 0;
	j = 1;
	bool escape = false;
	repetitionExit = false;
	if (citaj.good()) {
		while (!citaj.eof())
		{
			char c = citaj.get();
			if (c == -1)
				break;
			
			if (rep->yi[i] < i && !repetitionExit)
			{
				repetitionExit = true;
				cout << keys->repetition[rep->yi[i]] << "(" << keys->GetCharacter(true, keys->repetition[rep->yi[i]]) << ") ";
				//citaj.get();
				//i++;
			}
			else {
				if (repetitionExit) {
					repetitionExit = false;
					//cout << "~ ";
				}
				cout << aht->GetCode(c) << " ";
			}
			i++;
			j++;
		}
	}
	citaj.close();
}