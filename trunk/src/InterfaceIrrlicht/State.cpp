#include "State.h"

State::State(InterfaceIrrlicht * poInterface) : mpoInterface(poInterface), mbStop(false)
{
}

void State::Run()
{
	while(mpoInterface->mpoDevice->run() && !mbStop)
	{
		if(mpoInterface->mpoDevice->isWindowActive())
		{
			mpoInterface->mpoVideoDriver->beginScene();
			mpoInterface->mpoSceneManager->drawAll();
			mpoInterface->mpoGUI->drawAll();
			mpoInterface->mpoVideoDriver->endScene();
		}
		else
			mpoInterface->mpoDevice->yield();
	}
}

bool State::OnEvent(const irr::SEvent &)
{
	return false;
}

void State::Stop()
{
	mbStop = true;
}