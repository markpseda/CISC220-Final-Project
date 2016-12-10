/*
 * Game.hpp
 *
 *  Created on: Nov 17, 2016
 *      Author: FCES 20
 */

#ifndef GAME_HPP_
#define GAME_HPP_

//#include "Piece.hpp"
#include <string>
#include "Board.hpp"

class Game {
//Private methods and fields
	int siConv(std::string posString);

//Public methods and fields
public:
	Board * gameBoard;			// 2D-array holding Board object

	Game();
	void startGame();
	void begin2PlayerPlay();
	void begin1PlayerPlay();

	// print methods
	void displayWelcome();
	void displayMenu();
	void displayEndGame();
	void displayInstructions();

};

#endif /* GAME_HPP_ */
