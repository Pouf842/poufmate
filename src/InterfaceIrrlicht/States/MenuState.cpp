#include "MenuState.h"
#include "Controller.h"

using namespace irr;
using namespace core;
using namespace gui;

MenuState::MenuState(InterfaceIrrlicht * poInterface) : State(poInterface)
{
}

bool MenuState::OnEvent(const SEvent & oEvent)
{
	if(oEvent.EventType == EET_KEY_INPUT_EVENT
	&& oEvent.KeyInput.Key == KEY_ESCAPE
	&& !oEvent.KeyInput.PressedDown)
	{
        mpoInterface->mpoController->SetMenuChoice(moButtons[moButtons.size() - 2]->getID());
		return true;
	}
	else if(oEvent.EventType == EET_GUI_EVENT
	&& oEvent.GUIEvent.EventType == EGET_BUTTON_CLICKED)
	{
        if(oEvent.GUIEvent.Caller == moButtons.getLast())
        {
            mpoInterface->SetPieceViewerState();
        }

        mpoInterface->mpoController->SetMenuChoice(oEvent.GUIEvent.Caller->getID());
		return true;
	}

	return State::OnEvent(oEvent);
}

void MenuState::Show()
{
    for(s32 i = 0; i < moButtons.size(); ++i)
        moButtons[i]->setVisible(true);
}

void MenuState::Hide()
{
    for(s32 i = 0; i < moButtons.size(); ++i)
        moButtons[i]->setVisible(false);
}

void MenuState::SetMenu(const array<string<wchar_t> > & oMenu)
{
	IGUIEnvironment * poGUI = mpoDevice->getGUIEnvironment();

	for(s32 i = 0; i < moButtons.size(); ++i)
		moButtons[i]->remove();

	moButtons.clear();

	s32 sMenuSize = oMenu.size();
	for(s32 s = 0; s < sMenuSize; ++s)
		moButtons.push_back(poGUI->addButton(rect<s32>(0, 600 / (sMenuSize + 1) * s, 800, 600 / (sMenuSize + 1) * (s + 1)), NULL, s + 1, string<wchar_t>(oMenu[s]).c_str(), L"Tooltip"));

	moButtons.push_back(poGUI->addButton(rect<s32>(0, 600 / (sMenuSize + 1) * sMenuSize, 800, 600), NULL, sMenuSize + 1, L"Piece viewer"));
}

/*void MenuState::Stop()
{
	for(s32 i = 0; i < moButtons.size(); ++i)
		moButtons[i]->setVisible(false);
}*/