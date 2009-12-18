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
	Board moBoard;
	Piece::PieceType meNewPieceType;
	Piece::Color meNewPieceColor;
	bool mbNewPieceSelected;
	Position moSelection;

  public :
	GameEdition();
	virtual ~GameEdition();
	virtual void Run(Interface *);
};

#endif
