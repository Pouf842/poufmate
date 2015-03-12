#include "GameState.h"

using namespace irr;

GameState::GameState(InterfaceIrrlicht * poInterface) : State(poInterface)
{
}

bool GameState::OnEvent(const SEvent & oEvent)
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