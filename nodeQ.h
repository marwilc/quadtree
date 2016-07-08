/*
 * nodeq.h
 *
 *  Created on: Jul 5, 2016 8:42:27 PM
 *      Author: marwilc
 *		
 */

#ifndef NODEQ_H_
#define NODEQ_H_
#include <iostream>

using namespace std;

template <class T>
class NodeQ
{
	private:
		T _info;
		static const int _MAX=4;
		NodeQ<T> *_subTrees[_MAX];

	public:
		//contructores
		NodeQ(){int i;for(i=1;i<=_MAX;i++)_subTrees[i-1]=NULL;};
		NodeQ(const T &e){this->_info=e; int i;for(i=1;i<=_MAX;i++)this->_subTrees[i-1]=NULL;};
		NodeQ(const T &e, NodeQ<T>* subtree[_MAX]);
		//consultores
		T getInfo()const{return(this->_info);};
		NodeQ<T>* getSubTree(const int &pos){return(this->_subTrees[pos]);};
		//modificadores
		void setInfo(const T &e){this->_info=e;};
		void setSubTree(NodeQ<T>* ptr, const int &pos){this->_subTrees[pos]=ptr;};

};




#endif /* NODEQ_H_ */
