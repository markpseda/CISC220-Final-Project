//============================================================================
// Name        : ChessProject.cpp
// Author      : Collin Wallish and Mark Seda
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Piece.hpp"
#include "Board.hpp"
#include "Game.hpp"
#include "SLL.hpp"
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

int main() {


Game * game1 = new Game();
game1->startGame();

//Board * board1 = new Board();
//board1->printBoard();
//board1->movePiece(1, 12, 13);
//Board * board2 = new Board(board1, 0, 17, 16);
//board1->printBoard();
//board2->printBoard();
//
//Board * board3 = new Board(board2, 1, 13, 15);
//board1->printBoard();
//board2->printBoard();
//board3->printBoard();

//
//board1->movePiece(1, 51, 55);
//board1->printBoard();
//SLL * moves = board1->getMoves("K", 1, 55);
//moves->printSLL();
//cout << board1->isValidMove(1, 55, 45) << endl;

//board1->movePiece(0, 47, 45);
//board1->movePiece(1, 42, 43);
//board1->movePiece(1, 32, 33);
//board1->movePiece(1, 52, 53);
//board1->movePiece(1, 51, 45);

//board1->movePiece(1, 12, 33);
//board1->movePiece(1, 22, 34);
//board1->movePiece(1, 32, 35);
//board1->movePiece(1, 42, 45);
//board1->movePiece(1, 52, 55);
//board1->movePiece(1, 62, 54);
//board1->movePiece(1, 72, 53);
//board1->movePiece(1, 82, 43);
//board1->printBoard();


//SLL * moves;
//SLL * totalMoves = new SLL();
//Piece * tmp;
//int position;
//for (int i = 0; i < 8; i++) {
//	for (int j = 0; j < 8; j++) {
//		position = (10 * (j + 1)) + (1 * (i + 1));
//		tmp = board1->getAtPosition(position);
//		if (tmp->getSymbol() != " ") {
//			moves = board1->getMoves(tmp->getSymbol(), tmp->getColor(), position);
//			//cout << tmp->getSymbol() << " at " << position << " has moves: " << endl;
//			moves->printSLL();
//			totalMoves->join(moves);
//			totalMoves->printSLL();
//		}
//	}
//}


//SLL * moves = board1->getMoves("K", 1, 45);
//moves->printSLL();



//	char inCharPieces[8] = {'R', 'N', 'B', 'K', 'Q', 'B', 'N', 'R'};
//	int inPosPieces[8] = {11, 21, 31, 41, 51, 61, 71, 81};
//	Player *player = new Player(1, &inCharPieces[0], &inPosPieces[0], 8);
//	player->printPlayer();
//Game *game1 = new Game();
//game1->startGame();
//game1->printBoard();
//game1->player1->printPlayer();
//game1->player2->printPlayer();
//game1->movePiece(1, 52, 54);
//cout << game1->isValidMove(0, 47, 45) << endl;
//cout << game1->isValidMove(0, 27, 54) << endl;
//cout << game1->isValidMove(0, 15, 16) << endl;
//cout << game1->isValidMove(0, 27, 28) << endl;
//cout << game1->isValidMove(0, 27, 59) << endl;



//game1->printBoard();
//game1->player1->printPlayer();
//game1->player2->printPlayer();
//game1->movePiece(0, 47, 45);
//game1->printBoard();
//game1->player1->printPlayer();
//game1->player2->printPlayer();
//game1->movePiece(1, 54, 45);
//game1->printBoard();
//game1->player1->printPlayer();
//game1->player2->printPlayer();
//game1->movePiece(0, 67, 66);
//game1->printBoard();
//game1->player1->printPlayer();
//game1->player2->printPlayer();
//game1->movePiece(1, 45, 46);
//game1->printBoard();
//game1->player1->printPlayer();
//game1->player2->printPlayer();
//game1->movePiece(0, 57, 46);
//game1->printBoard();
//game1->player1->printPlayer();
//game1->player2->printPlayer();



//string s = "K";
//s = tolower(s[0]);
//
//cout << s << endl;

//	Pawn pawn;
//	Piece * piece1 = &pawn;
//	Piece * piece2 = new Piece('K', 21, 1);
//	piece1->setSymbol("P");
//	piece2->setSymbol("K");
//	cout << "Pawn: " << piece1->getColor() << " "<< piece1->getSymbol() << endl;
//	cout << "King: " << piece2->getColor() << " "<< piece2->getSymbol() << endl;
//	string str = "hello";
//	char str2 = str.at(1);
//	cout << str2 << endl;
	return 0;
}
