#include<iostream>
#include<string>
#include<sstream> 
#include<fstream> 
#include"BST.h"
using namespace std;

//Fills a tree with criminals from a text file
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

//Fills a list with cases from a file and returns the number of cases
int populateCases(Criminal* list, string file)
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
			insertion.name = "CASE NUMBER " + to_string(i);
			list[i - 1] = insertion;
			i++;
		}
		else
		{
			cases.close();
			return i;
		}
	}
	return 0;
}

void main()
{
	ofstream clear("Criminal.out"); clear << ""; clear.close(); //Clears file
	ofstream fout("Criminal.out", ios::app);

	Criminal cases[25];
	int numberOfCases = populateCases(cases, "Casefile.txt");
	for (int i = 1; i < numberOfCases; i++)
	{
		BST criminalTree; populateTree(criminalTree, "Criminal.txt");
		criminalTree.PruneTree(cases[i-1]);

		if (i != 1) fout << endl;
		fout << cases[i-1].name << endl << "PRIME SUSPECTS ARE..." << endl;
		
		criminalTree.Print("Criminal.out");
	}

	fout.close();
}