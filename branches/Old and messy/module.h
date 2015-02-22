#ifndef __MODULE_H_
#define __MODULE_H_

#include <string>
/**
 * This interface describes a module of the game,
 * such as one player game, two player game, game edition, etc...
 * It force the derivated class to implement a Run() methods
 */

class Interface;

class Module
{
  protected :
	Interface * mpoInterface;
  public :
    /**
	 * Destructor
	 */
    virtual ~Module();

	/**
	 * Run the module.
	 * Return r to restart the module, or q to quit the game
	 */
	virtual std::string Run() = 0;
	virtual void Initialize() = 0;
	virtual void SetInterface(Interface *);
};

#endif
