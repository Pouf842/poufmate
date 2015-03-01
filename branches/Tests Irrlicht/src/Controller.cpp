#include "Controller.h"

#include <iostream>
#include <exception>
#include <string>

using namespace std;
using namespace irr;

bool Controller::OnEvent(const SEvent & oEvent)
{
	if(oEvent.EventType == EET_KEY_INPUT_EVENT)
	{
		if(oEvent.KeyInput.Key == KEY_ESCAPE)
			mbExit = true;
		else if(oEvent.KeyInput.Key == KEY_MULTIPLY)
			mbAutoStop = true;

		mbKeysDown[oEvent.KeyInput.Key] = oEvent.KeyInput.PressedDown;
		return true;
	}
	else if(oEvent.EventType == EET_MOUSE_INPUT_EVENT
		 && oEvent.MouseInput.Event == EMIE_MOUSE_MOVED)
	{
		moMouseState = oEvent.MouseInput;
	}
	else if(oEvent.EventType == EET_JOYSTICK_INPUT_EVENT)
		moJoystickState = oEvent.JoystickEvent;

	return false;
}

bool Controller::bIsKeyDown(EKEY_CODE keyCode)
{
	if(keyCode < 0 || keyCode >= KEY_KEY_CODES_COUNT)
	{
		std::string strError = __FILE__;
		strError.append(".").append("-");
		strError += __LINE__;
		strError.append(" : Controller.IsKeyDown : Unknown key code : ");
		strError += keyCode;
		throw exception(strError.c_str());
	}

	return mbKeysDown[keyCode];
}

Controller::Controller() : mbExit(false),
						   mbAutoStop(false),
						   moJoystickState(),
						   moMouseState()
{
	for(u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
		mbKeysDown[i] = false;
}

bool Controller::bExit()
{
	return mbExit;
}

bool Controller::bAutoStop()
{
	return mbAutoStop;
}

void Controller::stopAutoStop()
{
	mbAutoStop = false;
}

irr::SEvent::SJoystickEvent Controller::oGetJoystickState()
{
	return moJoystickState;
}

irr::SEvent::SMouseInput Controller::oGetMouseState()
{
	return moMouseState;
}