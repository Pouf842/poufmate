#ifndef __ONE_PLAYER_GAME_H_
#define __ONE_PLAYER_GAME_H_

#include "game.h"
#include "interface.h"

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
	int HeuristicValue(Piece::Color);

	/**
	 * Generate a list of all possible movements for the specified player
	 * in the current situation (moBoard)
	 */
	std::vector<Movement*> GenerateMovementsForPlayer(Piece::Color eColor);

  public :
    /**
	 * Constructor
	 */
	OnePlayerGame(Interface * poInterface = NULL);

	/**
	 * Constructor to start a game
	 * with a predefined board
	 */
	OnePlayerGame(const Board &, Interface * poInterface = NULL);

	/**
	 * Destructor
	 */
	virtual ~OnePlayerGame();

	/**
	 * Overload of Game::Run()
	 * @see Game::Run()
	 */
	virtual void Run();
};

#endif
