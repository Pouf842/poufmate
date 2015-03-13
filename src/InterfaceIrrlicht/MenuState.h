#ifndef __MENU_STATE_H_
#define __MENU_STATE_H_

#include "State.h"
#include "InterfaceIrrlicht.h"

class MenuState : public State
{
protected :
	irr::s32 msChoice;
	std::vector<irr::gui::IGUIButton *> moButtons;
public :
	MenuState(InterfaceIrrlicht *);

	virtual bool OnEvent(const irr::SEvent &);
	void SetMenu(const std::vector<std::string> &);
	virtual void Stop();
	irr::s32 sGetChoice();
};

#endif