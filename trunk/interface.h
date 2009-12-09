#ifndef __INTERFACE_H_
#define __INTERFACE_H_

#include "board.h"
#include <string>

class Interface
{
  protected :
	static Interface * mpoInstance;
  public :
	virtual void DisplayBoard(const Board &) const = 0;
	virtual void DisplayMessage(std::string strMessage) const = 0;
	virtual std::string strGetCommand() const = 0;
	virtual void DisplayPossibilities(std::string strPossibilities) const = 0;
	static Interface * poGetInstance() {}
};

#endif
