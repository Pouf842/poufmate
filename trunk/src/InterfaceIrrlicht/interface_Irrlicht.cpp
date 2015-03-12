#include "interface_Irrlicht.h"
#include "Pieces/Piece.h"
#include "IntroState.h"
#include "TestState.h"
#include "MenuState.h"
#include "GameState.h"

#include <iostream>

using namespace std;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace gui;

s32 ID_BOARD = 1;
s32 ID_PIECE = 2;

extern "C" __declspec(dllexport) Interface * poGetInterface()
{
    Interface * poInterface = new InterfaceIrrlicht();

    return poInterface;
}

InterfaceIrrlicht::InterfaceIrrlicht() : mpoCurrentState(NULL), mpoCameraFPS(NULL), mpoCamera(NULL), mpoCurrentCamera(NULL)
{
	mpoDevice = createDevice(EDT_OPENGL, dimension2d<u32>(800, 600), 32, false, true, false, this);
	mpoVideoDriver = mpoDevice->getVideoDriver();
	mpoGUI = mpoDevice->getGUIEnvironment();
	mpoSceneManager = mpoDevice->getSceneManager();

	mpoSceneManager->setAmbientLight(SColorf(0.8, 0.8, 0.8));
	mpoSceneManager->addLightSceneNode(0, vector3df(0, 10, 0), SColorf(0.2, 0.2, 0.2), 10);

	mpoCameraFPS = mpoSceneManager->addCameraSceneNodeFPS(0, 10, 0.01);
	mpoCameraFPS->setPosition(vector3df(0, 5, -10));
	mpoCameraFPS->setTarget(vector3df(0, 0, 0));

	mpoCamera = mpoSceneManager->addCameraSceneNode(NULL, vector3df(0, 5, -10), vector3df(0, 0, 0));

	InitDatas();

	SetState(new IntroState(this));
	delete mpoCurrentState;
	mpoCurrentState = NULL;
	SetState(new TestState(this));
	delete mpoCurrentState;
	mpoCurrentState = NULL;

	
	mpoMenuState = new MenuState(this);
	mpoGameState = new GameState(this);
}

void InterfaceIrrlicht::InitDatas()
{
	moPiecesMeshs[Piece::PT_ROOK]   = NULL;
	moPiecesMeshs[Piece::PT_KNIGHT] = NULL;
	moPiecesMeshs[Piece::PT_BISHOP] = NULL;
	moPiecesMeshs[Piece::PT_QUEEN]  = NULL;
	moPiecesMeshs[Piece::PT_KING]   = NULL;
	moPiecesMeshs[Piece::PT_PAWN]   = NULL;

	mpoBoardMesh = mpoSceneManager->getGeometryCreator()->createCubeMesh(vector3df(8, 1, 8));
	mpoBoardNode = mpoSceneManager->addMeshSceneNode(mpoBoardMesh, NULL, ID_BOARD);
	mpoBoardNode->setName("Board");
	mpoBoardNode->setTriangleSelector(mpoSceneManager->createTriangleSelector(mpoBoardMesh, mpoBoardNode));
	mpoBoardNode->setMaterialFlag(EMF_LIGHTING, true);
	ITexture * poBoardTexture = mpoVideoDriver->getTexture("Medias/Images/board.bmp");
	mpoBoardNode->setMaterialTexture(0, poBoardTexture);
	//mpoBoardNode->setID(0);

	for(std::map<Piece::PIECE_TYPE, IMesh*>::iterator i = moPiecesMeshs.begin(); i != moPiecesMeshs.end(); ++i)
	{
		irr::core::string<char> strMeshFile = "Medias/";
		switch(i->first)
		{
		  case Piece::PT_ROOK :
			strMeshFile += /*/"rook.3ds";/*/"rook.b3d";/**/
			break;
		  case Piece::PT_PAWN :
		  default :
			strMeshFile += /*/"pawn.3ds";/*/"pawn.b3d";/**/
			break;
		}

		i->second = mpoSceneManager->getMesh(strMeshFile);
	}
	
	ISceneNode * poNode;
	/**/for(unsigned int i = 0; i < 8; ++i)/*/unsigned int i = 0;/**/
	{
		// Pawns
		poNode = mpoSceneManager->addMeshSceneNode(moPiecesMeshs[Piece::PT_PAWN], mpoBoardNode, ID_PIECE, vector3df(-3.5 + i, 0.5, -2.5));
		poNode->setScale(vector3df(0.5, 0.5, 0.5));
		poNode->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
		poNode->getMaterial(0).AmbientColor  = SColor(255, 220, 220, 220);
		poNode->getMaterial(0).SpecularColor = SColor(255, 255, 255, 255);
		poNode->setTriangleSelector(mpoSceneManager->createTriangleSelector(moPiecesMeshs[Piece::PT_PAWN], poNode));
		std::string str("White pawn n°");
		str += (i + '0');
		poNode->setName(str.c_str());

		poNode = mpoSceneManager->addMeshSceneNode(moPiecesMeshs[Piece::PT_PAWN], mpoBoardNode, ID_PIECE, vector3df(-3.5 + i, 0.5, +2.5));
		poNode->setScale(vector3df(0.5, 0.5, 0.5));
		poNode->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
		poNode->getMaterial(0).AmbientColor = SColor(255, 0, 0, 0);
		poNode->getMaterial(0).DiffuseColor = SColor(255, 0, 0, 0);
		poNode->setTriangleSelector(mpoSceneManager->createTriangleSelector(moPiecesMeshs[Piece::PT_PAWN], poNode));
		str = "Black pawn n°";
		str += (i + '0');
		poNode->setName(str.c_str());
		
		// Rooks
		poNode = mpoSceneManager->addMeshSceneNode(moPiecesMeshs[Piece::PT_ROOK], mpoBoardNode, ID_PIECE, vector3df(-3.5 + i, 0.5, -3.5));
		poNode->setScale(vector3df(0.5, 0.5, 0.5));
		poNode->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
		poNode->getMaterial(0).AmbientColor = SColor(255, 220, 220, 220);
		poNode->setTriangleSelector(mpoSceneManager->createTriangleSelector(moPiecesMeshs[Piece::PT_ROOK], poNode));
		str = "White rook n°";
		str += (i + '0');
		poNode->setName(str.c_str());

		poNode = mpoSceneManager->addMeshSceneNode(moPiecesMeshs[Piece::PT_ROOK], mpoBoardNode, ID_PIECE, vector3df(-3.5 + i, 0.5, +3.5));
		poNode->setScale(vector3df(0.5, 0.5, 0.5));
		poNode->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
		poNode->getMaterial(0).AmbientColor = SColor(255, 0, 0, 0);
		poNode->getMaterial(0).DiffuseColor = SColor(255, 0, 0, 0);
		poNode->setTriangleSelector(mpoSceneManager->createTriangleSelector(moPiecesMeshs[Piece::PT_ROOK], poNode));
		str = "Black rook n°";
		str += (i + '0');
		poNode->setName(str.c_str());
	}
}

int InterfaceIrrlicht::iGetMenuEntry(const std::vector<std::string> oMenu)
{
	mpoMenuState->SetMenu(oMenu);
	SetState(mpoMenuState);

	return mpoMenuState->sGetChoice();
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

void InterfaceIrrlicht::SetState(State * poNewState)
{
	if(mpoCurrentState)
		mpoCurrentState->Stop();

	mpoCurrentState = poNewState;
	mpoDevice->setEventReceiver(mpoCurrentState);

	if(poNewState)
		poNewState->Run();
}

bool InterfaceIrrlicht::OnEvent(const SEvent &)
{
	return false;
}

void InterfaceIrrlicht::SwitchCameraType()
{
	mpoCurrentCamera = mpoCurrentCamera == mpoCameraFPS ? mpoCamera : mpoCameraFPS;
	mpoSceneManager->setActiveCamera(mpoCurrentCamera);
}