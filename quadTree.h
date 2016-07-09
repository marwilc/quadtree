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
		static NodeQ<T> *recUnionQt(NodeQ<T> *ptr1, NodeQ<T> *ptr2);

	public:
		//constructores
		QuadTree():root(NULL), h(0){}; //listo
		//QuadTree(const T &e):root;
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
		int hMax()const{return(this->h);};// listo

		//modificadores
		void setColor(const T &c){this->root->setInfo(c);};
		void copyTree(const QuadTree<T> &qt);// listo
		void insertSubTree(const int &pos, QuadTree<T> &tree);//falta
		void deleteSubTree(const int &pos);//falta
		QuadTree<T> unionQt(const QuadTree<T> &qt2);
		//QuadTree<T> unionQ(QuadTree<T> B);//falta

		//sobrecarga
		QuadTree<T>& operator=(const QuadTree<T> &n);//listo


};


template <class T>
QuadTree<T>& QuadTree<T>::operator=(const QuadTree<T> &qt)
{
	if(this != &qt)
	{
		this->clear();
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


	nuevo=new NodeQ<T>(e);
	if(!listA.empty())
	{
		if(h>hfinal)
			hfinal=h;

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

	if(ptr->getInfo()==NEGRO)
		return(pixelsTotal);
	else if(ptr->getInfo()==BLANCO)
			return(pixels);
		else
		{
			for(i=1;i<=4;i++)
			{
				aux=ptr->getSubTree(i-1);
				pixels=contPixelsBlack(aux,pixelsTotal/4)+pixels;
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
	int pixels=0 ;
	if(this->root!=NULL)
	{
		pixels=contPixelsBlack(this->root,64);
	}
	return(pixels);
}

template <class T>
void QuadTree<T>:: copyTree(const QuadTree<T> &qt)
{
	this->root=copyNodes(qt.root);
}

template <class T>
void QuadTree<T>:: insertSubTree(const int &pos, QuadTree<T> &tree)
{
	if(!tree.isNull()&&root!=NULL)
	{
		root->setSubTree(tree.root, pos);

	}
}

template <class T>
void QuadTree<T>:: deleteSubTree(const int &pos)
{
	if(root!=NULL)
	{
		clear(root->getSubTree(pos));
	}
}

template <class T>
QuadTree<T> QuadTree<T>:: unionQt(const QuadTree<T> &qt2)
{
	QuadTree<T> nuevo;
	nuevo.root=recUnionQt(this->root,qt2.root);
	nuevo.h=(this->hMax()<=qt2.hMax())? qt2.hMax():this->hMax();
	return(nuevo);
}
template <class T>
NodeQ<T>* QuadTree<T>:: recUnionQt(NodeQ<T> *ptr1, NodeQ<T> *ptr2)
{
	NodeQ<T> *aux1, *aux2, *nuevo;
	//QuadTree<T> nuevo , aux;
	//list< QuadTree <T> > lstQt1, lstQt2;
	int i;

	if(ptr1!=NULL && ptr2!=NULL)
	{
		if(ptr1->getInfo()!=ptr2->getInfo())
		{
			if((ptr1->getInfo()==NEGRO || ptr1->getInfo()==GRIS) && ptr2->getInfo()!=NEGRO )
			{
				nuevo=copyNodes(ptr1);
				return(nuevo);
			}
			else
			{
				nuevo=copyNodes(ptr2);
				return(nuevo);
			}
		}
		else
		{
			if(ptr1->getInfo()==GRIS)
			{
				nuevo=new NodeQ<T>(GRIS);
				//nuevo.root=auxQ;
				//lstQt1=qt1.sons();
				//lstQt2=qt2.sons();
				//pos=0;
				//while(!lstQt1.empty() && !lstQt2.empty())
				//{
				for(i=1;i<=4;i++)
				{
					aux1=ptr1->getSubTree(i-1);
					aux2=ptr2->getSubTree(i-1);
					nuevo->setSubTree(recUnionQt(aux1,aux2),i-1);
					//aux=unionQt(lstQt1.front(),lstQt2.front());
					///lstQt1.pop_front();
					///lstQt2.pop_front();
					//nuevo.insertSubTree(pos,aux);
					//pos++;
				}
				//}
			}
			else
			{
				nuevo= new NodeQ<T>(ptr1->getInfo());
				return(nuevo);
			}
		}
	}
	return(nuevo);
}

#endif /* QUADTREE_H_ */
