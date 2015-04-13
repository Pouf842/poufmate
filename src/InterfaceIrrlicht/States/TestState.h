#ifndef __TEST_STATE_H_
#define __TEST_STATE_H_

#include "State.h"

class TestState : public State
{
protected :
    bool mbStop;
public :
	TestState(InterfaceIrrlicht *);
	virtual bool OnEvent(const irr::SEvent &);
    virtual void Show();
    virtual void Hide();
};

#endif