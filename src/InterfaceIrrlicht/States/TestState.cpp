#include "TestState.h"
#include "../Tools.h"

using namespace irr;
using namespace scene;
using namespace core;
using namespace video;

#include <iostream>

using namespace std;

extern s32 ID_BOARD;
extern s32 ID_PIECE;

TestState::TestState(InterfaceIrrlicht * poInterface) : State(poInterface)
{
	list<ISceneNode *> oChildren = mpoInterface->mpoBoardNode->getChildren();

	for(list<ISceneNode *>::Iterator i = oChildren.begin(); i != oChildren.end(); ++i)
		(*i)->setVisible(false);

	ISceneNode * poPiece1 = mpoSceneManager->addMeshSceneNode(mpoInterface->moPiecesMeshs[Piece::PT_PAWN]);
	ISceneNode * poPiece2 = mpoSceneManager->addMeshSceneNode(mpoInterface->moPiecesMeshs[Piece::PT_PAWN]);

	poPiece1->setPosition(vector3df(-1, 0.5, -4));

	poPiece2->setRotation(vector3df(45, 0, 0));
	poPiece2->setPosition(vector3df(+1, 0.5, -4));
}

void TestState::Run()
{
	mbStop = false;

	while(mpoDevice->run() && !mbStop)
	{
		if(mpoDevice->isWindowActive())
		{
			mpoVideoDriver->beginScene();
			mpoSceneManager->drawAll();
			vector3df XAxis[2] = {vector3df(-1000, 0, 0), vector3df(1000, 0, 0)};
			vector3df YAxis[2] = {vector3df(0, -1000, 0), vector3df(0, 1000, 0)};
			vector3df ZAxis[2] = {vector3df(0, 0, -1000), vector3df(0, 0, 1000)};

			mpoVideoDriver->draw3DLine(XAxis[0], XAxis[1], SColor(255, 255, 0, 0));
			mpoVideoDriver->draw3DLine(YAxis[0], YAxis[1], SColor(255, 0, 255, 0));
			mpoVideoDriver->draw3DLine(ZAxis[0], ZAxis[1], SColor(255, 0, 0, 255));

			mpoGUI->drawAll();
			mpoVideoDriver->endScene();
		}
		else
			mpoDevice->yield();
	}
}

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
		}
	}

	return State::OnEvent(oEvent);
}