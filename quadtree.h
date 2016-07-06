/*
 * quadtree.h
 *
 *  Created on: Jul 5, 2016 9:01:59 PM
 *      Author: marwilc
 *		
 */

#ifndef QUADTREE_H_
#define QUADTREE_H_
#include <list>
#include "nodeq.h"

enum color{BLANCO, NEGRO, GRIS};

template <class T>
class QuadTree
{
	private:
		NodeQ<T> *_root;

		QuadTree():_root(NULL){};


};



#endif /* QUADTREE_H_ */
