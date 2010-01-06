#ifndef __ONE_PLAYER_GAME_H_
#define __ONE_PLAYER_GAME_H_

#include "game.h"
#include "interface.h"

class OnePlayerGame : public Game
{
  public :
    /**
	 * Constructor
	 */
	OnePlayerGame();

	/**
	 * Constructor to start a game
	 * with a predefined board
	 */
	OnePlayerGame(Board & oBoard);

	/**
	 * Destructor
	 */
	virtual ~OnePlayerGame();

	/**
	 * Overload of Game::Run()
	 * @see Game::Run()
	 */
	virtual void Run(Interface *);

	void PlayComputerMove(unsigned int);
	int Alphabeta(unsigned int profondeur, int MinimumDesFreres);
	int HeuristicValue(Piece::Color);
	void DestroyMovements(std::vector<Movement *> & oPossibilities);

	std::vector<Movement*> GenerateMovementsForPlayer(Piece::Color eColor);
};

#endif
