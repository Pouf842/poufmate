#ifndef __MODULE_H_
#define __MODULE_H_

#include <string>

#include "Core/board.h"

/**
 * This interface describes a module of the game,
 * such as one player game, two player game, game edition, etc...
 * It force the derivated class to implement a Run() methods
 */

class Module
{
  public :
	enum MODULE_TYPE
	{
		MT_NONE=0,
		MT_GAME,
		MT_EDITION
	};
  protected :
	Board moBoard;					// The board of the game
    MODULE_TYPE meType;
  public :

    /**
	 * Destructor
	 */
    virtual ~Module();
	virtual void Initialize() = 0;
	virtual MODULE_TYPE eGetType() const;
    virtual bool bIsGame() const;
    virtual Board & oGetBoard() const;

    virtual void GrabPiece(const Position &) = 0;
    virtual void DropPiece(const Position &) = 0;
    virtual void SelectNewPiece() = 0;
};

#endif
