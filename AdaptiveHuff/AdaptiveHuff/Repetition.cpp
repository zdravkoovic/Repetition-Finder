#include "Repetition.h"
#include <string>
#include <fstream>

Repetition::Repetition()
{
	//this->xi = new char;
	this->yi = new int;
	yi[0] = 1;
	yi[1] = 2;
	this->ximin1xi = new char* [1024];
	for (int i = 0; i < 26 * 26; i++) {
		this->ximin1xi[i] = new char;
		this->ximin1xi[i][0] = '\0';
	}
	ximin1xi[0][0] = ' ';
	ximin1xi[0][1] = ' ';
	ximin1xi[0][2] = '\0';
	ind = 1;
	this->repetition = false;
}

Repetition::Repetition(char* data)
{
	/*this->xi = data;
	int length = strlen(xi);
	this->yi = new int[length-1];

	*ximin1xi = new char;
	strcpy(*ximin1xi, "");
	char* pom = new char[2];
	int j = 0;
	for (int i = 0; i < length-1; i++) {
		*ximin1xi[j++] = xi[i];
		*ximin1xi[j++] = xi[i+1];
	}
	bool repeat = false;
	for (int i = 0; i < length; i++) {
		if (i == 0) yi[i] = 1;
		else {
			int j = 0;
			while(j < (i-1)*2 && !repeat) {
				if (*ximin1xi[j] == *ximin1xi[(i-1)*2] && ximin1xi[j + 1] == ximin1xi[(i-1)*2 + 1]) repeat = true;
				else j += 2;
			}
			if (repeat) {
				yi[i] = ((i-1)*2 - j)/2;
				repeat = false;
			}
			else {
				yi[i] = i + 1;
			}
		}
	}*/
}



int Repetition::GenerateY(char c)
{
	int br = -1;
	this->repetition = false;
	if (ind == 1)
	{
		int i = strlen(ximin1xi[1]);
		ximin1xi[ind][i] = c;
		ximin1xi[ind][i + 1] = '\0';
		if (i == 1) ind++;
	}
	else {
		yi[ind] = ind + 1;
		ximin1xi[ind][0] = ximin1xi[ind - 1][1];
		ximin1xi[ind][1] = c;
		ximin1xi[ind][2] = '\0';
		for (int i = 0; i < ind; i++) {
			if (!strcmp(ximin1xi[i], ximin1xi[ind]))
			{
				yi[ind] = i + 1;
				this->repetition = true;
				br = ind - yi[ind] + 1;
				break;
			}
		}
		ind++;
	}
	return br;
}

bool Repetition::isRepetition()
{
	return this->repetition;
}

char* Repetition::GenerateCode(int num)
{
	char binaryNum[1000];
	char* retChar = new char;

	if (num == 0) {
		retChar[0] = '0';
		retChar[1] = '\0';
		return retChar;
	}
	// counter for binary array
	int i = 0;
	while (num > 0) {

		// storing remainder in binary array
		binaryNum[i] = num % 2 + '0';
		num = num / 2;
		i++;
	}
	i--;
	// printing binary array in reverse order
	retChar[0] = '\0';
	for (int j = i; j >= 0; j--)
		retChar[i - j] = binaryNum[j];
	retChar[i + 1] = '\0';
	return retChar;
}


void Repetition::proba()
{
	ifstream in("test.txt");
	int i = 0;
	if (in.good()) {
		while (!in.eof())
		{
			GenerateY((char)in.get());
		}
	}
	in.close();
}


