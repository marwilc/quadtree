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
int main ()
{
	list<color> lx, ly;

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

		//qt1.preOrderRoute();
		cout<<"qt1 pixels black:"<<qt1.pixelsBlack()<<endl;
		//qt2.preOrderRoute();
		cout<<"qt2 pixels black:"<<qt2.pixelsBlack()<<endl;
	}
	return (0);
}
