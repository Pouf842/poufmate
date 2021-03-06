#include "TestState.h"
#include "../Tools.h"

using namespace irr;
using namespace scene;
using namespace core;
using namespace video;

#include <iostream>

extern s32 ID_BOARD;
extern s32 ID_PIECE;

TestState::TestState(InterfaceIrrlicht * poInterface) : State(poInterface)
{
    /*mpoPlane->getMaterial(0).ColorMask = 0x00FFFF;*/
}

/*void TestState::Update()
{
	vector3df XAxis[2] = {vector3df(-1000, 0, 0), vector3df(1000, 0, 0)};
	vector3df YAxis[2] = {vector3df(0, -1000, 0), vector3df(0, 1000, 0)};
	vector3df ZAxis[2] = {vector3df(0, 0, -1000), vector3df(0, 0, 1000)};

	mpoVideoDriver->draw3DLine(XAxis[0], XAxis[1], SColor(255, 255, 0, 0));
	mpoVideoDriver->draw3DLine(YAxis[0], YAxis[1], SColor(255, 0, 255, 0));
	mpoVideoDriver->draw3DLine(ZAxis[0], ZAxis[1], SColor(255, 0, 0, 255));
}*/

bool TestState::OnEvent(const SEvent & oEvent)
{
	if(oEvent.EventType == EET_KEY_INPUT_EVENT)
	{
		if(!oEvent.KeyInput.PressedDown)
		{
            if(oEvent.KeyInput.Key == KEY_SPACE)
            {
                mpoInterface->SwitchCameraType();
                return true;
            }
            else if(oEvent.KeyInput.Key == KEY_ESCAPE)
                mbStop = true;
		}
	}

	return State::OnEvent(oEvent);
}

void TestState::Show()
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

void TestState::Hide()
{
}