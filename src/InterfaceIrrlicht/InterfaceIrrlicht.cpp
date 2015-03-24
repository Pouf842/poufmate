#include "InterfaceIrrlicht.h"
#include "Pieces/Piece.h"
#include "States/IncludeStates.h"
#include "Tools.h"

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

	/**/SetState(new IntroState(this));
	delete mpoCurrentState;
	mpoCurrentState = NULL;/*/
	SetState(new TestState(this));
	delete mpoCurrentState;
	mpoCurrentState = NULL;/**/

	mpoMenuState = new MenuState(this);
	mpoGameState = new GameState(this);
	mpoPieceViewerState = new PieceViewerState(this);
}

InterfaceIrrlicht::~InterfaceIrrlicht()
{
	mpoBoardMesh->drop();
	mpoDevice->closeDevice();
	mpoDevice->drop();
}

void InterfaceIrrlicht::InitDatas()
{
	ITriangleSelector * poTriangleSelector;

	moPiecesMeshs[Piece::PT_ROOK]   = NULL;
	moPiecesMeshs[Piece::PT_KNIGHT] = NULL;
	moPiecesMeshs[Piece::PT_BISHOP] = NULL;
	moPiecesMeshs[Piece::PT_QUEEN]  = NULL;
	moPiecesMeshs[Piece::PT_KING]   = NULL;
	moPiecesMeshs[Piece::PT_PAWN]   = NULL;

	mpoBoardMesh = mpoSceneManager->getGeometryCreator()->createCubeMesh(vector3df(8, 1, 8));
	mpoBoardNode = mpoSceneManager->addMeshSceneNode(mpoBoardMesh, NULL, ID_BOARD);
	mpoBoardNode->setName("Board");
	poTriangleSelector = mpoSceneManager->createTriangleSelector(mpoBoardMesh, mpoBoardNode);
	mpoBoardNode->setTriangleSelector(poTriangleSelector);
	poTriangleSelector->drop();
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
			strMeshFile += "rook.b3d";
			break;
		  default :
		  case Piece::PT_PAWN :
			strMeshFile += "pawn.b3d";
			break;
		  case Piece::PT_BISHOP :
			strMeshFile += "bishop.b3d";
			break;
		  case Piece::PT_KNIGHT :
			strMeshFile += "knight.b3d";
			break;
		  case Piece::PT_QUEEN :
			strMeshFile += "queen.b3d";
			break;
		  case Piece::PT_KING :
			strMeshFile += "king.b3d";
			break;
		}

		i->second = mpoSceneManager->getMesh(strMeshFile);

		if(!i->second)
			i->second = mpoSceneManager->getMesh("Medias/pawn.b3d");
	}
	
	PlacePieces();
}

void InterfaceIrrlicht::PlacePieces()
{
	vector<IMesh *> oMeshes;
	vector<vector3df> oPositions;
	vector<std::string> oNames;
	vector<Piece::PIECE_COLOR> oColors;

	// White pawns
	for(s32 i = 0; i < 8; ++i)
	{
		oMeshes.push_back(moPiecesMeshs[Piece::PT_PAWN]);
		oPositions.push_back(vector3df(-3.5 + i, 0.5, -2.5));
		std::string str("White pawn n°");
		str += '0' + i;
		oNames.push_back(str);
		oColors.push_back(Piece::PC_WHITE);
	}

	// Black pawns
	for(s32 i = 0; i < 8; ++i)
	{
		oMeshes.push_back(moPiecesMeshs[Piece::PT_PAWN]);
		oPositions.push_back(vector3df(-3.5 + i, 0.5, 2.5));
		std::string str("Black pawn n°");
		str += '0' + i;
		oNames.push_back(str);
		oColors.push_back(Piece::PC_BLACK);
	}

	// Kings
	oMeshes.push_back(moPiecesMeshs[Piece::PT_KING]);
	oPositions.push_back(vector3df(0.5, 0.5, -3.5));
	oNames.push_back("White king");
	oColors.push_back(Piece::PC_WHITE);

	oMeshes.push_back(moPiecesMeshs[Piece::PT_KING]);
	oPositions.push_back(vector3df(0.5, 0.5, 3.5));
	oNames.push_back("Black king");
	oColors.push_back(Piece::PC_BLACK);

	// Queens
	oMeshes.push_back(moPiecesMeshs[Piece::PT_QUEEN]);
	oPositions.push_back(vector3df(-0.5, 0.5, -3.5));
	oNames.push_back("White queen");
	oColors.push_back(Piece::PC_WHITE);

	oMeshes.push_back(moPiecesMeshs[Piece::PT_QUEEN]);
	oPositions.push_back(vector3df(-0.5, 0.5, 3.5));
	oNames.push_back("Black queen");
	oColors.push_back(Piece::PC_BLACK);
	
	// Bishops
	for(s32 i = 0; i < 2; ++i)
	{
		oMeshes.push_back(moPiecesMeshs[Piece::PT_BISHOP]);
		oPositions.push_back(vector3df(-1.5 + i * 3, 0.5, -3.5));
		std::string str("White bishop n°");
		str += '0' + i;
		oNames.push_back(str);
		oColors.push_back(Piece::PC_WHITE);
	}

	for(s32 i = 0; i < 2; ++i)
	{
		oMeshes.push_back(moPiecesMeshs[Piece::PT_BISHOP]);
		oPositions.push_back(vector3df(-1.5 + i * 3, 0.5, 3.5));
		std::string str("Black bishop n°");
		str += '0' + i;
		oNames.push_back(str);
		oColors.push_back(Piece::PC_BLACK);
	}
	
	// Knights
	for(s32 i = 0; i < 2; ++i)
	{
		oMeshes.push_back(moPiecesMeshs[Piece::PT_KNIGHT]);
		oPositions.push_back(vector3df(-2.5 + i * 5, 0.5, -3.5));
		std::string str("White knight n°");
		str += '0' + i;
		oNames.push_back(str);
		oColors.push_back(Piece::PC_WHITE);
	}

	for(s32 i = 0; i < 2; ++i)
	{
		oMeshes.push_back(moPiecesMeshs[Piece::PT_KNIGHT]);
		oPositions.push_back(vector3df(-2.5 + i * 5, 0.5, 3.5));
		std::string str("Black knight n°");
		str += '0' + i;
		oNames.push_back(str);
		oColors.push_back(Piece::PC_BLACK);
	}
	
	// Rooks
	for(s32 i = 0; i < 2; ++i)
	{
		oMeshes.push_back(moPiecesMeshs[Piece::PT_ROOK]);
		oPositions.push_back(vector3df(-3.5 + i * 7, 0.5, -3.5));
		std::string str("White rook n°");
		str += '0' + i;
		oNames.push_back(str);
		oColors.push_back(Piece::PC_WHITE);
	}

	for(s32 i = 0; i < 2; ++i)
	{
		oMeshes.push_back(moPiecesMeshs[Piece::PT_ROOK]);
		oPositions.push_back(vector3df(-3.5 + i * 7, 0.5, 3.5));
		std::string str("Black rook n°");
		str += '0' + i;
		oNames.push_back(str);
		oColors.push_back(Piece::PC_BLACK);
	}

	ISceneNode * poNode;

	for(s32 i = 0; i < 32; ++i)
	{
		poNode = mpoSceneManager->addMeshSceneNode(oMeshes[i], mpoBoardNode, ID_PIECE, oPositions[i]);
		poNode->setScale(vector3df(0.5, 0.5, 0.5));
		poNode->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);

		if(oColors[i] == Piece::PC_WHITE)
		{
			poNode->getMaterial(0).AmbientColor  = SColor(255, 220, 220, 220);
			poNode->getMaterial(0).SpecularColor = SColor(255, 255, 255, 255);
		}
		else
		{	
			poNode->getMaterial(0).AmbientColor = SColor(255, 0, 0, 0);
			poNode->getMaterial(0).DiffuseColor = SColor(255, 0, 0, 0);
		}

		poNode->setName(oNames[i].c_str());

		ITriangleSelector * poTriangleSelector = mpoSceneManager->createTriangleSelector(oMeshes[i], poNode);
		poNode->setTriangleSelector(poTriangleSelector);
		poTriangleSelector->drop();
	}
}

int InterfaceIrrlicht::iGetMenuEntry(const std::vector<std::string> oMenu)
{
	mpoMenuState->SetMenu(oMenu);
	SetState(mpoMenuState);

	while(mpoMenuState->sGetChoice() > oMenu.size())
	{
		SetState(mpoPieceViewerState);
		mpoCurrentState = NULL;
		mpoMenuState->SetMenu(oMenu);
		SetState(mpoMenuState);
	}
	
	return mpoMenuState->sGetChoice();
}

Entry InterfaceIrrlicht::oGetEntry()
{
	SetState(mpoGameState);

	return mpoGameState->oGetLastEntry();
}

void InterfaceIrrlicht::DisplayMessage(const std::string strMessage)
{
	cout << strMessage << endl;
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