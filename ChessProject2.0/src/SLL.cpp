/*
 * SLL.cpp
 *
 *  Created on: Sep 26, 2016
 *      Author: Debra
 */

#include "SLL.hpp"
#include "SNode.hpp"
#include <iostream>
#include <stdlib.h>
using namespace std;

SLL::SLL(){
	first = NULL;
	last = NULL;
	size = 0;
}
SLL::~SLL(){
	SNode *tmp = first;
	while (first != NULL) {
		tmp = first->next;
		delete first;
		first = tmp;
		size --;
	}
	first = NULL;
	last = NULL;
}
void SLL::printSLL() {
	SNode *tmp = first;
	while (tmp != NULL) {
		//cout << tmp->initialPos << ":" << tmp->finalPos << "->";
		cout << tmp->finalPos << "->";
		tmp = tmp->next;
	}
	cout << endl;
}

//make a new list of only one node, data is x
void SLL::addFirst(int x, int y) { // 3 pts
	SNode *firstNode = new SNode(x, y);
	first = firstNode;
	last = firstNode;
	size = 1;
}

//add a new node to the front of the list with data being x
void SLL::addAtFront(int x, int y) {  //3 pts
	if (size == 0) {
		addFirst(x, y);
	}
	else {
		SNode *nextFirstNode = new SNode(x, y);
		nextFirstNode->next = first;
		first = nextFirstNode;
		size++;
	}
}

//add a new node to the end of the list, with data x
void SLL::push(int x, int y) { //6 pts
	SNode *lastNode = new SNode(x, y);
	last->next = lastNode;
	last = lastNode;
	size++;
}

void SLL::addAtK(int x, int y, int k){
	SNode *tmp = first;
	if (k==0) {
		addAtFront(x, y);
		//size++;          Don't need since do already in addAtFront()
	}
	else if (k < size  && k >= 0) {					// Made an edit here-- changed to an else if so not triggering both if statements
		for (int i = 0; i < k-1; i++) {
			tmp = tmp->next;
		}
		SNode *tmp2 = tmp->next;
		tmp->next = new SNode(x, y);
		tmp->next->next = tmp2;
		size++;
	}
}

//join the list with list2, making the current list one longer list
void SLL::join(SLL *list2){ //3 pts
	if (list2->first == NULL) {
		// do nothing...
	}
	else if (first == NULL) {	// implied second list has stuff in it
		first = list2->first;
		last = list2->last;
		size = list2->size;
	}
	else {
		last->next = list2->first;
		last = list2->last;
		size += list2->size;
	}
}

int * SLL::pop() {
	if (size > 0) {
		int x = last->initialPos;
		int y = last->finalPos;
		int retArr[2] = {x, y};
		if (first != last ){
			SNode *tmp = first;
			for (int i = 0; i < size - 2; i++) {			// Changed limit of for loop to -2 instead of -1
				tmp = tmp->next;
			}
			delete last;
			last = tmp;
			last->next = NULL;
		}
		else {
			delete last;
			first = NULL;
			last = NULL;
		}
		size --;
		return retArr;
	}
	else {
		int null[1] = {-1};
		return null;
	}
}

// find the node at the kth location and return it. Assumes first element corresponds to k = 0.
SNode *SLL::findKth(int k) { //4 pts
	SNode *temp = first;

	if(!(k >= 0 && k < size)) {
		cout << "Could not find node at position " << k << endl;
		return NULL;
	}
	for(int i = 0; i < size; i++) {
		if(i == k) {
			return temp;
		}
		temp = temp->next;
	}
}

//// find the position of the first element in the list where k occurs
//int SLL::findK(int k) {
//	SNode *tmp = first;
//	int ind = 0;
//	while (tmp != NULL && tmp->initialPos != k) {
//		tmp = tmp->next;
//		ind++;
//	}
//	if (ind < size) {
//		return ind;
//	}
//	else {
//		return -1;
//	}
//}

//remove the first node from the list, returning its data
int * SLL::remFirst() { //3 pts
	SNode *temp = first;
	first = temp->next;
	int x = temp->initialPos;
	int y = temp->finalPos;
	int retArr[2] = {x,y};
	delete temp;
	size--;
	return retArr;
}

// returns finalPos
int SLL::remKth(int k) {
	if (k < size && k > 0) {
		SNode *tmp = first;
		for (int i = 0; i < k -1; i++) {
			tmp = tmp->next;
		}
		int y = tmp->next->finalPos;
		SNode *tmp2= tmp->next;
		tmp->next = tmp->next->next;
		delete tmp2;
		return y;
	}
	else {
		cout << "Can not find a node at k to remove" << endl;
		return -1;
	}
}

//Reverses the list, after completed, the last should be the first
//in the list and the first should be the last
//Challenge - I did this with one pass across the list
void SLL::reverseList(){ //10 pts
	SNode *prevTemp = NULL;
	SNode *curTemp = first;
	SNode *nextTemp = NULL;
	while (curTemp != NULL) {
		nextTemp = curTemp->next;
		curTemp->next = prevTemp;	//Crucial step where have current point to previous--hence reversing linked list
		prevTemp = curTemp;
		curTemp = nextTemp;
	}
	first = prevTemp;
}

int SLL::getSize() {
	return size;
}
