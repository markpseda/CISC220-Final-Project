/*
 * SSNode.hpp
 *
 *  Created on: Sep 26, 2016
 *      Author: Debra
 */

#ifndef SNode_HPP_
#define SNode_HPP_

class SNode {
	friend class SLL;
	friend class Board;
	int initialPos;
	int finalPos;
	SNode *next;
public:
	SNode(int initialPos, int finalPos);
	~SNode();
	int getInitialPos();
	int getFinalPos();

};



#endif /* SSNode_HPP_ */
