#include "PieceViewerState.h"
#include "../../Tools.h"

#include <iostream>

using namespace irr;
using namespace video;
using namespace scene;
using namespace core;

PieceViewerState::PieceViewerState(InterfaceIrrlicht * poInterface) : State(poInterface),
																	  mbPresentingPieces(false),
																	  mpoCurrentPiece(NULL),
																	  mbCurrentPieceWhite(true),
																	  mbChangingColor(false)
{
	mpoAnimator = new PieceViewerAnimator();
	mpoLight = mpoSceneManager->addLightSceneNode(mpoSceneManager->getActiveCamera(), vector3df(0, 5, 0), SColorf(0.2, 0.2, 0.2), 10);
	mpoLight->setVisible(false);
}

bool PieceViewerState::OnEvent(const SEvent & oEvent)
{
	if(oEvent.EventType == EET_KEY_INPUT_EVENT)
		if(!oEvent.KeyInput.PressedDown)
		{
			if(!mbPresentingPieces)
			{
				if(oEvent.KeyInput.Key == KEY_LEFT)
				{
					NextPiece((Piece::PIECE_TYPE) (meCurrentType == 0 ? Piece::PT_NONE - 1 : meCurrentType - 1), true);
					return true;
				}
				else if(oEvent.KeyInput.Key == KEY_RIGHT)
				{
					NextPiece((Piece::PIECE_TYPE) (meCurrentType == Piece::PT_NONE - 1 ? Piece::PT_PAWN : meCurrentType + 1));
					return true;
				}
				else if(oEvent.KeyInput.Key == KEY_SPACE)
				{
					if(!mbChangingColor)
						mbChangingColor = true;
				}
			}
		}

	return State::OnEvent(oEvent);
}

void PieceViewerState::NextPiece(Piece::PIECE_TYPE eType, bool bLeft)
{
	mbPresentingPieces = true;

	s32 sLeft = (bLeft ? -1 : 1);

	ICameraSceneNode * poCamera = mpoSceneManager->getActiveCamera();

	ISceneNode * poNewPiece = mpoSceneManager->addMeshSceneNode(mpoInterface->moPiecesMeshes[eType], poCamera, -1);
	s32 sPieceHeight = poNewPiece->getBoundingBox().MaxEdge.Y - poNewPiece->getBoundingBox().MinEdge.Y;
	vector3df oPosBase(-7 / 2 * sLeft, -sPieceHeight / 2, 0);
	vector3df oPos(oPosBase);
	poNewPiece->setPosition(oPos);

	vector3df oCurrentPiecePos;

	if(mpoCurrentPiece)
		oCurrentPiecePos = mpoCurrentPiece->getPosition(); 

	u32 uStart = mpoDevice->getTimer()->getTime();

	bool bOver = false;
	float TOTAL_TRANS_TIME = 1200;

	matrix4 mRotMatrix;

	if(mpoCurrentPiece)
		mpoCurrentPiece->removeAnimator(mpoAnimator);

	while(mpoDevice->run() && !bOver)
	{
		mpoVideoDriver->beginScene();
		mpoSceneManager->drawAll();
		mpoGUI->drawAll();
		mpoVideoDriver->endScene();

		u32 uNow = mpoDevice->getTimer()->getTime();
		float fFactor = (uNow - uStart) / TOTAL_TRANS_TIME;

		if(fFactor > 1)
		{
			fFactor = 1;
			bOver = true;
		}

		fFactor *= PI / 2;
		fFactor = sin(fFactor);

		float fDegrees = 90 * fFactor * sLeft;
		mRotMatrix.setRotationDegrees(vector3df(0, fDegrees, 0));
		oPos = oPosBase;
		mRotMatrix.transformVect(oPos);
		poNewPiece->setPosition(oPos);

		if(mpoCurrentPiece)
		{
			oPos = oCurrentPiecePos;
			//mRotMatrix.setRotationDegrees(vector3df(0, fDegrees + (90 * sLeft), 0));
			mRotMatrix.transformVect(oPos);
			mpoCurrentPiece->setPosition(oPos);
		}
	}

	if(mpoCurrentPiece)
		mpoCurrentPiece->remove();

	meCurrentType = eType;
	mpoCurrentPiece = poNewPiece;	

	matrix4 mPieceWorld = mpoCurrentPiece->getRelativeTransformation();
	vector3df vOffset = vector3df(0, ((float) sPieceHeight) / 2, 0);
	mPieceWorld.transformVect(vOffset);
	mpoAnimator->SetPivot(vOffset);

	mpoCurrentPiece->addAnimator(mpoAnimator);
	mpoAnimator->Start(mpoDevice->getTimer()->getTime());

	mbCurrentPieceWhite = true;
	mbPresentingPieces = false;
}

void PieceViewerState::PresentPieces()
{
	NextPiece(Piece::PT_PAWN);
	float fFactor = 1.0f;

	while(mpoDevice->run() && !mbStop)
	{
		if(mpoDevice->isWindowActive())
		{
			mpoVideoDriver->beginScene();

			if(mbChangingColor)
			{
				fFactor += (mbCurrentPieceWhite ? -0.01f : 0.01f);

				if(fFactor < 0
				|| fFactor > 1)
					fFactor = round32(fFactor);

				SColor oAmbientColor(255, 220, 220, 220);
				SColor oDiffuseColor(255, 255, 255, 255);

				mpoCurrentPiece->getMaterial(0).AmbientColor.set(oAmbientColor.getAlpha(), oAmbientColor.getRed() * fFactor, oAmbientColor.getGreen() * fFactor, oAmbientColor.getBlue() * fFactor);
				mpoCurrentPiece->getMaterial(0).DiffuseColor.set(oDiffuseColor.getAlpha(), oDiffuseColor.getRed() * fFactor, oDiffuseColor.getGreen() * fFactor, oDiffuseColor.getBlue() * fFactor);

				if(fFactor == 0
				|| fFactor == 1)
				{
					mbChangingColor = false;
					mbCurrentPieceWhite = (fFactor == 1);
				}
			}

			mpoSceneManager->drawAll();
			mpoGUI->drawAll();
			mpoVideoDriver->endScene();
		}
		else
			mpoDevice->yield();
	}

	mpoCurrentPiece->removeAnimator(mpoAnimator);
	mpoCurrentPiece->setPosition(mpoCurrentPiece->getAbsolutePosition());
	mpoCurrentPiece->setRotation(mpoCurrentPiece->getAbsoluteTransformation().getRotationDegrees());
	mpoCurrentPiece->setParent(mpoSceneManager->getRootSceneNode());
}

PieceViewerState::~PieceViewerState()
{
	mpoLight->remove();
	mpoAnimator->drop();
}

void PieceViewerState::Run()
{
	mbStop = false;

	mpoInterface->RotateCamera(0, 90, 0);
	mpoLight->setVisible(true);
	PresentPieces();
	mpoInterface->RotateCamera(0, -90, 0);
	mpoLight->setVisible(false);

	mpoCurrentPiece->remove();
	mpoCurrentPiece = NULL;
}