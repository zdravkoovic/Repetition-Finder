#include <iostream>

using namespace std;

class Keys
{
public:
	Keys();
	~Keys();
	void PutCode(bool rep, char* code, int index, char* data = nullptr);
	char* GetCharacter(bool rep, char* code);
public:
	char** huffman, ** repetition, ** repCharacters;
};

Keys::Keys()
{
	this->huffman = new char* [1000];
	this->repetition = new char* [1000]; 
	this->repCharacters = new char* [1000];
	for (int i = 0; i < 1000; i++) {
		this->huffman[i] = new char;
		this->repetition[i] = new char;
		this->repCharacters[i] = new char;
	}
}

Keys::~Keys()
{
	for (int i = 0; i < 1000; i++) {
		delete this->huffman[i], this->repetition[i], this->repCharacters;
	}
	delete[] this->huffman, this->repetition, repCharacters;
}

inline void Keys::PutCode(bool rep, char* code, int index, char* data)
{
	if (rep) {
		this->repetition[index] = code;
		this->repCharacters[index] = data;
	}
	else {
		this->huffman[index] = code;
	}
}

inline char* Keys::GetCharacter(bool rep, char* code)
{
	if (rep) {
		int i = 0;
		while (strcmp(code, this->repetition[i])) {
			i++;
		}
		return this->repCharacters[i];
	}
	else {
		int i = 0;
		while (!strcmp(code, this->huffman[i])) {
			i++;
		}
		return (char*)i;
	}
}
