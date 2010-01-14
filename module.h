#ifndef __MODULE_H_
#define __MODULE_H_

/**
 * This interface describes a module of the game,
 * such as one player game, two player game, game edition, etc...
 * It force the derivated class to implement a Run() methods
 */

#include "interface.h"
class Interface;

class Module
{
  public :
    /**
	 * Destructor
	 */
    virtual ~Module();

	/**
	 * Run the module.
	 */
	virtual void Run(Interface *) = 0;
};

#endif
