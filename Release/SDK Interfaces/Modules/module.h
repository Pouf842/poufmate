#ifndef __MODULE_H_
#define __MODULE_H_

#include <string>

#include "Core\board.h"
#include "Interface\entry.h"
/**
 * This interface describes a module of the game,
 * such as one player game, two player game, game edition, etc...
 * It force the derivated class to implement a Run() methods
 */

class Interface;

class Module
{
  public :
	enum MODULE_TYPE
	{
		MT_NONE=0,
		MT_ONE_PLAYER_GAME,
		MT_TWO_PLAYER_GAME,
		MT_EDITION,
	};
  protected :
	Board moBoard;					// The board of the game
	MODULE_TYPE meType;
	Interface * mpoInterface;
  public :

    /**
	 * Destructor
	 */
    virtual ~Module();

	/**
	 * Run the module.
	 * Return Entry::EC_RESET_GAME to restart the module, or Entry::EC_QUIT_GAME to quit the game
	 */
	virtual Entry::ENTRY_COMMAND Run() = 0;
	virtual void Initialize() = 0;
	virtual void SetInterface(Interface *);
	virtual Board & oGetBoard() const;
	virtual MODULE_TYPE eGetType() const;
	virtual bool bIsGame() const;
};

#endif
