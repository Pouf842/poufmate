#ifndef __CONTROLLER_H_
#define __CONTROLLER_H_

#include <irrlicht.h>

class Controller : public irr::IEventReceiver
{
protected :
	bool mbKeysDown[irr::KEY_KEY_CODES_COUNT];
	irr::SEvent::SJoystickEvent moJoystickState;
	irr::SEvent::SMouseInput moMouseState;

	// Various commands
	bool mbExit;
	bool mbAutoStop;
public :
	Controller();
	virtual bool OnEvent(const irr::SEvent & oEvent);
	virtual bool bIsKeyDown(irr::EKEY_CODE keyCode);
	virtual bool bAutoStop();
	virtual bool bExit();
	virtual irr::SEvent::SJoystickEvent oGetJoystickState();
	virtual irr::SEvent::SMouseInput oGetMouseState();
	virtual void stopAutoStop();
};

#endif