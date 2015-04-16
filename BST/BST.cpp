#include <string>
#include <sstream> 
#include <iostream>
#include <fstream> 
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

	void DeleteNode(Node* parent, int side)
	{
		if (children[0] == NULL && children[1] == NULL)
		{
			parent->children[side] = NULL;
			delete this;			//Hello?
		}
		else if (children[0] != NULL && children[1] == NULL)
		{
			parent->children[side] = children[0];
			children[0] = NULL;
			delete this;			//Hello?
		}
		else if(children[0] == NULL && children[1] != NULL)
		{
			children[1] = NULL;
			parent->children[side] = children[1];
			delete this;			//Hello?
		}
		else if (children[0] != NULL && children[1] != NULL)
		{
			DataType replacement; Node * current = children[0]; Node * parentOfCurrent = this; int i = 0;
			while (current->children[1] != NULL)
			{
				i = 1;
				parentOfCurrent = current;
				current=current->children[1];
			}
			replacement = current->data;
			current->DeleteNode(parentOfCurrent, i);
			data = replacement;
		}
	}
	Node* DeleteNode() //For the root node case
	{
		if (children[0] == NULL && children[1] == NULL)
		{
			delete this;			//Hello?
			return NULL;
		}
		else if (children[0] != NULL && children[1] == NULL)
		{
			children[0] = NULL;
			delete this;			//Hello?
			return children[0];
		}
		else if(children[0] == NULL && children[1] != NULL)
		{
			children[1] = NULL;
			delete this;			//Hello?
			return children[1];
		}
		else if (children[0] != NULL && children[1] != NULL)
		{
			DataType replacement; Node * current = children[0]; Node * parentOfCurrent = this; int i = 0;
			while (current->children[1] != NULL)
			{
				i = 1;
				parentOfCurrent = current;
				current=current->children[1];
			}
			replacement = current->data;
			current->DeleteNode(parentOfCurrent, i);
			data = replacement;
			return this;
		}
	}

	void PruneNode(DataType Case, Node * parent, int side)
	{
		if (children[0] != NULL) children[0]->PruneNode(Case, this, 0);
		if (children[1] != NULL) children[1]->PruneNode(Case, this, 1);


		for (int i = 0; i < Case.attributeCount; i++)
		{
			bool hasAttribute = false;
			for (int j = 0; j < data.attributeCount; j++)
			{
				if (data.attributes[j] == Case.attributes[i])
				{
					hasAttribute = true;
					break;
				}
			}
			if (!hasAttribute)
			{
				DeleteNode(parent, side);
				break;
			}
		}
	}
	Node* PruneNode(DataType Case) //For the root node case
	{
		for (int i = 0; i < Case.attributeCount; i++)
		{
			bool hasAttribute = false;
			for (int j = 0; j < data.attributeCount; j++)
			{
				if (data.attributes[j] == Case.attributes[i])
				{
					hasAttribute = true;
					break;
				}
			}
			if (!hasAttribute) return DeleteNode(); 
		}
		return this;
	}

	void PrintNode(string filename)
	{
		ofstream fout(filename, ios::app);
		if (children[0] != NULL) children[0]->PrintNode(filename);
		fout << data.name << endl;
		if (children[1] != NULL) children[1]->PrintNode(filename);
	}
};


//Constructor
BST::BST()
{
	root = NULL;
}

//Destructor
BST::~BST()
{
	if (!root) delete root; 
}

//Inserts an object into the tree using compare function
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

//Removes nodes that do not meet requirements
void BST::PruneTree(DataType Case)
{
	if (root != NULL && root->children[0] != NULL) root->children[0]->PruneNode(Case, root, 0);
	if (root != NULL && root->children[1] != NULL) root->children[1]->PruneNode(Case, root, 1);
	if (root != NULL) root = root->PruneNode(Case);
}

//Appends the tree to a file
void BST::Print(string filename)
{
	ofstream fout(filename, ios::app);
	if (root != NULL)
		root->PrintNode(filename);
	else
		fout << "NO SUSPECTS FOR THIS CASE" << endl;
}