#ifndef __INTERFACE_CONSOLE_H_
#define __INTERFACE_CONSOLE_H_

#include "interface.h"

class InterfaceConsole : public Interface
{
  protected :
	InterfaceConsole();
  public :
	virtual void DisplayBoard(const Board &) const;
	virtual void DisplayMessage(std::string strMessage) const;
	virtual std::string strGetEntry() const;
	virtual void DisplayPossibilities(std::string strPossibilities) const;
	virtual void DisplayInCheck(Position) const;
	virtual void DisplayCurrentPlayer(Piece::Color) const;
	virtual void DisplaySelection(Position) const;
	static Interface * poGetInstance();
};

#endif