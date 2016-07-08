/*
 * main.cpp
 *
 *  Created on: Jul 4, 2016 9:35:02 PM
 *      Author: marwilc
 *
 */

#include <iostream>
#include "quadTree.h"

using namespace std;

//enum color { BLANCO, NEGRO, GRIS };

void printList(list<QuadTree <color> > l)
{
	list<QuadTree <color> >:: iterator it = l.begin();
	QuadTree<color> qt;
	while( it != l.end())
	{
		qt=*it;
		cout <<" "<<qt.getColor();
		*it++;
	}
}

color pintar(const char &c)
{
	color colour=GRIS;

	if(c=='p')
	{
		colour=GRIS;
	}
	else if(c=='f')
		{
		colour=NEGRO;
		}
		else if(c=='e')
			{
			  colour=BLANCO;
			}
	return(colour);
}
int main (int argc, char *argv[])
{
	list<color> lx, ly;
	list<QuadTree <color> > lqt1, lqt2;
	int cases,i;
	char c;
	color colour;

	cin>>cases;
	cin.get();
	for(i=1;i<=3;i++)
	{
		while((c=cin.get())!='\n')
		{
			//cout<<c;
			colour=pintar(c);
			//cout<<colour;
			lx.push_back(colour);
		}
		//cout<<endl;
		while((c=cin.get())!='\n')
		{	//cout<<c;
			colour=pintar(c);
			//cout<<colour;
			ly.push_back(colour);
		}
		//cout<<endl;
		QuadTree<color> qt1(lx), qt2(ly);

		lqt1=qt1.sons();
		lqt2=qt2.sons();
		cout<<qt1.hMax()<<endl;
		cout<<qt2.hMax()<<endl;
		//printList(lqt1);
		//cout<<endl;
		//printList(lqt2);
		//cout<<endl;
		//qt1.preOrderRoute();
		//cout<<"qt1 pixels black:"<<qt1.pixelsBlack()<<endl;
		//qt2.preOrderRoute();
		//cout<<"qt2 pixels black:"<<qt2.pixelsBlack()<<endl;
		//qt1.clear();
		//qt2.clear();
	}
	return (0);
}
