#ifndef __MENU_STATE_H_
#define __MENU_STATE_H_

#include "State.h"
#include "../InterfaceIrrlicht.h"

class MenuState : public State
{
protected :
	irr::s32 msChoice;
	irr::core::array<irr::gui::IGUIButton *> moButtons;
public :
	MenuState(InterfaceIrrlicht *);

	virtual bool OnEvent(const irr::SEvent &);
	void SetMenu(const irr::core::array<irr::core::string<wchar_t> > &);
	virtual void Run();
	virtual void Stop();
	irr::s32 sGetChoice();
};

#endif