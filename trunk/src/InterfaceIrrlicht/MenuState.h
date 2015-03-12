#ifndef __MENU_STATE_H_
#define __MENU_STATE_H_

#include "State.h"
#include "interface_Irrlicht.h"

class MenuState : public State
{
protected :
	irr::s32 msChoice;
public :
	MenuState(InterfaceIrrlicht *, const std::vector<std::string> &);

	virtual bool OnEvent(const irr::SEvent &);
	irr::s32 sGetChoice();
};

#endif