/*
 * Game.cpp
 *
 *  Created on: Nov 17, 2016
 *      Author: FCES 20
 */

#include "Game.hpp"
#include "Board.hpp"
#include "Piece.hpp"
#include <string>
#include <iostream>
#include <stdlib.h>

using namespace std;

// constructor
Game::Game() {
	Board * board = new Board();
	gameBoard = board;
}

void Game::startGame() {
	bool keepGoing = true;
	string menuChoice1;
	string menuChoice2;
	while(keepGoing) {
		displayWelcome();
		do {
			displayMenu();
			cin >> menuChoice1;
			menuChoice1 = toupper(menuChoice1[0]);	// acounts for lowercase inpus
		} while(menuChoice1 != "P" && menuChoice1 != "I" && menuChoice1 != "Q");
		if (menuChoice1 == "Q" ) {
			displayEndGame();
			keepGoing = false;
		}
		else if (menuChoice1 == "I") {
			displayInstructions();
		}
		else if (menuChoice1 == "P") {
			do {
				cout << "Enter 2 for a two player game and 1 for a 1 player game: " << endl;
				cin >> menuChoice2;
				menuChoice2 = menuChoice2[0];	// acounts for lowercase inpus
			} while (menuChoice2 != "1" && menuChoice2 != "2");
			if (menuChoice2 == "2") {
				begin2PlayerPlay();
			}
			else {
				begin1PlayerPlay();
			}
		}
	}
}

void Game::begin2PlayerPlay() {
	bool noWinner = true;
	int turnsPlayed = 0;		// keeps track of turns played so far
	int colorTurn;				// keeps track of whose turn it is
	string startPosStr;
	string endPosStr;
	int startPos;
	int endPos;
	string s;
	while(noWinner) {
		colorTurn = (turnsPlayed + 1) % 2;    // since white begins traditionally
		gameBoard->printBoard();
		bool validMove = false; 		//assume not good move initially
		do {
			if (colorTurn == 1) {
				s = "WHITE TURN--";
			}
			else if (colorTurn == 0) {
				s = "BLACK TURN--";
			}
			cout << s << "ENTER THE POSITION OF THE PIECE YOU WISH TO MOVE:" << endl;
			cin >> startPosStr;
			cout << "ENTER THE POSITION THAT YOU WANT TO MOVE PIECE TO: " << endl;
			cin >> endPosStr;
			startPos = siConv(startPosStr);		// converts string to int position representation
			endPos = siConv(endPosStr);

			if (startPos < 11 || startPos > 88 || endPos < 11 || endPos > 88) {		// necessary because function isValidMove assumes position inputs greater than zero
				cout << "WARNING: NOT VALID INPUT -- ENTER A POSITION BETWEEN 11 AND 88!!!" << endl;
				validMove = false;
			}
			else if (!gameBoard->isValidMove(colorTurn, startPos, endPos)) {
				cout << "WARNING: NOT VALID INPUT -- NOT VALID CHESS MOVE -- READ INSTRUCTIONS FOR MORE INFORMATION!!!" << endl;
				validMove = false;
			}
			else {
				validMove = true;
			}

		} while(!validMove);

		gameBoard->movePiece(colorTurn, startPos, endPos);
		if (gameBoard->colorLost(1)) {		// if white loses
			gameBoard->printBoard();
			cout << "CONGRATULATIONS--BLACK WINS!!!" << endl;
			noWinner = false;

		}
		if (gameBoard->colorLost(0)) {		// if black loses
			gameBoard->printBoard();
			cout << "CONGRATULATIONS--WHITE WINS!!!" << endl;
			noWinner = false;

		}
		turnsPlayed++;
	}
}

void Game::begin1PlayerPlay() {
	cout << "1 player play" << endl;
}

int Game::siConv(string posString) {
	int xDigit, yDigit;
	string s1, s2;
	s1 = tolower(posString[0]);
	s2 = posString[1];
	if (s1 == "a") {
		xDigit = 1;
	} else if (s1 == "b") {
		xDigit = 2;
	} else if (s1 == "c") {
		xDigit = 3;
	} else if (s1 == "d") {
		xDigit = 4;
	} else if (s1 == "e") {
		xDigit = 5;
	} else if (s1 == "f") {
		xDigit = 6;
	} else if (s1 == "g") {
		xDigit = 7;
	} else if (s1 == "h") {
		xDigit = 8;
	}
	else {
		cout << "WARNING: ERROR IN siConv() -- INVALID USER INPUT" << endl;
		return 0;
	}
	if (s2 == "1") {
		yDigit = 1;
	}
	else if (s2 == "2") {
		yDigit = 2;
	}
	else if (s2 == "3") {
		yDigit = 3;
	}
	else if (s2 == "4") {
		yDigit = 4;
	}
	else if (s2 == "5") {
		yDigit = 5;
	}
	else if (s2 == "6") {
		yDigit = 6;
	}
	else if (s2 == "7") {
		yDigit = 7;
	}
	else if (s2 == "8") {
		yDigit = 8;
	}
	else {
		cout << "WARNING: ERROR IN siConv() -- INVALID USER INPUT" << endl;
		return 0;
	}

	return (10 * xDigit) + (1 * yDigit);
}

// print methods -- handle output and formatting to screen
void Game::displayWelcome() {
	cout << "***************************WELCOME TO CHESS***************************" << endl;
	// description of project purpose of program, what demonstrates
}
void Game::displayMenu() {
	cout << "Enter one of the following to continue: " << endl;
	cout << "P -- PLAY" << endl;
	cout << "I -- INSTRUCTIONS" << endl;
	cout << "Q -- QUIT" << endl;


}
void Game::displayEndGame() {
	cout << "***************************THANK YOU FOR PLAYING***************************" << endl;

}
void Game::displayInstructions() {
	cout << "INSTRUCTIONS: A SPECTACULAR ACCOUNT OF THE GAME OF CHESS IS GIVEN HERE" << endl;
}
