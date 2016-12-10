/*
 * Board.cpp
 *
 *  Created on: Nov 23, 2016
 *      Author: FCES 20
 */

#include "Board.hpp"
#include "Piece.hpp"
#include "SLL.hpp"
#include "SNode.hpp"
#include <iostream>
#include <string>

using namespace std;

Board::Board() {
	boardSize = 8;					// standard chess board dimensions

	board = new Piece*[boardSize];
	for(int i = 0; i < boardSize; i++) {	// initializes standard 8x8 board
		board[i] = new Piece[boardSize];
	}

	int numPieces = 16;		// assume standard 16 pieces for each player
	Piece * player1;		// will hold whites pieces
	Piece * player2;		// will hold blacks pieces

	// Create white player -- i.e. player1
	char inCharPieces1[numPieces] = {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R',
							 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'};
	int inPosPieces1[numPieces] = {11, 21, 31, 41, 51, 61, 71, 81,
						   12, 22, 32, 42, 52, 62, 72, 82};

	player1 = makePiecesArray(1, &inCharPieces1[0], numPieces);

	// Create black player -- i.e. player2
	char inCharPieces2[numPieces] = {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R',
							 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'};
	int inPosPieces2[numPieces] = {18, 28, 38, 48, 58, 68, 78, 88,
						   17, 27, 37, 47, 57, 67, 77, 87};

	player2 = makePiecesArray(0, &inCharPieces2[0], numPieces);

	// add player1 and player2 pieces to board
	updateBoard(numPieces, &player1[0], &inPosPieces1[0]);
	updateBoard(numPieces, &player2[0], &inPosPieces2[0]);
}

Piece * Board::makePiecesArray(int color, char inPieceSym[], int numPieces) {
	Piece * pieces = new Piece[numPieces];

	for (int i = 0; i < numPieces; i++) {
		char type = inPieceSym[i];
		if (type == 'P') {// call appropriate constructor and put in pieces array
			pieces[i] = Pawn();
		} else if (type == 'K') {
			pieces[i] = King();
		} else if (type == 'Q') {
			pieces[i] = Queen();
		} else if (type == 'R') {
			pieces[i] = Rook();
		} else if (type == 'N') {
			pieces[i] = Knight();
		} else if (type == 'B') {
			pieces[i] = Bishop();
		}
		pieces[i].setColor(color);// set color field of each piece object
	}
	return &pieces[0];
}

Board::Board(Board * board1, int color, int initialPos, int finalPos) {
	board = new Piece * [boardSize];
	tempPiece = board1->tempPiece;
	boardSize = 8;
	int position;

	for(int i = 0; i < boardSize; i++) {	// initializes standard 8x8 board
		board[i] = new Piece[boardSize];
	}

	for(int i = 0; i < boardSize; i++) {	// initializes standard 8x8 board
		for (int j = 0; j < boardSize; j++ ) {
			position = ((i + 1) * 10) + ((j + 1) * 1);
			addToPosition(position, board1->getAtPosition(position));
		}
	}

	//this->board = board1->board;
	movePiece(color, initialPos, finalPos);
}


/* if pieces array is updated in player object then want to also update board field which
 * holds up to date spatial information that is easily outputted.
 */
void Board::updateBoard(int numPieces, Piece * piecesArray, int * positionsArray) {
	for(int i = 0; i < numPieces; i++) {
		addToPosition(positionsArray[i], &piecesArray[i]);
	}
}

/* Takes a position and adds a piece to board 2D array at that position.
 *Translation from one coordinate system to another in a sense.
 */
void Board::addToPosition(int position, Piece * piece) {
	if (position >= 11 && position <= 88) {
		int xPos, yPos;
		xPos = (position / 10) - 1;		// -1 because call leftmost corner position (1, 1)
		yPos = (position % 10) - 1;
		board[xPos][yPos] = *piece;
	}
	else {
		cout << "WARNING: addToPosition() TRIGGERED ERROR" << endl;
	}
}
Piece * Board::getAtPosition(int position) {
	if (position >= 11 && position <= 88) {
		int xPos, yPos;
		xPos = (position / 10) - 1;		// -1 because call leftmost corner position (1, 1)
		yPos = (position % 10) - 1;
		return &board[xPos][yPos];
	}
	else {
		cout << "WARNING: getAtPosition() TRIGGERED ERROR" << endl;
		return NULL;
		}
}

/* Moves a color piece from initialPos to finalPos on
 * the chess board. Only does the mechanics of the movement
 * and does not validate that movement is legal.
 */
void Board::movePiece(int color, int initialPos, int finalPos) {
	Piece * temP1;
	Piece* temP2;
	temP1 = getAtPosition(initialPos);
	temP2 = getAtPosition(finalPos);

	if (color != temP1->getColor()) {	// If no piece on initialPos for player to move let know
		string s;
		if (color == 0) {
			s = "black";
		}
		else if (color == 1){
			s = "white";
		}
		else {
			s = "NULL";
		}
		cout << "WARNING: No " << s << " piece could be found at position: " << initialPos << endl;
	}
	else if (color == 1 && temP2->getColor() == 0) {	// if white is moving a piece to space occupied by black
			temP2->setSymbol(" ");						// then set occupying piece to null space
			temP2->setColor(-1);
		}
	else if (color == 0 && temP2->getColor() == 1) {	// if black is moving a piece to space occupied by white
		temP2->setSymbol(" ");							// then set occupying piece to null space
		temP2->setColor(-1);
	}

	tempPiece = new Piece();							// Not most efficient I'd think, but ask for help before submission
	tempPiece->setSymbol(temP1->getSymbol());
	tempPiece->setColor(temP1->getColor());
	addToPosition(initialPos, temP2);
	addToPosition(finalPos, tempPiece);					// swap pieces and add to board
}

/* Determines whether a move is valid. Returns a boolean... true = valid move,
 *  false = not valid move.
 */
bool Board::isValidMove(int color, int initialPos, int finalPos) {
	string sym = getAtPosition(initialPos)->getSymbol();
	SLL * possibleMoves = getMoves(sym, color, initialPos);

	if (sym == " ") {	// can't move empty space
		return false;
	}
	if (color == getAtPosition(finalPos)->getColor()) {
		return false;
	}
//	if (sym == "K") {	// King can not move into check
//		SLL * allEnemyMoves = getAllEnemyMoves(color, initialPos, finalPos);
//
//		SNode * temp1 = allEnemyMoves->first;
//		while (temp1 != NULL) {	// loop through all enemy moves, if position want to move to is in
//			if (temp1->finalPos == finalPos) { // SLL of bad moves then it is not a valid move
//				return false;
//			}
//				temp1 = temp1->next;
//		}
//	}
	// check if finalPos is a valid move for type of piece--i.e. is in possibleMoves linked list
	SNode * temp2 = possibleMoves->first;
	bool foundInSLL = false;
	while (temp2 != NULL) {
		if (finalPos == temp2->getFinalPos()) {
			foundInSLL = true;
		}
		temp2 = temp2->next;
	}

	if (!foundInSLL) {		// if move not in list of valid moves isValidMove can return false
		return false;
	}
	else {
		return true;
	}
}

bool Board::colorLost(int color) {	// returns true if this color lost (and game is over)
	int position;					// lost defined as board having no king piece on it.
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			position = ((i + 1) * 10) + ((j + 1) * 1);
			if (getAtPosition(position)->getSymbol() == "K" && getAtPosition(position)->getColor() == color) {
				return false;
			}
		}
	}
	return true;		// king with your color is not found on board...
}

// returns SLL of all possible enemy moves if you do undertake the movement from initial to final positions.
SLL * Board::getAllEnemyMoves(int color, int initialPos, int finalPos) {	// need initial and final positions because
	int position;															// pawn moves dependent on
	SLL * enemyMoves;	// holds all possible moves of enemy pieces on the board
	SLL * allEnemyMoves = new SLL();
	Piece * tmp;
	for (int i = 0; i < boardSize; i++) {	// traverse the whole board
		for (int j = 0; j < boardSize; j++) {
			position = (10 * (j + 1)) + (1 * (i + 1));
			tmp = getAtPosition(position);
			if (tmp->getColor() != -1 && tmp->getColor() != color) {  // if opposite color and not empty
				if (tmp->getSymbol() == "P") { 		// have to include because pawns attack adjacently
					movePiece(color, initialPos, finalPos);
					enemyMoves = getMoves(tmp->getSymbol(), tmp->getColor(), position);
					movePiece(color, finalPos, initialPos);
				}
				else {
					enemyMoves = getMoves(tmp->getSymbol(), tmp->getColor(), position);
				}
				allEnemyMoves->join(enemyMoves);	// make a big SLL of all possible enemy moves
				//allEnemyMoves->printSLL();
			}
		}
	}
	return allEnemyMoves;
}

SLL * Board::getMoves(string sym, int color, int initialPos) {
	SLL * moves = new SLL();
	int upLimit;
	int opMatSize;
	int * movementOperator;
	int * xMovementOperator;
	int * yMovementOperator;

	if (sym == " ") {
		return moves;
	}
	else if (sym == "P") {
		moves = getPawnMoves(color, initialPos);	// different movement from the rest so implemented elsewhere
		return moves;
	}
	else if (sym == "K") {
		upLimit = 2;
		opMatSize = 8;
		int movementOperatorD[8] = { -9, 01, 11,
								   -10,     10,
								   -11, -1,  9};
		int xMovementOperatorD[8] = {-1,  0,  1,
									-1,      1,
									-1,  0,  1};
		int yMovementOperatorD[8] = { 1,  1,  1,
									 0,      0,
									-1, -1, -1};
		movementOperator = new int[opMatSize];					// so ugly but not sure how else to do it
		xMovementOperator = new int[opMatSize];					// since aren't sure of size before hand
		yMovementOperator = new int[opMatSize];					// and aren't supposed to use global variables
		for (int i = 0; i < opMatSize; i++) {
			movementOperator[i] = movementOperatorD[i];
			xMovementOperator[i] = xMovementOperatorD[i];
			yMovementOperator[i] = yMovementOperatorD[i];
		}
	}
	else if (sym == "Q") {
		upLimit = 7;
		opMatSize = 8;
		int movementOperatorD[8] = { -9, 01, 11,
								   -10,     10,
								   -11, -1,  9};
		int xMovementOperatorD[8] = {-1,  0,  1,
									-1,      1,
									-1,  0,  1};
		int yMovementOperatorD[8] = { 1,  1,  1,
									 0,      0,
									-1, -1, -1};
		movementOperator = new int[opMatSize];
		xMovementOperator = new int[opMatSize];
		yMovementOperator = new int[opMatSize];
		for (int i = 0; i < opMatSize; i++) {
			movementOperator[i] = movementOperatorD[i];
			xMovementOperator[i] = xMovementOperatorD[i];
			yMovementOperator[i] = yMovementOperatorD[i];
		}
	}
	else if (sym == "R") {
		upLimit = 7;
		opMatSize = 4;
		int movementOperatorD[4] = {     01,
								   -10,     10,
										-1,    };
		int xMovementOperatorD[4] = {     0,
									-1,      1,
										 0,    };
		int yMovementOperatorD[4] = {     1,
									 0,      0,
										-1,    };
		movementOperator = new int[opMatSize];
		xMovementOperator = new int[opMatSize];
		yMovementOperator = new int[opMatSize];
		for (int i = 0; i < opMatSize; i++) {
			movementOperator[i] = movementOperatorD[i];
			xMovementOperator[i] = xMovementOperatorD[i];
			yMovementOperator[i] = yMovementOperatorD[i];
		}
	}
	else if (sym == "B") {
		upLimit = 7;
		opMatSize = 4;
		int movementOperatorD[4] = { -9,     11,

								   -11,      9};
		int xMovementOperatorD[4] = {-1,      1,

									-1,      1};
		int yMovementOperatorD[4] = { 1,      1,

									-1,     -1};
		movementOperator = new int[opMatSize];
		xMovementOperator = new int[opMatSize];
		yMovementOperator = new int[opMatSize];
		for (int i = 0; i < opMatSize; i++) {
			movementOperator[i] = movementOperatorD[i];
			xMovementOperator[i] = xMovementOperatorD[i];
			yMovementOperator[i] = yMovementOperatorD[i];
		}
	}
	else if (sym == "N") {
		upLimit = 2;
		opMatSize = 8;
		int movementOperatorD[8] =  {    -8,     12,
									-19,            21,

									-21,            19,
								        -12,     8     };
		int xMovementOperatorD[8] = {    -1,      1,
									 -2,             2,

									 -2,             2,
								         -1,     1     };
		int yMovementOperatorD[8] = {      2,     2,
									  1,             1,

									 -1,            -1,
								         -2,     -2    };
		movementOperator = new int[opMatSize];
		xMovementOperator = new int[opMatSize];
		yMovementOperator = new int[opMatSize];
		for (int i = 0; i < opMatSize; i++) {
			movementOperator[i] = movementOperatorD[i];
			xMovementOperator[i] = xMovementOperatorD[i];
			yMovementOperator[i] = yMovementOperatorD[i];
		}
	}
	else {
		cout << "ERROR IN getMoves()--SYMBOL NOT RECOGNIZED" << endl;
		return moves;
	}

	int xPos, yPos;
	xPos = (initialPos / 10) - 1;
	yPos = (initialPos % 10) - 1;

	for (int i = 0; i < opMatSize; i++) {	// run 8 times, loop through movementOperator matrix.
		for (int j = 1; j < upLimit; j++) {	// DIFFERENCE from the king movement is queen can keep going in that direction.
			if (j * xMovementOperator[i] + xPos > 7 || j * xMovementOperator[i] + xPos < 0 ||
				j * yMovementOperator[i] + yPos > 7 || j * yMovementOperator[i] + yPos < 0) {	//if. out of bounds
				break;	// do not add, end looping
			}
			else if (color == getAtPosition(initialPos + (j * movementOperator[i]))->getColor()) {		// if same color
				break;
			}
			else if (getAtPosition(initialPos + (j * movementOperator[i]))->getColor() != -1) {		// different color
				moves->addAtFront(initialPos, initialPos + j * movementOperator[i]);	// allow that move, but not further in that direction
				break;
			}
			else {		// since three color possibilities if not 0 == black, 1 == white, then must be -1 == empty space... so good to add piece
				moves->addAtFront(initialPos, initialPos + j * movementOperator[i]);
			}
		}
	}
	delete [] movementOperator;
	delete [] xMovementOperator;
	delete [] yMovementOperator;
	return moves;
}

SLL * Board::getPawnMoves(int color, int initialPos) {
	SLL * moves = new SLL();
	int xPos, yPos;
	xPos = (initialPos / 10) - 1;
	yPos = (initialPos % 10) - 1;

	if (color == 1) {	// white pawn moves
		// white moves diagonal in positive x direction, if black on occupying piece and dosn't go off board = valid move
		if (xPos < 7 && getAtPosition(initialPos + 10 + 1)->getColor() == 0) {
			moves->addAtFront(initialPos, initialPos + 11);
		}
		// white moves diagonal in negative x direction, if black on occupying piece and dosn't go off board = valid move
		if (xPos > 0 && getAtPosition(initialPos - 10 + 1)->getColor() == 0) {
			moves->addAtFront(initialPos, initialPos - 9);
		}
		// check spaces in front of if white, if occupied end, can't move through own pieces or blacks
		for (int i = 1; i < 3; i++) {
			if (yPos > 7 || getAtPosition(initialPos + i)->getColor() != -1) {	// if not empty -- i.e. if occupied
				break;
			}
			// since pawns can only move two spaces on the first move need a condition to check if its yPos is its initial position of 2
			if (i == 2 && yPos != 1) {
				break;
			}
			moves->addAtFront(initialPos, initialPos + i);
		}
	}
	else if (color == 0) {	// black pawn moves
		// black moves diagonal in positive x direction, if white on occupying piece and dosn't go off board = valid move
		if (xPos < 7 && getAtPosition(initialPos + 10 - 1)->getColor() == 1) {
			moves->addAtFront(initialPos, initialPos + 10 - 1);
		}
		// black moves diagonal in negative x direction, if white on occupying piece and dosn't go off board = valid move
		if (xPos > 0 && getAtPosition(initialPos - 10 - 1)->getColor() == 1) {
			moves->addAtFront(initialPos, initialPos - 10 - 1);
		}
		// check spaces in front of (below) if black, if occupied end, can't move through own pieces or blacks
		for (int i = 1; i < 3; i++) {
			if (yPos < 0 || getAtPosition(initialPos - i)->getColor() != -1) {	// if not empty -- i.e. if occupied
				break;
			}
			// since pawns can only move two spaces on the first move need a condition to check if its yPos is its initial position of 2
			if (i == 2 && yPos != 6) {
				break;
			}
			moves->addAtFront(initialPos, initialPos - i);
		}
	}
	return moves;
}

//SLL * Board::getKingMoves(int color, int initialPos) {
//	SLL * moves = new SLL();
//	int xPos, yPos;
//	xPos = (initialPos / 10) - 1;
//	yPos = (initialPos % 10) - 1;
//
//	// check all 8 adjacent spaces if on board, if any are occupied determine if their friendly or not, if not friendly or empty = valid move
//	int movementOperator[8] = { -9, 01, 11,
//							   -10,     10,
//							   -11, -1,  9};
//	int xMovementOperator[8] = {-1,  0,  1,
//								-1,      1,
//								-1,  0,  1};
//	int yMovementOperator[8] = { 1,  1,  1,
//								 0,      0,
//								-1, -1, -1};
//
//	for (int i = 0; i < 8; i++) {	// run 8 times, loop through movementOperator matrix.
//		if(xPos + xMovementOperator[i] < 8 && xPos + xMovementOperator[i] > -1 &&
//		   yPos + yMovementOperator[i] < 8 && yPos + yMovementOperator[i] > -1 ) {		// make sure movement is within bounds of board
//			if (getAtPosition(initialPos + movementOperator[i])->getColor() != color) {
//				moves->addAtFront(initialPos, initialPos + movementOperator[i]);
//			}
//		}
//	}
//	// also, king can not technically move into check, something to think about for later...
//
//	return moves;
//}
//
//SLL * Board::getQueenMoves(int color, int initialPos) {
//	SLL * moves = new SLL();
//	int xPos, yPos;
//	xPos = (initialPos / 10) - 1;
//	yPos = (initialPos % 10) - 1;
//
//	// check all 8 adjacent spaces if on board, if any are occupied determine if their friendly or not, if not friendly or empty = valid move
//	int movementOperator[8] = { -9, 01, 11,
//							   -10,     10,
//							   -11, -1,  9};
//	int xMovementOperator[8] = {-1,  0,  1,
//								-1,      1,
//								-1,  0,  1};
//	int yMovementOperator[8] = { 1,  1,  1,
//								 0,      0,
//								-1, -1, -1};
//
//	for (int i = 0; i < 8; i++) {	// run 8 times, loop through movementOperator matrix.
//		for (int j = 1; j < 7; j++) {	// DIFFERENCE from the king movement is queen can keep going in that direction.
//			if (j * xMovementOperator[i] + xPos > 7 || j * xMovementOperator[i] + xPos < 0 ||
//				j * yMovementOperator[i] + yPos > 7 || j * yMovementOperator[i] + yPos < 0) {	//if. out of bounds
//				break;	// do not add, end looping
//			}
//			else if (color == getAtPosition(initialPos + (j * movementOperator[i]))->getColor()) {		// if same color
//				break;
//			}
//			else if (getAtPosition(initialPos + (j * movementOperator[i]))->getColor() != -1) {		// different color
//				moves->addAtFront(initialPos, initialPos + j * movementOperator[i]);	// allow that move, but not further in that direction
//				break;
//			}
//			else {		// since three color possibilities if not 0 == black, 1 == white, then must be -1 == empty space... so good to add piece
//				moves->addAtFront(initialPos, initialPos + j * movementOperator[i]);
//			}
//		}
//	}
//	return moves;
//}
//
//SLL * Board::getRookMoves(int color, int initialPos) {
//	SLL * moves = new SLL();
//	int xPos, yPos;
//	xPos = (initialPos / 10) - 1;
//	yPos = (initialPos % 10) - 1;
//
//	// check all 8 adjacent spaces if on board, if any are occupied determine if their friendly or not, if not friendly or empty = valid move
//	int movementOperator[4] = {     01,
//							   -10,     10,
//									-1,    };
//	int xMovementOperator[4] = {     0,
//								-1,      1,
//								     0,    };
//	int yMovementOperator[4] = {     1,
//								 0,      0,
//								    -1,    };
//
//	for (int i = 0; i < 4; i++) {	// run 8 times, loop through movementOperator matrix.
//		for (int j = 1; j < 7; j++) {	// DIFFERENCE from the king movement is queen can keep going in that direction.
//			if (j * xMovementOperator[i] + xPos > 7 || j * xMovementOperator[i] + xPos < 0 ||
//				j * yMovementOperator[i] + yPos > 7 || j * yMovementOperator[i] + yPos < 0) {	//if. out of bounds
//				break;	// do not add, end looping
//			}
//			else if (color == getAtPosition(initialPos + (j * movementOperator[i]))->getColor()) {		// if same color
//				break;
//			}
//			else if (getAtPosition(initialPos + (j * movementOperator[i]))->getColor() != -1) {		// different color
//				moves->addAtFront(initialPos, initialPos + j * movementOperator[i]);	// allow that move, but not further in that direction
//				break;
//			}
//			else {		// since three color possibilities if not 0 == black, 1 == white, then must be -1 == empty space... so good to add piece
//				moves->addAtFront(initialPos, initialPos + j * movementOperator[i]);
//			}
//		}
//	}
//	return moves;
//}
//
//SLL * Board::getBishopMoves(int color, int initialPos) {
//	SLL * moves = new SLL();
//	int xPos, yPos;
//	xPos = (initialPos / 10) - 1;
//	yPos = (initialPos % 10) - 1;
//
//	// check all 8 adjacent spaces if on board, if any are occupied determine if their friendly or not, if not friendly or empty = valid move
//	int movementOperator[4] = { -9,     11,
//
//							   -11,      9};
//	int xMovementOperator[4] = {-1,      1,
//
//								-1,      1};
//	int yMovementOperator[4] = { 1,      1,
//
//								-1,     -1};
//
//	for (int i = 0; i < 4; i++) {	// run 8 times, loop through movementOperator matrix.
//		for (int j = 1; j < 7; j++) {	// DIFFERENCE from the king movement is queen can keep going in that direction.
//			if (j * xMovementOperator[i] + xPos > 7 || j * xMovementOperator[i] + xPos < 0 ||
//				j * yMovementOperator[i] + yPos > 7 || j * yMovementOperator[i] + yPos < 0) {	//if. out of bounds
//				break;	// do not add, end looping
//			}
//			else if (color == getAtPosition(initialPos + (j * movementOperator[i]))->getColor()) {		// if same color
//				break;
//			}
//			else if (getAtPosition(initialPos + (j * movementOperator[i]))->getColor() != -1) {		// different color
//				moves->addAtFront(initialPos, initialPos + j * movementOperator[i]);	// allow that move, but not further in that direction
//				break;
//			}
//			else {		// since three color possibilities if not 0 == black, 1 == white, then must be -1 == empty space... so good to add piece
//				moves->addAtFront(initialPos, initialPos + j * movementOperator[i]);
//			}
//		}
//	}
//	return moves;
//}
//
//SLL * Board::getKnightMoves(int color, int initialPos) {
//	SLL * moves = new SLL();
//	int xPos, yPos;
//	xPos = (initialPos / 10) - 1;
//	yPos = (initialPos % 10) - 1;
//
//	// check all 8 adjacent spaces if on board, if any are occupied determine if their friendly or not, if not friendly or empty = valid move
//	int movementOperator[8] =  {    -8,     12,
//								-19,            21,
//
//								-21,            19,
//							        -12,     8     };
//	int xMovementOperator[8] = {    -1,      1,
//								 -2,             2,
//
//								 -2,             2,
//							         -1,     1     };
//	int yMovementOperator[8] = {      2,     2,
//								  1,             1,
//
//								 -1,            -1,
//							         -2,     -2    };
//
//	for (int i = 0; i < 8; i++) {	// run 8 times, loop through movementOperator matrix.
//		for (int j = 1; j < 2; j++) {	// DIFFERENCE from the king movement is queen can keep going in that direction.
//			if (j * xMovementOperator[i] + xPos > 7 || j * xMovementOperator[i] + xPos < 0 ||
//				j * yMovementOperator[i] + yPos > 7 || j * yMovementOperator[i] + yPos < 0) {	//if. out of bounds
//				break;	// do not add, end looping
//			}
//			else if (color == getAtPosition(initialPos + (j * movementOperator[i]))->getColor()) {		// if same color
//				break;
//			}
//			else if (getAtPosition(initialPos + (j * movementOperator[i]))->getColor() != -1) {		// different color
//				moves->addAtFront(initialPos, initialPos + j * movementOperator[i]);	// allow that move, but not further in that direction
//				break;
//			}
//			else {		// since three color possibilities if not 0 == black, 1 == white, then must be -1 == empty space... so good to add piece
//				moves->addAtFront(initialPos, initialPos + j * movementOperator[i]);
//			}
//		}
//	}
//	return moves;
//}

void Board::printBoard() { // outputs board with the symbol of each piece in a space corresponding to its position
	string s;
	for (int i = boardSize - 1; i >= 0; i--) {
		for (int j = 0; j < boardSize; j++) {
			if (j == 0) {
				cout << i + 1 << " ";
			}
			if (board[j][i].getColor() == 0) {// if black piece -- display as lowercase
				s = tolower(board[j][i].getSymbol()[0]);

				cout << "|_" << s << "_";
			} else {
				cout << "|_" << board[j][i].getSymbol() << "_";
			}
		}
		cout << "|" << endl;
	}
	cout << "    a   b   c   d   e   f   g   h " << endl;
}
