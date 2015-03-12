#include "MenuState.h"

using namespace irr;
using namespace core;
using namespace gui;

MenuState::MenuState(InterfaceIrrlicht * poInterface) : State(poInterface), msChoice(-1)
{
}

bool MenuState::OnEvent(const SEvent & oEvent)
{
	if(oEvent.EventType == EET_KEY_INPUT_EVENT
	&& oEvent.KeyInput.Key == KEY_ESCAPE
	&& !oEvent.KeyInput.PressedDown)
	{
		mbStop = true;
		return true;
	}
	else if(oEvent.EventType == EET_GUI_EVENT
	&& oEvent.GUIEvent.EventType == EGET_BUTTON_CLICKED)
	{
		msChoice = oEvent.GUIEvent.Caller->getID();
		mbStop = true;
		return true;
	}

	return false;
}

s32 MenuState::sGetChoice()
{
	return msChoice;
}

void MenuState::SetMenu(const std::vector<std::string> & oMenu)
{
	IGUIEnvironment * poGUI = mpoInterface->mpoDevice->getGUIEnvironment();

	for(s32 i = 0; i < moButtons.size(); ++i)
		moButtons[i]->remove();

	moButtons.clear();

	s32 sMenuSize = oMenu.size();
	for(s32 s = 0; s < sMenuSize; ++s)
		moButtons.push_back(poGUI->addButton(rect<s32>(0, 600 / sMenuSize * s, 800, 600 / sMenuSize * (s + 1)), NULL, s + 1, std::wstring().assign(oMenu[s].begin(), oMenu[s].end()).c_str(), L"Tooltip"));
}

void MenuState::Stop()
{
	for(s32 i = 0; i < moButtons.size(); ++i)
		moButtons[i]->setVisible(false);

	State::Stop();
}