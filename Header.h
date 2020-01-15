#ifndef HEADER_H
#define  HEADER_H
#include <vector>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;


class Rectangle
{
private:
	int top;
	int left;
	int bottom;
	int right;

public:
	Rectangle (){};
	Rectangle (int t, int l, int b, int r)
	{
		top=t;
		left=l;
		bottom=b;
		right=r;			
	};

	int Rectangle::getBottom()
	{return bottom;}

	int Rectangle::getRight()
	{return right;}

	int Rectangle::getLeft()
	{return left;}

	int Rectangle::getTop()
	{return top;}

	friend class TwoDimTreeNode;
};

class TwoDimTreeNode
{
private:
	Rectangle rec;
	vector <Rectangle> Vertical, Horizontal;
	TwoDimTreeNode *TopLeft, *TopRight, *BottomLeft, *BottomRight;

public:
	TwoDimTreeNode(){};
	TwoDimTreeNode(int a, int b, int c, int d) //constructer
	{
		Rectangle getReqt(a,b,c,d);
		rec=getReqt;
		TopLeft=NULL;
		TopRight=NULL;
		BottomLeft=NULL;
		BottomRight=NULL;
	}
	friend class Rectangle;
	void Insert(Rectangle rec, TwoDimTreeNode *root);
	int search(int input1,int input2,int &count,vector<Rectangle> &searcher);
};
void TwoDimTreeNode::Insert(Rectangle getReqt,TwoDimTreeNode* root)
 {  
	
	int centerX=(root->rec.getLeft()+root->rec.getRight())/2; //center point on x coord.
	int centerY=(root->rec.getTop()+root->rec.getBottom())/2; //center point on y coord.

	if(getReqt.getLeft() <= centerX && centerX < getReqt.getRight())
		root->Vertical.push_back(getReqt); //if any rectangle intersects with the vertical line, it pushes it to vector

	else if(getReqt.getBottom() <= centerY && centerY < getReqt.getBottom())
		root->Vertical.push_back(getReqt); //else if any rectangle intersects with the horizontal line, does the same.

	else //that means the rectangle will be on the quadrants
	{
		if(getReqt.getRight() < centerX && getReqt.getBottom() < centerY) //top left quadrant
		{
			if(root->TopLeft==NULL)
			{
				TwoDimTreeNode *leftop = new TwoDimTreeNode(root->rec.getTop(),root->rec.getLeft(),centerY,centerX);
				root->TopLeft = leftop;
			}
			Insert(getReqt,root->TopLeft); //Insert func lets us to do recursive calls
		}
		else if(getReqt.getLeft() > centerX && getReqt.getBottom() < centerY) //top right quadrant
		{
			if(root->TopRight==NULL)
			{
				TwoDimTreeNode *rightop = new TwoDimTreeNode (root->rec.getTop(),centerX,centerY,root->rec.getRight());
				root->TopRight = rightop;
			}
			Insert(getReqt,root->TopRight);
		}
		else if(getReqt.getRight() < centerX && getReqt.getTop() > centerY) //bottom left quadrant
		{
			if(root->BottomLeft == NULL)
			{
				TwoDimTreeNode *leftbottom = new TwoDimTreeNode(centerY,root->rec.getLeft(),root->rec.getBottom(),centerX);
				root->BottomLeft = leftbottom;
			}
			Insert(getReqt,root->BottomLeft);
		}
		else if(getReqt.getLeft() > centerX && getReqt.getTop () > centerY) //bottom right quadrant
		{
			if(root->BottomRight==NULL)
			{
				TwoDimTreeNode *rightbottom = new TwoDimTreeNode(centerY,centerX,root->rec.getBottom(),root->rec.getRight());
				root->BottomRight = rightbottom;
			}
			Insert(getReqt,root->BottomRight);
		}
	}
}

int TwoDimTreeNode::search(int input1, int input2,int &count,vector<Rectangle> &searcher)
{
	if(this == NULL)
		return count;
	if(this->Vertical.size() != 0) //checks whether there is vector to cout
	{
		for(unsigned int i=0 ; i < this->Vertical.size() ; i++)
		{
			if(this->Vertical[i].getLeft() < input1 && input1 < this->Vertical[i].getRight() && this->Vertical[i].getTop() < input2 && input2 < this->Vertical[i].getBottom())
			{
				count++;
				cout << this->Vertical[i].getTop() << " " << this->Vertical[i].getLeft()<< " " << this->Vertical[i].getBottom()<< " " << this->Vertical[i].getRight() << " ";
				cout << endl;;
			}
		}
	}
	if(this->Horizontal.size() != 0)//same...
	{
		for(unsigned int i=0 ; i < this->Horizontal.size() ; i++)
		{
			if(this->Horizontal[i].getLeft() < input1 && input1 < this->Horizontal[i].getRight() && this->Horizontal[i].getTop() < input2 && input2 < this->Horizontal[i].getBottom())
			{
				count++;
				cout << this->Horizontal[i].getTop() << " " << this->Horizontal[i].getLeft() << " " << this->Horizontal[i].getBottom() << " " << this->Horizontal[i].getRight();
				cout << endl;
			}
		}
	}

	if(input1 > (this->rec.getLeft()+this->rec.getRight())/2 && input2 > (this->rec.getBottom() + this->rec.getTop())/2) //if there is no rec at the vectors, then it checks the other nodes vector if there is.
	{
		(*(this->BottomRight)).search(input1,input2,count,searcher);
	}
	else if(input1 > (this->rec.getLeft()+this->rec.getRight())/2 && input2 < (this->rec.getBottom() + this->rec.getTop())/2)
	{
		(*(this->TopRight)).search(input1,input2,count,searcher);
	}
	else if(input1 < (this->rec.getLeft()+this->rec.getRight())/2 && input2 > (this->rec.getBottom() + this->rec.getTop())/2)
	{
		(*(this->BottomLeft)).search(input1,input2,count,searcher);
	}
	else if(input1 < (this->rec.getLeft()+this->rec.getRight())/2 && input2 < (this->rec.getBottom() + this->rec.getTop())/2)
	{
		(*(this->TopLeft)).search(input1,input2,count,searcher);
	}

	return count;
}

#endif //HEADER_H
