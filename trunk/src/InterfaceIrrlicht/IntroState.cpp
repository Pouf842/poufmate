#include "IntroState.h"
#include "IntroAnimator.h"

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;

IntroState::IntroState(InterfaceIrrlicht * poInterface) : State(poInterface), mpoAnimator(NULL)
{
	mpoInterface->mpoDevice->setEventReceiver(this);

	IMeshSceneNode * poNode;
	ISceneNode * poBoardNode = mpoInterface->mpoBoardNode;
	ISceneManager * poSceneManager = mpoInterface->mpoSceneManager;
	std::map<Piece::PIECE_TYPE, IMesh *> & oPiecesMeshs = mpoInterface->moPiecesMeshs;

	/**/for(unsigned int i = 0; i < 8; ++i)/*/unsigned int i = 0;/**/
	{
		// Pawns
		poNode = mpoInterface->mpoSceneManager->addMeshSceneNode(oPiecesMeshs[Piece::PT_PAWN], mpoInterface->mpoBoardNode, -1, vector3df(-3.5 + i, 0.5, -2.5));
		poNode->setScale(vector3df(0.5, 0.5, 0.5));
		poNode->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
		poNode->getMaterial(0).AmbientColor  = SColor(255, 220, 220, 220);
		poNode->getMaterial(0).SpecularColor = SColor(255, 255, 255, 255);

		poNode = mpoInterface->mpoSceneManager->addMeshSceneNode(oPiecesMeshs[Piece::PT_PAWN], mpoInterface->mpoBoardNode, -1, vector3df(-3.5 + i, 0.5, +2.5));
		poNode->setScale(vector3df(0.5, 0.5, 0.5));
		poNode->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
		poNode->getMaterial(0).AmbientColor = SColor(255, 0, 0, 0);
		poNode->getMaterial(0).DiffuseColor = SColor(255, 0, 0, 0);
		
		// Rooks
		poNode = mpoInterface->mpoSceneManager->addMeshSceneNode(oPiecesMeshs[Piece::PT_ROOK], mpoInterface->mpoBoardNode, -1, vector3df(-3.5 + i, 0.5, -3.5));
		poNode->setScale(vector3df(0.5, 0.5, 0.5));
		poNode->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
		poNode->getMaterial(0).AmbientColor = SColor(255, 220, 220, 220);

		poNode = mpoInterface->mpoSceneManager->addMeshSceneNode(oPiecesMeshs[Piece::PT_ROOK], mpoInterface->mpoBoardNode, -1, vector3df(-3.5 + i, 0.5, +3.5));
		poNode->setScale(vector3df(0.5, 0.5, 0.5));
		poNode->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
		poNode->getMaterial(0).AmbientColor = SColor(255, 0, 0, 0);
		poNode->getMaterial(0).DiffuseColor = SColor(255, 0, 0, 0);
	}

	mpoAnimator = new IntroAnimator(vector3df(0, 0, 500), vector3df(0, 0, 0), 2000);
	poBoardNode->addAnimator(mpoAnimator);
}

IntroState::~IntroState()
{
	mpoInterface->mpoBoardNode->setPosition(vector3df(0, 0, 0));
	mpoInterface->mpoBoardNode->setRotation(vector3df(0, 0, 0));
	mpoInterface->mpoBoardNode->removeAnimator(mpoAnimator);
	delete mpoAnimator;
}

bool IntroState::OnEvent(const irr::SEvent & oEvent)
{
	if(oEvent.EventType == EET_KEY_INPUT_EVENT)
		if(!oEvent.KeyInput.PressedDown)
		{
			if(oEvent.KeyInput.Key == KEY_ESCAPE)
			{
				mbStop = true;
				return true;
			}
		}

	return false;
}