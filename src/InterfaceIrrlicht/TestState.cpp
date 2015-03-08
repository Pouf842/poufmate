#include "TestState.h"

using namespace irr;
using namespace scene;
using namespace core;
using namespace video;

#include <iostream>

using namespace std;

#define ID_PIECE 1

TestState::TestState(InterfaceIrrlicht * poInterface) : State(poInterface), mpoHighlightedPiece(NULL)
{
	// White pawn
	IMeshSceneNode * poPawn = mpoInterface->mpoSceneManager->addMeshSceneNode(mpoInterface->moPiecesMeshs[Piece::PT_PAWN], mpoInterface->mpoBoardNode);
	poPawn->setPosition(vector3df(-3, 0.45, 3));
	poPawn->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
	poPawn->setScale(vector3df(0.3, 0.3, 0.3));
	poPawn->getMaterial(0).AmbientColor.set(255, 255, 255, 255);

	// Black pawn
	poPawn = mpoInterface->mpoSceneManager->addMeshSceneNode(mpoInterface->moPiecesMeshs[Piece::PT_PAWN], mpoInterface->mpoBoardNode);
	poPawn->setPosition(vector3df(3, 0.45, 3));
	poPawn->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
	poPawn->setScale(vector3df(0.3, 0.3, 0.3));
	poPawn->getMaterial(0).AmbientColor.set(255, 10, 10, 10);

	// White rook
	IMeshSceneNode * poRook = mpoInterface->mpoSceneManager->addMeshSceneNode(mpoInterface->moPiecesMeshs[Piece::PT_ROOK], mpoInterface->mpoBoardNode);
	poRook->setPosition(vector3df(-3, 0.45, -3));
	poRook->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
	poRook->setScale(vector3df(0.5, 0.5, 0.5));
	poRook->getMaterial(0).AmbientColor.set(255, 255, 255, 255);

	// Black rook
	poRook = mpoInterface->mpoSceneManager->addMeshSceneNode(mpoInterface->moPiecesMeshs[Piece::PT_ROOK], mpoInterface->mpoBoardNode);
	poRook->setPosition(vector3df(3, 0.45, -3));
	poRook->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
	poRook->setScale(vector3df(0.5, 0.5, 0.5));
	poRook->getMaterial(0).AmbientColor.set(255, 10, 10, 10);
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

			vector2d<s32> oMousePos = poDevice->getCursorControl()->getPosition();
			ISceneNode * poHighlightedPiece = mpoInterface->mpoSceneManager->getSceneCollisionManager()->getSceneNodeFromScreenCoordinatesBB(oMousePos, 0, false, mpoInterface->mpoBoardNode);

			if(poHighlightedPiece)
			{
				if(mpoHighlightedPiece)
				{
					mpoHighlightedPiece->getMaterial(0);
				}

				mpoHighlightedPiece = poHighlightedPiece;
				mpoHighlightedPiece->getMaterial(0);
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
		if(!oEvent.KeyInput.PressedDown)
			if(oEvent.KeyInput.Key == KEY_ESCAPE)
			{
				mbStop = true;
				return true;
			}

	return false;
}