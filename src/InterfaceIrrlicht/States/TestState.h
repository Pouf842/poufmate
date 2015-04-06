#ifndef __TEST_STATE_H_
#define __TEST_STATE_H_

#include "State.h"

class TestState : public State
{
protected :
public :
	TestState(InterfaceIrrlicht *);
	virtual bool OnEvent(const irr::SEvent &);
};

#endif