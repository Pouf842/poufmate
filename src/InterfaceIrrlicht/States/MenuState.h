#ifndef __MENU_STATE_H_
#define __MENU_STATE_H_

#include "State.h"
#include "../InterfaceIrrlicht.h"

class MenuState : public State
{
protected :
	irr::core::array<irr::gui::IGUIButton *> moButtons;
public :
	MenuState(InterfaceIrrlicht *);

    virtual bool OnEvent(const irr::SEvent &);
    virtual void Show();
    virtual void Hide();
	void SetMenu(const irr::core::array<irr::core::string<wchar_t> > &);
};

#endif