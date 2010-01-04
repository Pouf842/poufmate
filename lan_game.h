#ifndef __LAN_GAME_H_
#define __LAN_GAME_H_

#include "game.h"
#include "interface.h"

class LanGame : public Game
{
  public :
	LanGame();
	LanGame(const Board &);
	void Run(Interface * poInterface);
};

#endif