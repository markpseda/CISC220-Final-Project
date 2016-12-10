/*
 * Board.hpp
 *
 *  Created on: Nov 23, 2016
 *      Author: FCES 20
 */

#ifndef BOARD_HPP_
#define BOARD_HPP_

#include "Piece.hpp"
#include "SLL.hpp"

using namespace std;

class Board {
// private methods and fields
	int boardSize;

// public methods and fields
public:
	Piece ** board;	// 2D-array holding piece objects
	Piece * tempPiece;	// temporary Piece object that contains last piece moved
	//SLL * allPosMoves;	// Singly linked list hold all legal board moves

	Board();
	Board(std::string s);
	Board(Board * board1, int color, int initialPos, int finalPos);

	void updateBoard(int numPieces,  Piece * piecesArray, int * positionsArray);
	Piece * makePiecesArray(int color, char inPieceSym[], int numPieces);
	void movePiece(int color, int initialPos, int finalPos);
	void addToPosition(int position, Piece * piece);
	Piece * getAtPosition(int position);
	bool isValidMove(int color, int initialPos, int finalPos);
	bool colorLost(int color);

	// returns list of possible position moves dependent on piece type
	SLL * getMoves(std::string sym, int color, int initialPos);
	SLL * getPawnMoves(int color, int initialPos);
	SLL * getAllEnemyMoves(int color, int initialPos, int finalPos);
//	SLL * getKingMoves(int color, int initialPos);
//	SLL * getQueenMoves(int color, int initialPos);
//	SLL * getRookMoves(int color, int initialPos);
//	SLL * getBishopMoves(int color, int initialPos);
//	SLL * getKnightMoves(int color, int initialPos);

	// print methods
	void printBoard();

};



#endif /* BOARD_HPP_ */
