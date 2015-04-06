#ifndef __INTRO_STATE_H_
#define __INTRO_STATE_H_

#include "../../InterfaceIrrlicht.h"
#include "../State.h"

class IntroState : public State
{
protected :
    irr::scene::ISceneNodeAnimator * mpoAnimator;
    bool mbStop;
public :
    IntroState(InterfaceIrrlicht *);
    virtual ~IntroState();

    virtual void Show();
    virtual void Hide();
    virtual bool OnEvent(const irr::SEvent &);
};

#endif