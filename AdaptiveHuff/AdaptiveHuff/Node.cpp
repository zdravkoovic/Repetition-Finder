#include "Node.h"

Node::Node()
	:data(0), weight(0), order(0), left(nullptr), right(nullptr), parent(nullptr), isNYT(false)
{}

Node::Node(int value, int weight, int order, Node* left, Node* right, Node* parent, bool isNYT)
	: data(value), weight(weight), order(order), left(left), right(right), parent(parent), isNYT(isNYT)
{}

Node::Node(bool isNYT, int value)
	: Node()
{
	this->isNYT = isNYT;
	this->data = value;
}

Node::~Node()
{
}
