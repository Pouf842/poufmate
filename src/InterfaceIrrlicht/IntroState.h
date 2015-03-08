#ifndef __INTRO_STATE_H_
#define __INTRO_STATE_H_

#include "interface_Irrlicht.h"
#include "State.h"

class IntroState : public State
{
protected :
	irr::scene::ISceneNodeAnimator * mpoAnimator;
public :
	virtual ~IntroState();
	IntroState(InterfaceIrrlicht *);

	virtual bool OnEvent(const irr::SEvent &);
};

#endif