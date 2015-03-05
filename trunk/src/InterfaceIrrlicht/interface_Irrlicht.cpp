#include "interface_Irrlicht.h"
#include "Pieces/Piece.h"

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

InterfaceIrrlicht::InterfaceIrrlicht()
{
	mpoDevice = createDevice(EDT_OPENGL, dimension2d<u32>(800, 600), 32, false, true, false, NULL);
	mpoVideoDriver = mpoDevice->getVideoDriver();
	mpoGUI = mpoDevice->getGUIEnvironment();
	mpoSceneManager = mpoDevice->getSceneManager();

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

	for(std::map<Piece::PIECE_TYPE, IMesh*>::iterator i = oPiecesMeshs.begin(); i != oPiecesMeshs.end(); ++i)
	{
		irr::core::string<char> strMeshFile = "medias/";
		switch(i->first)
		{
		  case Piece::PT_ROOK :
			strMeshFile += "rook.3ds";
			break;
		  case Piece::PT_PAWN :
		  default :
			strMeshFile += "pawn.3ds";
			break;
		}

		i->second = mpoSceneManager->getMesh(strMeshFile);
	}

/*	ISceneNode * poNode = mpoSceneManager->addMeshSceneNode(oPiecesMeshs[Piece::PT_PAWN]);
	mpoSceneManager->addLightSceneNode(0, vector3df(0, 10, 0), SColorf(0.2, 0.2, 0.2));
	mpoSceneManager->setAmbientLight(SColorf(0.5, 0.5, 0.5));

	poNode->setPosition(vector3df(0, 0, 5));
	poNode->setMaterialFlag(EMF_LIGHTING, true);
	mpoSceneManager->addCameraSceneNodeFPS(0, 10, 0.01);*/

	while(mpoDevice->run())
	{
		/*mpoVideoDriver->beginScene(true, true, SColor(255, 180, 180, 180));
		mpoSceneManager->drawAll();
		mpoVideoDriver->endScene();*/
	}
}

int InterfaceIrrlicht::iGetMenuEntry(const std::vector<std::string> oMenu)
{
	mpoGUI->addStaticText(L"Faites un choix", rect<s32>(0, 0, 100, 100), true, true, NULL, -1, true);

	while(mpoDevice->run())
	{
		mpoVideoDriver->beginScene();
		mpoGUI->drawAll();
		mpoVideoDriver->endScene();
	}

	return 0;
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

bool InterfaceIrrlicht::OnEvent(const irr::SEvent &)
{
	return false;
}