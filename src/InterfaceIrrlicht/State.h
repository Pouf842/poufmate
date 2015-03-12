#ifndef __STATE_H_
#define __STATE_H_

#include "irrlicht.h"
#include "interface_Irrlicht.h"

class State : public irr::IEventReceiver
{
protected :
	bool mbStop;
	InterfaceIrrlicht * mpoInterface;
public :
	State(InterfaceIrrlicht * poInterface);
	virtual bool OnEvent(const irr::SEvent &);
	virtual void Run();
	virtual void Stop();
};

#endif