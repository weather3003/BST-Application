/* This header contains the data type definitions for a user-defined Binary 
Search Tree ADT that will be implemented as a dynamic linked list.
*/
#include <string>
using namespace std;

struct Node;

typedef struct Criminal
{
	string name;
	string attributes[8];
	int attributeCount;

	//default constructor for Criminal
	Criminal::Criminal()
	{
		name = "";
		for (int i = 0; i< 8; i++) attributes[i] = "";
		attributeCount = 0;
	}

	//constructor for criminal
	Criminal::Criminal(string info)
	{
		name = "";
		for (int i = 0; i< 8; i++) attributes[i] = "";
		attributeCount = 0;

		istringstream stream(info);
		stream >> name;
		for (int i = 0; !stream.eof(); i++)
		{
			stream >> attributes[i];
			attributeCount++;
		}
		attributeCount--;
	}

	//returns 1 if the passed in criminal is greater; 0 if not
	int Criminal::compare(Criminal other)
	{
		if (name.compare(other.name) > 0)
			return 1;
		else
			return 0;
	}

} DataType; //Change custom type here


class BST
{
public:
	BST();
	~BST();

	bool Insert(DataType);
	void PruneTree(DataType);
	void Print(string);

private:
	Node * root;
};