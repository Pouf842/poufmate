#ifndef __GAME_EDITION_H_
#define __GAME_EDITION_H_

/**
 * This class is an implement of the module interface.
 * It describes the game edition mode, where the user
 * can place the piece as he choose to on the board,
 * and eventually start a game with the edited board.
 */

#include "module.h"
#include "board.h"
#include "interface.h"

class GameEdition : public Module
{
	Board moBoard;						/// Board
	Position moKingAlreadyThere[2];		/// The position of kings

  public :
	/**
	 * Basic constructor
	 */
	GameEdition(Interface * poInterface = NULL);

	/**
	 * Destructor
	 */
	virtual ~GameEdition();

	/**
	 * Implement of Module::Run()
	 * Run the edition mode
	 */
	virtual Entry::ENTRY_COMMAND Run();
	Board oGetBoard() const;
	void Initialize();
};

#endif
