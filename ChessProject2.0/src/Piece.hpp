/*
 * Piece.hpp
 *
 *  Created on: Nov 18, 2016
 *      Author: FCES 20
 */

#ifndef PIECE_HPP_
#define PIECE_HPP_
#include <string>

/* Defines the symbol and color of a piece and handles its movement on
 * a board with other pieces.
 */


// Base Class
class Piece {
//Protected methods and fields
protected:
	std::string symbol;
	int color;			// black or white


//Public methods and fields
public:
	// constructors
	Piece();
	Piece(char sym, int color);

	// accessors
	std::string getSymbol();
	int getColor();

	// mutators
	void setSymbol(std::string symbol);
	void setColor(int color);

	// methods with common implementation
	void printPiece();

	// methods with implementation unique to derived class
	virtual int getMoves();
	//virtual int * getMoves(Board * board); //{return 0;}

};

// Derived Classes
class Pawn: public Piece {

public:
	Pawn();
	int getMoves();
	//int * getMoves(Board * board);
};

class King: public Piece {

public:
	King();
	int getMoves();
	//int * getMoves(Board * board);
};

class Queen: public Piece {

public:
	Queen();
	int getMoves();
	//int  * getMoves(Board * board);
};

class Rook: public Piece {

public:
	Rook();
	int getMoves();
	//int * getMoves(Board * board);
};

class Knight: public Piece {

public:
	Knight();
	int getMoves();
	//int * getMoves(Board * board);
};

class Bishop: public Piece {

public:
	Bishop();
	int getMoves();
	//int * getMoves(Board * board);
};

#endif /* PIECE_HPP_ */
