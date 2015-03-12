#ifndef __GAME_STATE_H_
#define __GAME_STATE_H_

#include "State.h"

class GameState : public State
{
protected :
public :
	GameState(InterfaceIrrlicht *);
	virtual bool OnEvent(const irr::SEvent &);
};

#endif