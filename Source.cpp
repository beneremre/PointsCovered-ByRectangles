#include <iostream>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include "Header.h"

using namespace std;


void EMRE()
{
	ifstream infile; //file opening
	infile.open("rectdb.txt");
	string line = ""; //this is for getting strings from txt file

	int x=0, y=0, z=0, w=0; //top-left-bottom-right in a row
	getline(infile,line);
	istringstream ss(line);
	ss>>x>>y>>z>>w;
	
	TwoDimTreeNode tree(x,y,z,w); //creating root node
	TwoDimTreeNode* root = new TwoDimTreeNode;
	root = &tree; // keeping the adress of node

	while(getline(infile,line))
	{	
		istringstream ss(line);
		ss>>x>>y>>z>>w;
		if(x < 0 || y < 0 || z < 0 || w < 0)
			break;
		Rectangle getReqt(x,y,z,w);	// rectangles to insert
		tree.Insert(getReqt,root);
	}
	int inputX,inputY;//query points
	cout << "Please enter the query point \n ";
	while(cin>>inputX>>inputY)
	{
		int count=0;
		vector<Rectangle>searcher; // vector to keep the info of how many rectangles intersects
		int a = tree.search(inputX,inputY,count,searcher); //count of rectangles
		cout << a << endl;
		for(unsigned int search=0; search < searcher.size();search++)
		cout << searcher[search].getTop() << " " << searcher[search].getLeft() << " " << searcher[search].getBottom() << " " << searcher[search].getRight() << endl;
	}
}

int main()
{
	EMRE();
	return 0;
}