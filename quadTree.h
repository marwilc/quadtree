/*
 * quadTree.h
 *
 *  Created on: Jul 4, 2016
 *      Author: marwilc
 */

#ifndef QUADTREE_H_
#define QUADTREE_H_
#include <list>
#include <queue>
#include <stack>
#include "nodeQ.h"
#include <iostream>

using namespace std;

enum color { BLANCO, NEGRO, GRIS };

template <class T>
class QuadTree
{
	private:
		NodeQ<T> *root;
		static const int totalPixel=64;

		static NodeQ<T> *construct(list<T> &listA, const T &e); //contruye un arbol QuadTree pasandole un elemento como raiz y una lista
		static NodeQ<T> *copyNodes(NodeQ<T> *ptr);//copia los apartir del apuntador y lo devuelve
		static void preOrder(NodeQ<T> *ptr);
		static int contPixelsBlack(NodeQ<T> *ptr, const int &pixelsTotal);

	public:
		//constructores
		QuadTree<T>():root(NULL){}; //listo
		//QuadTree<T>(const T &e, list<QuadTree> l);
		QuadTree(list <T> &listA);// listo
		~QuadTree<T>();//listo
		//consultores
		bool isNull()const{return(root==NULL);} //listo
		T getColor()const{return(root->getInfo());}//listo
		void preOrderRoute();//listo
		int pixelsBlack()const;
		list<QuadTree> sons()const;//falta

		//modificadores
		void insertSubTree(const int &pos, QuadTree<T> tree);//falta
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
		root=copyNodes(qt.root);
	}
	return(*this);
}

//staticos
template <class T>
NodeQ<T>* QuadTree<T>::construct(list<T> &listA, const T &e)
{
	NodeQ<T> *nuevo=NULL, *aux;
	int i;
	T elem;

	if(!listA.empty())
	{
		nuevo=new NodeQ<T>(e);
		for(i=1;i<=4;i++)
		{
			elem=listA.front();
			listA.pop_front();
			if(elem==GRIS)
			{
				aux=construct(listA, elem);
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

	if(!listA.empty())
	{
		e=listA.front();
		listA.pop_front();
		aux=construct(listA,e);
	}
	this->root=aux;
}

//destructor
template <class T>
QuadTree<T>::~QuadTree()
{
	NodeQ<T> *aux;
	stack<NodeQ<T>* > p;
	int i;


	if(root!=NULL)
	{
		p.push(root);
		while(!p.empty())
		{
			aux=p.top();
			p.pop();
			for(i=1;i<=4;i++)
			{
				if(aux->getSubTree(i-1)!=NULL)
				{
					p.push(aux->getSubTree(i-1));
					aux->setSubTree(NULL, i-1);
				}
			}
			delete(aux);
		}
	}
}

template <class T>
void QuadTree<T>::preOrderRoute()
{
	if(root!=NULL)
	{
		preOrder(root);
	}
}

template <class T>
int QuadTree<T>::pixelsBlack()const
{
	int pixels=0 ,tPixels=64;
	if(root!=NULL)
	{
		pixels=contPixelsBlack(root,tPixels/4);
	}
	return(pixels);
}




#endif /* QUADTREE_H_ */
