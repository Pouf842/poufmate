#ifndef __GAME_EDITION_H_
#define __GAME_EDITION_H_

/**
 * This class is an implement of the module interface.
 * It describes the game edition mode, where the user
 * can place the piece as he choose to on the board,
 * and eventually start a game with the edited board.
 */

#include "Modules/module.h"
#include "Core/board.h"
#include "Interface/interface.h"

class GameEdition : public Module
{
	Board moBoard;						/// Board
	Piece::PIECE_TYPE meSelectedPieceType;
	Piece::PIECE_COLOR meSelectedPieceColor;
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
	Piece::PIECE_TYPE eGetSelectedPieceType();
	Piece::PIECE_COLOR eGetSelectedPieceColor();
	void Initialize();
};

#endif
