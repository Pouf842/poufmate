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
};

#endif
