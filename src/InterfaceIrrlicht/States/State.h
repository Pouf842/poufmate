#ifndef __STATE_H_
#define __STATE_H_

#include "irrlicht.h"
#include "../InterfaceIrrlicht.h"

class State : public irr::IEventReceiver
{
protected:
    Controller                         * mpoController;
	irr::IrrlichtDevice				   * mpoDevice;
	irr::scene::ISceneManager		   * mpoSceneManager;
	irr::scene::ISceneCollisionManager * mpoCollisionManager;
	irr::video::IVideoDriver		   * mpoVideoDriver;
	irr::gui::IGUIEnvironment		   * mpoGUI;
	InterfaceIrrlicht * mpoInterface;
public:
	State(InterfaceIrrlicht * poInterface);
    virtual void Show() = 0;
    virtual void Hide() = 0;
	virtual bool OnEvent(const irr::SEvent &);
};

#endif