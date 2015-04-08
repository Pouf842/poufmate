#ifndef __ONE_PLAYER_GAME_H_
#define __ONE_PLAYER_GAME_H_

#include "Modules/game.h"
#include "Interface/interface.h"

class OnePlayerGame : public Game
{
	protected :

	/**
	 * Play the computer move
	 */
	void PlayComputerMove(unsigned int);

	/**
	 * Alphabeta algorithm to note each possible move for the computer
	 */
	int Alphabeta(unsigned int profondeur, int MinimumDesFreres);

	/**
	 * Note the current situation (moBoard) for the specified player
	 */
	int HeuristicValue(Piece::PIECE_COLOR);

	/**
	 * Generate a list of all possible movements for the specified player
	 * in the current situation (moBoard)
	 */
	std::vector<Movement*> GenerateMovementsForPlayer(Piece::PIECE_COLOR eColor);

  public :
    /**
	 * Constructor
	 */
	OnePlayerGame(Controller * = NULL);

	/**
	 * Constructor to start a game
	 * with a predefined board
	 */
	OnePlayerGame(const Board &, Controller * = NULL);

	/**
	 * Destructor
	 */
	virtual ~OnePlayerGame();
};

#endif
