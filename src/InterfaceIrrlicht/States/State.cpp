#include "State.h"

using namespace irr;
using namespace gui;

State::State(InterfaceIrrlicht * poInterface) : mpoInterface(poInterface)
{
	mpoDevice			= mpoInterface->mpoDevice;
	mpoSceneManager		= mpoInterface->mpoSceneManager;
	mpoGUI				= mpoSceneManager->getGUIEnvironment();
	mpoVideoDriver		= mpoInterface->mpoVideoDriver;
	mpoCollisionManager = mpoSceneManager->getSceneCollisionManager();
}

bool State::OnEvent(const SEvent &)
{
    return false;
}

void State::Draw()
{
}