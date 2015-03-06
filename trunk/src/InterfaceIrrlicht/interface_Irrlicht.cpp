#include "interface_Irrlicht.h"
#include "Pieces/Piece.h"
#include "Intro.h"

#include <iostream>
#include <map>

using namespace std;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace gui;

extern "C" __declspec(dllexport) Interface * poGetInterface()
{
    Interface * poInterface = new InterfaceIrrlicht();

    return poInterface;
}

InterfaceIrrlicht::InterfaceIrrlicht() : mbExit(false)
{
	mpoDevice = createDevice(EDT_OPENGL, dimension2d<u32>(800, 600), 32, false, true, false, this);
	mpoVideoDriver = mpoDevice->getVideoDriver();
	mpoGUI = mpoDevice->getGUIEnvironment();
	mpoSceneManager = mpoDevice->getSceneManager();

	mpoSceneManager->setAmbientLight(SColorf(0.5, 0.5, 0.5));
	mpoSceneManager->addLightSceneNode(0, vector3df(0, 10, 0), SColorf(0.2, 0.2, 0.2));
	/*/ICameraSceneNode * poCamera = mpoSceneManager->addCameraSceneNodeFPS(0, 10, 0.01);
	poCamera->setPosition(vector3df(0, 5, -10));
	poCamera->setTarget(vector3df(0, 0, 0));/*/
	mpoSceneManager->addCameraSceneNode(NULL, vector3df(0, 5, -10), vector3df(0, 0, 0));/**/

	Intro();
}

void InterfaceIrrlicht::Intro()
{
	std::map<Piece::PIECE_TYPE, IMesh*> oPiecesMeshs;
	oPiecesMeshs[Piece::PT_ROOK]   = NULL;
	oPiecesMeshs[Piece::PT_KNIGHT] = NULL;
	oPiecesMeshs[Piece::PT_BISHOP] = NULL;
	oPiecesMeshs[Piece::PT_QUEEN]  = NULL;
	oPiecesMeshs[Piece::PT_KING]   = NULL;
	oPiecesMeshs[Piece::PT_PAWN]   = NULL;

	IMesh * poBoardMesh = mpoSceneManager->getGeometryCreator()->createCubeMesh(vector3df(8, 1, 8));
	IMeshSceneNode * poBoardNode = mpoSceneManager->addMeshSceneNode(poBoardMesh);
	poBoardMesh->drop();
	poBoardNode->setMaterialFlag(EMF_LIGHTING, true);
	ITexture * poBoardTexture = mpoVideoDriver->getTexture("Medias/Images/board.bmp");
	poBoardNode->setMaterialTexture(0, poBoardTexture);

	for(std::map<Piece::PIECE_TYPE, IMesh*>::iterator i = oPiecesMeshs.begin(); i != oPiecesMeshs.end(); ++i)
	{
		irr::core::string<char> strMeshFile = "Medias/";
		switch(i->first)
		{
		  case Piece::PT_ROOK :
			strMeshFile += "rook.3ds";
			break;
		  case Piece::PT_PAWN :
		  default :
			strMeshFile += "pawn.3ds";//"sydney.md2";
			break;
		}

		i->second = mpoSceneManager->getMesh(strMeshFile);
	}

	/*/for(unsigned int i = 0; i < 8; ++i)/*/unsigned int i = 0;/**/
	{
		mpoSceneManager->addMeshSceneNode(oPiecesMeshs[Piece::PT_PAWN], poBoardNode, -1, vector3df(-3.5 + i, 0.45, -2.5))->setScale(vector3df(0.5, 0.5, 0.5));
		/*mpoSceneManager->addMeshSceneNode(oPiecesMeshs[Piece::PT_PAWN], poBoardNode, -1, vector3df(-3.5 + i, 0.45, -3.5))->setScale(vector3df(0.5, 0.5, 0.5));
		mpoSceneManager->addMeshSceneNode(oPiecesMeshs[Piece::PT_PAWN], poBoardNode, -1, vector3df(-3.5 + i, 0.45,  2.5))->setScale(vector3df(0.5, 0.5, 0.5));
		mpoSceneManager->addMeshSceneNode(oPiecesMeshs[Piece::PT_PAWN], poBoardNode, -1, vector3df(-3.5 + i, 0.45,  3.5))->setScale(vector3df(0.5, 0.5, 0.5));*/
	}

	/**/ISceneNodeAnimator * poRotator = mpoSceneManager->createRotationAnimator(vector3df(0, 5*3.6*0.05, 0));
	ISceneNodeAnimator * poTranslator = mpoSceneManager->createFlyStraightAnimator(vector3df(0, 0, 500), vector3df(0, 0, 0), 2000);

	poBoardNode->addAnimator(poRotator);
	//poBoardNode->addAnimator(poTranslator);

	/*/IntroAnimator * poAnim = new IntroAnimator(vector3df(0, 0, 500), vector3df(0, 0, 0), 2000);
	poBoardNode->addAnimator(poAnim);/**/

	while(mpoDevice->run() && !mbExit)// && !poAnim->bIsDone())
	{
		if(mpoDevice->isWindowActive())
		{
			mpoVideoDriver->beginScene(true, true, SColor(255, 210, 210, 210));
			mpoSceneManager->drawAll();
			mpoVideoDriver->endScene();
		}
		else
			mpoDevice->yield();
	}
}

int InterfaceIrrlicht::iGetMenuEntry(const std::vector<std::string> oMenu)
{
	mpoGUI->addStaticText(L"Faites un choix", rect<s32>(0, 0, 100, 100), true, true, NULL, -1, true);

	while(mpoDevice->run() && !mbExit)
	{
		mpoVideoDriver->beginScene();
		mpoSceneManager->drawAll();
		mpoGUI->drawAll();
		mpoVideoDriver->endScene();
	}

	return 6;
}

Entry InterfaceIrrlicht::oGetEntry()
{
	return Entry(Entry::EC_NONE);
}

void InterfaceIrrlicht::DisplayMessage(const std::string strMessage)
{
}

std::string InterfaceIrrlicht::strGetIPEntry()
{
	return "";
}

std::string InterfaceIrrlicht::strGetPortEntry()
{
	return "";
}

Piece::PIECE_TYPE InterfaceIrrlicht::eGetNewPieceType(const Piece::PIECE_COLOR)
{
	return Piece::PT_NONE;
}

Piece::PIECE_COLOR InterfaceIrrlicht::eGetPlayerColorChoice()
{
	return Piece::PC_BLACK;
}

Entry::ENTRY_COMMAND InterfaceIrrlicht::GameOver(std::string strMessage)
{
	return Entry::EC_NONE;
}

void InterfaceIrrlicht::SetBusy()
{
}

void InterfaceIrrlicht::SetProgress(unsigned int)
{
}

bool InterfaceIrrlicht::OnEvent(const irr::SEvent & oEvent)
{
	if(oEvent.EventType == EET_KEY_INPUT_EVENT
	&& oEvent.KeyInput.Key == KEY_ESCAPE)
	{
		mbExit = true;
		return true;
	}

	return false;
}