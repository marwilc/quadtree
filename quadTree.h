/*
 * quadTree.h
 *
 *  Created on: Jul 4, 2016
 *      Author: marwilc
 */

#ifndef QUADTREE_H_
#define QUADTREE_H_
#include <limits>
#include <list>
#include <queue>
#include <stack>
#include "nodeQ.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

enum color { BLANCO, NEGRO, GRIS };

template <class T>
class QuadTree
{
	private:
		NodeQ<T> *root;
		int h;
		//static const int totalPixel=64;

		static NodeQ<T> *construct(list<T> &listA, const T &e, int &hfinal, const int &h); //contruye un arbol QuadTree pasandole un elemento como raiz y una lista
		static NodeQ<T> *copyNodes(NodeQ<T> *ptr);//copia los apartir del apuntador y lo devuelve
		static void preOrder(NodeQ<T> *ptr);//listo
		static int contPixelsBlack(NodeQ<T> *ptr, const int &pixelsTotal);//listo
		static void clear(NodeQ<T> *ptr);

	public:
		//constructores
		QuadTree():root(NULL), h(0){}; //listo
		//QuadTree<T>(const T &e, list<QuadTree> l);
		QuadTree(list <T> &listA);// listo
		QuadTree(const QuadTree<T> &qt):root(copyNodes(qt.root)), h(qt.h){};
		~QuadTree();//listo
		void clear();
		//consultores
		bool isNull()const{return(this->root==NULL);} //listo
		T getColor()const{return(this->root->getInfo());}//listo
		void preOrderRoute();//listo
		int pixelsBlack()const;//listo
		list< QuadTree<T> > sons()const;//listo
		int hMax()const{return(this->h);};

		//modificadores
		void copyTree(const QuadTree<T> &qt);
		void insertSubTree(const int &pos, QuadTree<T> &tree);//falta
		void deleteSubTree(const int &pos);//falta
		QuadTree<T> unionQ(QuadTree<T> B);//falta

		//sobrecarga
		QuadTree<T>& operator=(const QuadTree<T> &n);//listo


};


template <class T>
QuadTree<T>& QuadTree<T>::operator=(const QuadTree<T> &qt)
{
	if(this != &qt)
	{
		this->root=copyNodes(qt.root);
	}
	return(*this);
}

//staticos
template <class T>
NodeQ<T>* QuadTree<T>::construct(list<T> &listA, const T &e , int &hfinal, const int &h)
{
	NodeQ<T> *nuevo=NULL, *aux;
	int i;
	T elem;

	if(!listA.empty())
	{
		if(h>hfinal)
			hfinal=h;

		nuevo=new NodeQ<T>(e);
		for(i=1;i<=4;i++)
		{
			elem=listA.front();
			listA.pop_front();
			if(elem==GRIS)
			{
				aux=construct(listA, elem, hfinal, h+1);

			}
			else
			{
				aux=new NodeQ<T>(elem);
			}
			nuevo->setSubTree(aux, i-1);
		}
	}
	return(nuevo);
}

template <class T>
NodeQ<T>* QuadTree<T>::copyNodes(NodeQ<T> *ptr)
{
	NodeQ<T> *nuevo, *aux;
	int i;

	if(ptr==NULL)
	{
		return(NULL);
	}
	else
	{
		nuevo=new NodeQ<T>(ptr->getInfo());
		for(i=1;i<=4;i++)
		{
			aux=copyNodes(ptr->getSubTree(i-1));
			nuevo->setSubTree(aux, i-1);
		}
		return(nuevo);
	}
}

template <class T>
void QuadTree<T>:: preOrder(NodeQ<T> *ptr)
{
		NodeQ<T> *aux;
		T e;
		int i;

		if(ptr!=NULL)
		{
			aux=ptr;
			e=aux->getInfo();
			cout<<e;
			for(i=1;i<=4;i++)
			{
				if(aux->getSubTree(i-1)!=NULL)
				{
					preOrder(aux->getSubTree(i-1));
				}
			}
		}
}

template<class T>
int QuadTree<T>::contPixelsBlack(NodeQ<T> *ptr, const int &pixelsTotal)
{
	NodeQ<T> *aux;
	int pixels=0,i;

	if(ptr==NULL)
	{
		return(0);
	}
	else
	{
		for(i=1;i<=4;i++)
		{
			aux=ptr->getSubTree(i-1);
			if(aux->getInfo()==GRIS)
			{
				pixels=contPixelsBlack(aux,pixelsTotal/4)+pixels;
			}
			else if(aux->getInfo()==NEGRO)
			{
				pixels+=pixelsTotal;
			}
		}
		return(pixels);
	}
}

//contructores
template <class T>
QuadTree<T>::QuadTree(list <T>  &listA)
{
	NodeQ<T> *aux=NULL;
	T e;
	int n=0, hf=numeric_limits<int>::min();

	if(!listA.empty())
	{
		e=listA.front();
		listA.pop_front();
		aux=construct(listA,e, hf, n+1);
	}
	this->root=aux;
	this->h=hf;
}

//destructor
template <class T>
QuadTree<T>::~QuadTree()
{
	this->clear();
}

template <class T>
void QuadTree<T>::clear()
{
	clear(this->root);
	this->root=NULL;
	this->h=0;
}
template <class T>
void QuadTree<T>::clear(NodeQ<T> *ptr)
{
	NodeQ<T> *aux;
	int i;

	if(ptr!=NULL)
	{
		aux=ptr;
		for(i=1;i<=4;i++)
		{
			clear(aux->getSubTree(i-1));
		}
		delete(aux);
		ptr=NULL;
		//aux=NULL;
		//cout<<"hola";
	}
}
template <class T>
void QuadTree<T>::preOrderRoute()
{
	if(this->root!=NULL)
	{
		preOrder(this->root);
	}
}

template <class T>
list< QuadTree<T> > QuadTree<T>:: sons()const
{
	QuadTree<T> A;
	NodeQ<T> *aux;
	list< QuadTree<T> > l;

	int i;

	if(this->root!=NULL)
	{

		aux=this->root;
		for(i=1;i<=4;i++)
		{
			if(aux->getSubTree(i-1)!=NULL)
			{
				A.root=copyNodes(aux->getSubTree(i-1));
				//A.root=aux->getSubTree(i-1);
				A.h=h-1;
				l.push_back(A);
			}
		}
	}
	return(l);
}
template <class T>
int QuadTree<T>::pixelsBlack()const
{
	int pixels=0 ,tPixels=64;
	if(this->root!=NULL)
	{
		pixels=contPixelsBlack(this->root,64/4);
	}
	return(pixels);
}

template <class T>
void QuadTree<T>:: copyTree(const QuadTree<T> &qt)
{
	this->root=copyNodes(qt.root);
}



#endif /* QUADTREE_H_ */
