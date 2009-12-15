#ifndef __INTERFACE_CONSOLE_H_
#define __INTERFACE_CONSOLE_H_

#include "interface.h"
#include <sstream>

class InterfaceConsole : public Interface
{
  protected :
	std::stringstream mOs;
	InterfaceConsole();
  public :
	virtual void DisplayBoard(const Board &);
	virtual void DisplayMessage(std::string strMessage);
	virtual std::string strGetEntry();
	virtual void DisplayPossibilities(std::string strPossibilities);
	virtual void DisplayInCheck(Position);
	virtual void DisplayCurrentPlayer(Piece::Color);
	virtual void DisplaySelection(Position);
	virtual void CommitDisplay();
	virtual char cGetNewPieceType();
	static Interface * poGetInstance();
	static void FreeInstance();
};

#endif