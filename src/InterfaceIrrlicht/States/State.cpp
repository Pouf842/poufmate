#include "State.h"

using namespace irr;
using namespace gui;

State::State(InterfaceIrrlicht * poInterface) : mpoInterface(poInterface), mbStop(false)
{
	mpoDevice			= mpoInterface->mpoDevice;
	mpoSceneManager		= mpoInterface->mpoSceneManager;
	mpoGUI				= mpoSceneManager->getGUIEnvironment();
	mpoVideoDriver		= mpoInterface->mpoVideoDriver;
	mpoCollisionManager = mpoSceneManager->getSceneCollisionManager();
}

void State::Run()
{
	mbStop = false;

	while(mpoDevice->run() && !mbStop)
	{
		if(mpoDevice->isWindowActive())
		{
			mpoVideoDriver->beginScene();
			mpoSceneManager->drawAll();
			mpoGUI->drawAll();
			mpoVideoDriver->endScene();
		}
		else
			mpoDevice->yield();
	}
}

bool State::OnEvent(const SEvent & oEvent)
{
	if(oEvent.EventType == EET_KEY_INPUT_EVENT)
	{
		if(!oEvent.KeyInput.PressedDown)
		{
			if(oEvent.KeyInput.Key == KEY_ESCAPE)
			{
				mbStop = true;
				return true;
			}
		}
	}

	return false;
}

bool State::bIsRunning()
{
	return !mbStop;
}

void State::Stop()
{
	mbStop = true;
}