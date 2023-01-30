#include <iostream>

using namespace std;

class Repetition
{
public:
	Repetition();
	Repetition(char* data);
	int GenerateY(char c);
	bool isRepetition();
	char* GenerateCode(int num);
	void proba();
	int* yi;
	int ind;
	char** ximin1xi;
private:
	bool repetition;
};