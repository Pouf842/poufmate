#include "TestState.h"

using namespace irr;
using namespace scene;
using namespace core;
using namespace video;

#include <iostream>

using namespace std;

#define ID_PIECE 1
extern s32 ID_BOARD;

TestState::TestState(InterfaceIrrlicht * poInterface) : State(poInterface), mpoHighlightedPiece(NULL), mbIsDragging(false)
{
}

void TestState::run()
{
	IrrlichtDevice * poDevice		= mpoInterface->mpoDevice;
	ISceneManager  * poSceneManager = mpoInterface->mpoSceneManager;
	IVideoDriver   * poVideoDriver  = mpoInterface->mpoVideoDriver;

	while(poDevice->run() && !mbStop)
	{
		if(poDevice->isWindowActive())
		{
			poVideoDriver->beginScene();
			poSceneManager->drawAll();

			if(!mbIsDragging)
			{
				vector2d<s32> oMousePos = poDevice->getCursorControl()->getPosition();
				ISceneNode * poHighlightedPiece = mpoInterface->mpoSceneManager->getSceneCollisionManager()->getSceneNodeFromScreenCoordinatesBB(oMousePos, 0, false, mpoInterface->mpoBoardNode);

				if(poHighlightedPiece != mpoHighlightedPiece)
					if(mpoHighlightedPiece)
						mpoHighlightedPiece->getMaterial(0).EmissiveColor = SColor(255, 0, 0, 0);

				if(poHighlightedPiece)
				{
					mpoHighlightedPiece = poHighlightedPiece;
					mpoHighlightedPiece->getMaterial(0).EmissiveColor = SColor(255, 255, 0, 0);
				}
			}

			poVideoDriver->endScene();
		}
		else
			poDevice->yield();
	}
}

bool TestState::OnEvent(const SEvent & oEvent)
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
			else if(oEvent.KeyInput.Key == KEY_SPACE)
				mpoInterface->SwitchCameraType();
		}
	}

	if(oEvent.EventType == EET_MOUSE_INPUT_EVENT)
		if(oEvent.MouseInput.isLeftPressed())
		{
			if(mpoHighlightedPiece)
			{
				mbIsDragging = true;

				vector2d<s32> vMousePos(oEvent.MouseInput.X, oEvent.MouseInput.Y);
				line3df ray = mpoInterface->mpoSceneManager->getSceneCollisionManager()->getRayFromScreenCoordinates(vMousePos);
				vector3df oCollisionPoint;
				triangle3df oTriangle;

				ISceneNode * poNode = mpoInterface->mpoSceneManager->getSceneCollisionManager()->getSceneNodeAndCollisionPointFromRay(ray, oCollisionPoint, oTriangle);
				
				if(poNode)
					mpoHighlightedPiece->setPosition(oCollisionPoint + (0, 0.5, 0));
				else
					cout <<" Node : NULL" << endl;

				return true;
			}
		}
		else
			mbIsDragging = false;

	return false;
}