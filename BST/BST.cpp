#include <string>
#include <sstream> 
#include <iostream>
#include "BST.h"
using namespace std;

struct Node
{
	DataType data;
	Node * children[2];

	~Node()
	{
		if (children[0] != NULL) delete children[0];
		if (children[1] != NULL) delete children[1];
	}
};



BST::BST()
{
	root = NULL;
}

BST::BST(Node * ptr)
{
	root = ptr;
}

BST::~BST()
{
	delete root; 
}


bool BST::Insert(DataType newData)
{
	Node * insertion = new Node; if (!insertion) return false;
	insertion->data = newData; 
	insertion->children[0] = NULL; insertion->children[1] = NULL;

	//if tree empty 
	if (root == NULL)
		root = insertion;
	else
	{
		//tree not empty, use trailer(parent) to insert node
		Node* current = root;
		Node* parent = NULL;
		//find insertion spot, parent will point to insertion node
		while (current != NULL)
		{
			parent = current;														
			current = current->children[newData.compare(current->data)];
		}
		//graft node onto parent’s correct side
		parent->children[newData.compare(parent->data)] = insertion;					
	}
	return true;
}

