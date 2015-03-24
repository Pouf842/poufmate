#include "GameState.h"

using namespace std;
using namespace irr;
using namespace scene;
using namespace core;
using namespace video;
using namespace gui;

extern s32 ID_BOARD;
extern s32 ID_PIECE;

GameState::GameState(InterfaceIrrlicht * poInterface) : State(poInterface), mpoHighlightedPiece(NULL), mbIsDragging(false), moRelColl(0, 0, 0)
{
}

bool GameState::OnEvent(const SEvent & oEvent)
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
			{
				moLastEntry = Entry(Entry::EC_STOP_GAME);
				mbStop = true;
				return true;
			}
		}
	}

	if(oEvent.EventType == EET_MOUSE_INPUT_EVENT)
	{
		if(oEvent.MouseInput.isLeftPressed())
		{
			if(mpoHighlightedPiece)
			{
				if(!mbIsDragging)
				{
					vector3df oPos = mpoHighlightedPiece->getPosition();
					moLastEntry = Entry(Position(round32(oPos.X + 0.5) - 0.5 + 4, 4 - (round32(oPos.Z + 0.5) - 0.5)));
					cout << "Entry : " << moLastEntry.oGetPos().mX << " ; " << moLastEntry.oGetPos().mY << ")" << endl;
					mbStop = true;
				}

				mbIsDragging = true;

				vector2d<s32> vMousePos(oEvent.MouseInput.X, oEvent.MouseInput.Y);
				line3df ray = mpoCollisionManager->getRayFromScreenCoordinates(vMousePos);
				vector3df oBoardCollisionPoint;
				triangle3df oTriangle;

				ISceneNode * poNode = mpoCollisionManager->getSceneNodeAndCollisionPointFromRay(ray, oBoardCollisionPoint, oTriangle, ID_BOARD);
				
				if(poNode)
				{
					vector3df oCameraPos = mpoSceneManager->getActiveCamera()->getPosition();
					/*/vector3df oPieceCollisionPoint = mpoHighlightedPiece->getAbsolutePosition() + moRelColl.Y;
					vector3df v1 = oPieceCollisionPoint - oBoardCollisionPoint;
					vector3df v2 = oCameraPos - oBoardCollisionPoint;
					v2.Y = 0;
					vector3df vNewPos = v2 * (v1.dotProduct(v2) / v2.getLengthSQ());

					mpoHighlightedPiece->setPosition(oBoardCollisionPoint + vNewPos);/*/
					vector3df v = oCameraPos - oBoardCollisionPoint;
					v.Y = 0;

					float a = (moRelColl.Y - oBoardCollisionPoint.Y) * v.getLength();
					a /= oCameraPos.Y - oBoardCollisionPoint.Y;

					v.normalize() * a;

					vector3df oPos(oBoardCollisionPoint + v);

					if(oPos.X < -4)
						oPos.X = -4;

					if(oPos.Z < -4)
						oPos.Z = -4;

					oPos.Y = 0.5;
					mpoHighlightedPiece->setPosition(oPos);/**/
				}
			}
		}
		else
		{
			if(mbIsDragging)
			{
				vector3df oPos(mpoHighlightedPiece->getPosition());
				oPos.X = round32(oPos.X + 0.5) - 0.5;
				oPos.Z = round32(oPos.Z + 0.5) - 0.5;
				mpoHighlightedPiece->setPosition(oPos);
				mbIsDragging = false;

				moLastEntry = Entry(Position(oPos.X + 4, 4 - oPos.Z));
				mbStop = true;
			}
				
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
				mpoHighlightedPiece = poHighlightedPiece;
				mpoHighlightedPiece->getMaterial(0).EmissiveColor = SColor(255, 255, 0, 0);
			}
		}

		return true;
	}

	return State::OnEvent(oEvent);
}

Entry GameState::oGetLastEntry() const
{
	return moLastEntry;
}

void GameState::Run()
{
	State::Run();

	if(!mbStop) // If we quit without having set mbStop to true, that's because the window was closed
		moLastEntry = Entry(Entry::EC_QUIT_GAME);
}