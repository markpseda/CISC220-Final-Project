/*
 * SSNode.cpp
 *
 *  Created on: Sep 26, 2016
 *      Author: Debra
 */
#include "SNode.hpp"
#include <iostream>
#include <stdlib.h>

using namespace std;

SNode::SNode(int x, int y) {
	initialPos = x;
	finalPos = y;
	next = NULL;
}
SNode::~SNode() {
	if (next != NULL) {
		cout << "deleting this SNode may cause a memory leak" << endl;
	}
}
int SNode::getInitialPos() {
	return initialPos;
}
int SNode::getFinalPos() {
	return finalPos;
}


