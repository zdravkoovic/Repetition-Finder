#include "AHT.h"

AHT::AHT()
	: root(new Node(-1, 0, 512, nullptr, nullptr, nullptr, true))
{
	NYTNode = root;
	this->word = new char;
}

AHT::~AHT()
{

}

Node* AHT::GetDataNode(int data, Node* node)
{
	if (node == nullptr || node->data == data) return node;

	Node* current = GetDataNode(data, node->left);
    return current == nullptr ? GetDataNode(data, node->right) : current;
}

void AHT::FindPotentialSwap(Node* node1, Node* &node2)
{
	if (node1 == nullptr || node2 == root)
	{
		return;
	}

	if (node1->weight == node2->weight && node1 != node2->parent && node1->order > node2->order)
	{
		node2 = node1;
	}

	FindPotentialSwap(node1->left, node2);
	FindPotentialSwap(node1->right, node2);
}

void AHT::SwapNodes(Node* first, Node* second)
{
	if (first->parent == nullptr || second->parent == nullptr) return;

	if (first->parent == second || second->parent == first) return;

	Node*& firstRef = first->parent->left == first ? first->parent->left : first->parent->right;
	Node*& secondRef = second->parent->left == second ? second->parent->left : second->parent->right;

	std::swap(firstRef, secondRef);
	std::swap(firstRef->parent, secondRef->parent);
	std::swap(firstRef->order, secondRef->order);
}

string AHT::GetCode(Node* node, Node* result, string code)
{
	if (node == result)
	{
		return code;
	}
	if (node == nullptr)
	{
		return "";
	}

	string left = GetCode(node->left, result, code + "0");
	return left != "" ? left : GetCode(node->right, result, code + "1");
}

void AHT::SlideAndIncrement(Node* node)
{
	if (node == nullptr)
	{
		return;
	}

	Node* potentional = node;
	FindPotentialSwap(root, potentional);
	if (potentional != node)
	{
		SwapNodes(potentional, node);
	}

	++node->weight;
	SlideAndIncrement(node->parent);
}

void AHT::UpdateTree(int data)
{
	Node* node = GetDataNode(data, root);

	if (node == nullptr)
	{
		NYTNode->isNYT = false;
		int currentMinOrder = NYTNode->order;
		NYTNode->left = new Node(-1, 0, currentMinOrder - 2, nullptr, nullptr, NYTNode, true);
		NYTNode->right = new Node(data, 0, currentMinOrder - 1, nullptr, nullptr, NYTNode, false);
		node = NYTNode->right;
		NYTNode = NYTNode->left;
	}

	SlideAndIncrement(node);
}

void AHT::Encoding(int data)
{
	Node* symbolNode = GetDataNode(data, root);
	if (symbolNode != nullptr)
	{
		string result = GetCode(root, symbolNode, "");
		UpdateTree(data);
	}
	else UpdateTree(data);
}

char* AHT::GetCode(char data)
{
	char* ret = new char;
	strcpy(ret, GetCode(root, GetDataNode(data, root), "").c_str());
	return ret;
}

void AHT::PutData(char* fileName)
{
	/*ifstream in(fileName);
	int i = 0;
	if (in.good()) {
		while (!in.eof())
		{
			this->word[i] = (char)in.get();
			Encoding(word[i]);
			i++;
		}
		this->word[i] = '\0';
	}
	in.close();*/
}
