#ifndef __STATE_H_
#define __STATE_H_

#include "irrlicht.h"
#include "InterfaceIrrlicht.h"

class State : public irr::IEventReceiver
{
protected :
	bool mbStop;
	InterfaceIrrlicht * mpoInterface;
public :
	State(InterfaceIrrlicht * poInterface);
	virtual bool OnEvent(const irr::SEvent &);
	virtual void Run();
	virtual bool bIsRunning();
	virtual void Stop();
};

#endif