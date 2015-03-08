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
		poNode = poSceneManager->addMeshSceneNode(oPiecesMeshs[Piece::PT_PAWN], poBoardNode, -1, vector3df(-3.5 + i, 0.45, -2.5));
		poNode->setScale(vector3df(0.3, 0.3, 0.3));
		poNode->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
		poNode = poSceneManager->addMeshSceneNode(oPiecesMeshs[Piece::PT_ROOK], poBoardNode, -1, vector3df(-3.5 + i, 0.45, -3.5));
		poNode->setScale(vector3df(0.5, 0.5, 0.5));
		poNode->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
		poNode = poSceneManager->addMeshSceneNode(oPiecesMeshs[Piece::PT_PAWN], poBoardNode, -1, vector3df(-3.5 + i, 0.45,  2.5));
		poNode->setScale(vector3df(0.3, 0.3, 0.3));
		poNode->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
		poNode = poSceneManager->addMeshSceneNode(oPiecesMeshs[Piece::PT_ROOK], poBoardNode, -1, vector3df(-3.5 + i, 0.45,  3.5));
		poNode->setScale(vector3df(0.5, 0.5, 0.5));
		poNode->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
	}

	mpoAnimator = new IntroAnimator(vector3df(0, 0, 500), vector3df(0, 0, 0), 2000);
	poBoardNode->addAnimator(mpoAnimator);
}

IntroState::~IntroState()
{
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