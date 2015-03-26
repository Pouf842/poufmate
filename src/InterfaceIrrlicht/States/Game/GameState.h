#ifndef __GAME_STATE_H_
#define __GAME_STATE_H_

#include "../State.h"

class GameState : public State
{
protected :
	irr::scene::ISceneNode * mpoHighlightedPiece;
	irr::core::vector3df moRelColl;
	bool mbIsDragging;

	Entry moLastEntry;
public :
	GameState(InterfaceIrrlicht *);
	virtual bool OnEvent(const irr::SEvent &);
	virtual void Run();
	Entry oGetLastEntry() const;
};

#endif