#include<iostream>
#include<string>
#include<sstream> 
#include<fstream> 
#include"BST.h"
using namespace std;

void populateTree(BST& tree, string file)
{
	string currentLine = "";
	ifstream criminals(file);
	getline(criminals, currentLine);											//Gets first SUBJECT line
	
	while (!criminals.eof())
	{
		string data = "";
		getline(criminals, currentLine);										//Gets name of criminal

		if (currentLine != "FINISHED")
		{
			while (currentLine != "SUSPECT")
			{
				data += currentLine + " ";
				getline(criminals, currentLine);								//Gets attributes and subsequent SUBJECTs
			}

			Criminal insertion = Criminal(data);
			tree.Insert(insertion);
		}
		else
		{
			criminals.close();
			return;
		}
	}
}

void populateCases(Criminal* list, string file)
{
	string currentLine = "";
	ifstream cases(file);
	cases >> currentLine;											//Gets first CASE line
	int i = 1;

	while (!cases.eof())
	{
		string data = "CASE ";
		cases >> currentLine;										//Gets TIP

		if (currentLine != "FINISHED")
		{
			while (currentLine != "CASE" && currentLine != "FINISHED")
			{
				cases >> currentLine;								//Gets tip
				data += currentLine + " ";
				cases >> currentLine;								//Gets TIP or CASE
			}

			Criminal insertion = Criminal(data);
			insertion.name = "CASE NUMBER " + i;
			list[i - 1] = insertion;
			i++;
		}
		else
		{
			cases.close();
			return;
		}
	}
}

void main()
{
	BST criminalTree; Criminal cases[25];
	populateTree(criminalTree, "Criminal.dat");
	populateCases(cases, "Casefile.dat");
}