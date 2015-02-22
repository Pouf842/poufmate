#ifndef __GAME_ENTRY_H_
#define __GAME_ENTRY_H_

#include <string>
#include "position.h"

class GameEntry
{
  public:
	GameEntry(Position, Position);
	GameEntry(std::string);
	virtual ~GameEntry();

	bool bIsCommand();
	Position oGetPos1();
	Position oGetPos2();
	std::string strGetCommand();

  protected :
	Position moPos1;
	Position moPos2;
	bool mbIsCommand;
	std::string mstrCommand;
};

#endif