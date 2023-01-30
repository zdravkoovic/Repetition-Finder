#include <iostream>
#include "Node.h"
#include <string>

using namespace std;

class AHT
{
public:
	AHT();
	~AHT();
	Node* GetDataNode(int data, Node* node);
	void FindPotentialSwap(Node* node1, Node* &node2);
	void SwapNodes(Node* node1, Node* node2);
	string GetCode(Node* node1, Node* node2, string code);
	void SlideAndIncrement(Node* node);
	void UpdateTree(int data);
	void Encoding(int data);
	char* GetCode(char data);
	void PutData(char* data);
private:
	Node* root, * NYTNode;
	char* word;
};
