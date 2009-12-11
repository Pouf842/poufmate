#ifndef __INTERFACE_H_
#define __INTERFACE_H_

#include "board.h"
#include "position.h"
#include <string>

class Interface
{
  protected :
	static Interface * mpoInstance;
  public :
	virtual void DisplayBoard(const Board &) = 0;
	virtual void DisplayMessage(std::string strMessage) = 0;
	virtual std::string strGetEntry() = 0;
	virtual void DisplayPossibilities(std::string strPossibilities) = 0;
	virtual void DisplayInCheck(Position) = 0;
	virtual void DisplayCurrentPlayer(Piece::Color) = 0;
	virtual void DisplaySelection(Position) = 0;
	virtual void CommitDisplay() = 0;
	static Interface * poGetInstance() {}
	static void FreeInstance()
	{
		if(mpoInstance)
			delete mpoInstance;
	}
};

#endif
