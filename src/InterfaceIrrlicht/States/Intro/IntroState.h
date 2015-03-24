#ifndef __INTRO_STATE_H_
#define __INTRO_STATE_H_

#include "../../InterfaceIrrlicht.h"
#include "../State.h"

class IntroState : public State
{
protected :
	irr::scene::ISceneNodeAnimator * mpoAnimator;
public :
	virtual ~IntroState();
	IntroState(InterfaceIrrlicht *);
};

#endif