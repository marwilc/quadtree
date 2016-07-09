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
	//list<QuadTree <color> > lqt1, lqt2;
	int cases,i;
	char c;
	color colour;

	cin>>cases;
	cin.get();
	for(i=1;i<=cases;i++)
	{
		while((c=cin.get())!='\n')
		{
			colour=pintar(c);
			lx.push_back(colour);
		}
		while((c=cin.get())!='\n')
		{
			colour=pintar(c);
			ly.push_back(colour);
		}
		QuadTree<color> qt1(lx), qt2(ly) ,qtsuma;

		qtsuma=qt1.unionQt(qt2);
		cout<<"Hay "<<qtsuma.pixelsBlack()<<" pixels negros."<<endl;

	}
	return (0);
}
