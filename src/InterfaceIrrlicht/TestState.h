#ifndef __TEST_STATE_H_
#define __TEST_STATE_H_

#include "State.h"

class TestState : public State
{
protected :
	irr::scene::ISceneNode * mpoHighlightedPiece;
	bool mbIsDragging;
public :
	TestState(InterfaceIrrlicht *);
	virtual void run();
	virtual bool OnEvent(const irr::SEvent &);
};

#endif