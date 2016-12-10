/*
 * Piece.cpp
 *
 *  Created on: Nov 18, 2016
 *      Author: FCES 20
 */

#include "Piece.hpp"
//#include "Board.hpp"
#include <string>
#include <iostream>

using namespace std;

// Piece methods -- belonging to base class

// Default constructor makes an empty space piece
Piece::Piece() {
	symbol = " ";
	color = -1;
}

Piece::Piece(char sym, int color) {
	this->color = color;

	if (sym == 'P') {
		Pawn();
	}
	else if (sym == 'K') {
		King();
	}
	else if (sym == 'Q') {
		Queen();
	}
	else if (sym == 'R') {
		Rook();
	}
	else if (sym == 'N') {
		Knight();
	}
	else if (sym == 'B') {
		Bishop();
	}
}

// accesors
string Piece::getSymbol() {
	return symbol;
}
int Piece::getColor() {
	return color;
}

// mutators
void Piece::setSymbol(string symbol) {
	this->symbol = symbol;
}
void Piece::setColor(int color) {
	this->color = color;
}

// methods with common implementation
void Piece::printPiece() {
	cout << "Piece: " << getSymbol() <<
			" Color: " << color << endl;
}

// constructors
Pawn::Pawn() {
	symbol = "P";
}
King::King() {
	symbol = "K";
}
Queen::Queen() {
	symbol = "Q";
}
Rook::Rook() {
	symbol = "R";
}
Knight::Knight() {
	symbol = "N";
}
Bishop::Bishop() {
	symbol = "B";
}

// methods with unique implementation
// methods with unique implementation
int Piece::getMoves() {
	return 0;
}

int Pawn::getMoves() {
	return 1;
}
int King::getMoves() {
	return 1;
}
int Queen::getMoves() {
	return 1;
}
int Rook::getMoves() {
	return 1;
}
int Knight::getMoves() {
	return 1;
}
int Bishop::getMoves() {
	return 1;
}

// ask why dosn't work
//int * Piece::getMoves(Board * board) {
//	int * ints = new int[1];
//	return ints;
//}
//int * Pawn::getMoves(Board * board) {
//	int * ints = new int[1];
//	return ints;
//}
//int * King::getMoves(Board * board) {
//	int * ints = new int[1];
//	return ints;
//}
//int * Queen::getMoves(Board * board) {
//	int * ints = new int[1];
//	return ints;
//}
//int * Rook::getMoves(Board * board) {
//	int * ints = new int[1];
//	return ints;
//}
//int * Knight::getMoves(Board * board) {
//	int * ints = new int[1];
//	return ints;
//}
//int * Bishop::getMoves(Board * board) {
//	int * ints = new int[1];
//	return ints;
//}
