#ifndef __TEST_STATE_H_
#define __TEST_STATE_H_

#include "State.h"

class TestState : public State
{
protected :
	irr::IrrlichtDevice * mpoDevice;
	irr::scene::ISceneManager  * mpoSceneManager;
	irr::scene::ISceneCollisionManager * mpoCollisionManager;
	irr::video::IVideoDriver   * mpoVideoDriver;
	irr::scene::ISceneNode * mpoHighlightedPiece;
	irr::core::vector3df moRelColl;
	bool mbIsDragging;
public :
	TestState(InterfaceIrrlicht *);
	virtual void run();
	virtual bool OnEvent(const irr::SEvent &);
};

#endif