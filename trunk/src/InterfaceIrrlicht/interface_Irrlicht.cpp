#include "interface_Irrlicht.h"
#include "Pieces/Piece.h"
#include "IntroState.h"
#include "TestState.h"

#include <iostream>

using namespace std;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace gui;

s32 ID_BOARD = 1;

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

	InitMeshs();

	/*/ISceneNode * poPawn = mpoSceneManager->addMeshSceneNode(moPiecesMeshs[Piece::PT_PAWN]);
	poPawn->setPosition(vector3df(-5, 0, 0));
	poPawn->setMaterialFlag(EMF_LIGHTING, true);
	ISceneNode * poRook = mpoSceneManager->addMeshSceneNode(moPiecesMeshs[Piece::PT_ROOK]);
	poRook->setPosition(vector3df(5, 0, 0));
	poRook->setMaterialFlag(EMF_LIGHTING, true);/*/
	SetState(new IntroState(this));
	SetState(new TestState(this));
}

void InterfaceIrrlicht::InitMeshs()
{
	moPiecesMeshs[Piece::PT_ROOK]   = NULL;
	moPiecesMeshs[Piece::PT_KNIGHT] = NULL;
	moPiecesMeshs[Piece::PT_BISHOP] = NULL;
	moPiecesMeshs[Piece::PT_QUEEN]  = NULL;
	moPiecesMeshs[Piece::PT_KING]   = NULL;
	moPiecesMeshs[Piece::PT_PAWN]   = NULL;

	mpoBoardMesh = mpoSceneManager->getGeometryCreator()->createCubeMesh(vector3df(8, 1, 8));
	mpoBoardNode = mpoSceneManager->addMeshSceneNode(mpoBoardMesh);
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
}

int InterfaceIrrlicht::iGetMenuEntry(const std::vector<std::string> oMenu)
{
	//SetState(IIS_MENU);

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

void InterfaceIrrlicht::SetState(State * poNewState)
{
	if(mpoCurrentState)
		delete mpoCurrentState;

	mpoCurrentState = poNewState;
	mpoDevice->setEventReceiver(mpoCurrentState);
	poNewState->run();
}

bool InterfaceIrrlicht::OnEvent(const SEvent &)
{
	return false;
}

void InterfaceIrrlicht::SwitchCameraType()
{
	mpoSceneManager->setActiveCamera(mpoCurrentCamera == mpoCameraFPS ? mpoCamera : mpoCameraFPS);
}