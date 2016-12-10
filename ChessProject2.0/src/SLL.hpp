/*
 * SLL.hpp
 *
 *  Created on: Sep 26, 2016
 *      Author: Debra
 */

#ifndef SLL_HPP_
#define SLL_HPP_
#include "SNode.hpp"

class SLL {
	friend class Board;
	SNode *first;
	SNode *last;
	int size;
public:
	SLL();
	~SLL();
	void printSLL();
	void addFirst(int x, int y);
	void addAtFront(int x, int y);
	void push(int x, int y);
	void addAtK(int x, int y, int k);

	void join(SLL *list2);
	int * pop();
	SNode *findKth(int k);
	int findK(int k);
	int * remFirst();
	int remKth(int k);
	void reverseList();
	int getSize();
};





#endif /* SLL_HPP_ */
