#include "TestState.h"

using namespace irr;
using namespace scene;
using namespace core;
using namespace video;

#include <iostream>

using namespace std;

extern s32 ID_BOARD;
extern s32 ID_PIECE;

ostream & operator<<(ostream & out, const vector3df & oVec)
{
	out << "(" << oVec.X << " ; " << oVec.Y << " ; " << oVec.Z << ")";
	return out;
}

TestState::TestState(InterfaceIrrlicht * poInterface) : State(poInterface), mpoHighlightedPiece(NULL), mbIsDragging(false), moRelColl(0, 0, 0)
{
	mpoDevice			= mpoInterface->mpoDevice;
	mpoSceneManager		= mpoInterface->mpoSceneManager;
	mpoVideoDriver		= mpoInterface->mpoVideoDriver;
	mpoCollisionManager = mpoSceneManager->getSceneCollisionManager();
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
	{
		if(oEvent.MouseInput.isLeftPressed())
		{
			if(mpoHighlightedPiece)
			{
				mbIsDragging = true;

				vector2d<s32> vMousePos(oEvent.MouseInput.X, oEvent.MouseInput.Y);
				line3df ray = mpoCollisionManager->getRayFromScreenCoordinates(vMousePos);
				vector3df oCollisionPoint;
				triangle3df oTriangle;

				ISceneNode * poNode = mpoCollisionManager->getSceneNodeAndCollisionPointFromRay(ray, oCollisionPoint, oTriangle, ID_BOARD);
				
				if(poNode)
				{
					vector3df oCameraPos = mpoSceneManager->getActiveCamera()->getPosition();
					vector3df v = oCameraPos - oCollisionPoint;
					v.Y = 0;

					float a = (moRelColl.Y - oCollisionPoint.Y) * v.getLength();
					a /= oCameraPos.Y - oCollisionPoint.Y;

					v.normalize() * a;

					mpoHighlightedPiece->setPosition(oCollisionPoint + v);
				}

				return true;
			}
		}
		else
		{
			mbIsDragging = false;
				
			/**/vector2d<s32> vMousePos = mpoDevice->getCursorControl()->getPosition();
			line3df ray = mpoCollisionManager->getRayFromScreenCoordinates(vMousePos);
			vector3df oCollisionPoint;

			ISceneNode * poHighlightedPiece = mpoCollisionManager->getSceneNodeAndCollisionPointFromRay(ray, oCollisionPoint, triangle3df(), ID_PIECE);/*/

			vector2d<s32> oMousePos = mpoDevice->getCursorControl()->getPosition();
			ISceneNode * poHighlightedPiece = mpoCollisionManager->getSceneNodeFromScreenCoordinatesBB(oMousePos, ID_PIECE, false, mpoInterface->mpoBoardNode);/**/

			if(poHighlightedPiece != mpoHighlightedPiece)
				if(mpoHighlightedPiece)
					mpoHighlightedPiece->getMaterial(0).EmissiveColor = SColor(0, 0, 0, 0);

			if(poHighlightedPiece)
			{
				moRelColl = oCollisionPoint - poHighlightedPiece->getAbsolutePosition();
				cout << moRelColl.Y << endl;
				mpoHighlightedPiece = poHighlightedPiece;
				mpoHighlightedPiece->getMaterial(0).EmissiveColor = SColor(255, 255, 0, 0);
			}
		}
	}

	return false;
}