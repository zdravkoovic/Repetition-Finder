#include <iostream>

using namespace std;

class Node
{
public:
	Node();
	Node(int value, int weight, int order, Node* left, Node* right, Node* parent, bool isNYT = false);
	Node(bool isNYT, int value);
	~Node();
	friend class AHT;
private:
	int data, weight, order;
	Node* parent,* left,* right;
	bool isNYT;
};