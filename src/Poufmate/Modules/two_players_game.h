#ifndef __TWO_PLAYERS_GAME_H_
#define __TWO_PLAYERS_GAME_H_

/**
 * This class describes a chess game
 * The Run() method start the game, controls
 * the actions of the players, interact with
 * them via an Interface object, and transmit
 * their choices of action to the board
 * @see class Module
 */

#include "Modules/game.h"

class Controller;

class TwoPlayersGame : public Game
{
public :
	/**
	 * Destructor
	 */
	virtual ~TwoPlayersGame();

	/**
	 * Constructor
	 */
	TwoPlayersGame(Controller * = NULL);

	/**
	 * Constructor to start a two player game with a specified board
	 * Note that the board must contain one and only one king for each player
	 */
    TwoPlayersGame(const Board & oBoard, Controller * = NULL);
};

#endif