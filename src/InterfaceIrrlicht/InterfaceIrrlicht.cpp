#include "InterfaceIrrlicht.h"
#include "Pieces/Piece.h"
#include "States/IncludeStates.h"
#include "Tools.h"

#include <iostream>

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

	moPiecesMeshes[Piece::PT_ROOK]   = NULL;
	moPiecesMeshes[Piece::PT_KNIGHT] = NULL;
	moPiecesMeshes[Piece::PT_BISHOP] = NULL;
	moPiecesMeshes[Piece::PT_QUEEN]  = NULL;
	moPiecesMeshes[Piece::PT_KING]   = NULL;
	moPiecesMeshes[Piece::PT_PAWN]   = NULL;

	mpoBoardMesh = mpoSceneManager->getGeometryCreator()->createCubeMesh(vector3df(8, 1, 8));
	mpoBoardNode = mpoSceneManager->addMeshSceneNode(mpoBoardMesh, NULL, ID_BOARD);
	mpoBoardNode->setName("Board");
	poTriangleSelector = mpoSceneManager->createTriangleSelector(mpoBoardMesh, mpoBoardNode);
	mpoBoardNode->setTriangleSelector(poTriangleSelector);
	poTriangleSelector->drop();
	mpoBoardNode->setMaterialFlag(EMF_LIGHTING, true);
	ITexture * poBoardTexture = mpoVideoDriver->getTexture("Medias/Images/board.bmp");
	mpoBoardNode->setMaterialTexture(0, poBoardTexture);

	for(map<Piece::PIECE_TYPE, IAnimatedMesh*>::Iterator i = moPiecesMeshes.getIterator(); !i.atEnd(); i++)
	{
		irr::core::string<char> strMeshFile = "Medias/";
		switch(i->getKey())
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

		i->setValue(mpoSceneManager->getMesh(strMeshFile));

		if(!i->getValue())
			i->setValue(mpoSceneManager->getMesh("Medias/pawn.b3d"));
	}
	
	PlacePieces();
}

void InterfaceIrrlicht::PlacePieces()
{
	array<IMesh *> oMeshes;
	array<vector3df> oPositions;
	array<string<char> > oNames;
	array<Piece::PIECE_COLOR> oColors;

	// White pawns
	for(s32 i = 0; i < 8; ++i)
	{
		oMeshes.push_back(moPiecesMeshes[Piece::PT_PAWN]);
		oPositions.push_back(vector3df(-3.5 + i, 0.5, -2.5));
		string<char> str("White pawn n°");
		str += '0' + i;
		oNames.push_back(str);
		oColors.push_back(Piece::PC_WHITE);
	}

	// Black pawns
	for(s32 i = 0; i < 8; ++i)
	{
		oMeshes.push_back(moPiecesMeshes[Piece::PT_PAWN]);
		oPositions.push_back(vector3df(-3.5 + i, 0.5, 2.5));
		string<char> str("Black pawn n°");
		str += '0' + i;
		oNames.push_back(str);
		oColors.push_back(Piece::PC_BLACK);
	}

	// Kings
	oMeshes.push_back(moPiecesMeshes[Piece::PT_KING]);
	oPositions.push_back(vector3df(0.5, 0.5, -3.5));
	oNames.push_back("White king");
	oColors.push_back(Piece::PC_WHITE);

	oMeshes.push_back(moPiecesMeshes[Piece::PT_KING]);
	oPositions.push_back(vector3df(0.5, 0.5, 3.5));
	oNames.push_back("Black king");
	oColors.push_back(Piece::PC_BLACK);

	// Queens
	oMeshes.push_back(moPiecesMeshes[Piece::PT_QUEEN]);
	oPositions.push_back(vector3df(-0.5, 0.5, -3.5));
	oNames.push_back("White queen");
	oColors.push_back(Piece::PC_WHITE);

	oMeshes.push_back(moPiecesMeshes[Piece::PT_QUEEN]);
	oPositions.push_back(vector3df(-0.5, 0.5, 3.5));
	oNames.push_back("Black queen");
	oColors.push_back(Piece::PC_BLACK);
	
	// Bishops
	for(s32 i = 0; i < 2; ++i)
	{
		oMeshes.push_back(moPiecesMeshes[Piece::PT_BISHOP]);
		oPositions.push_back(vector3df(-1.5 + i * 3, 0.5, -3.5));
		string<char> str("White bishop n°");
		str += '0' + i;
		oNames.push_back(str);
		oColors.push_back(Piece::PC_WHITE);
	}

	for(s32 i = 0; i < 2; ++i)
	{
		oMeshes.push_back(moPiecesMeshes[Piece::PT_BISHOP]);
		oPositions.push_back(vector3df(-1.5 + i * 3, 0.5, 3.5));
		string<char> str("Black bishop n°");
		str += '0' + i;
		oNames.push_back(str);
		oColors.push_back(Piece::PC_BLACK);
	}
	
	// Knights
	for(s32 i = 0; i < 2; ++i)
	{
		oMeshes.push_back(moPiecesMeshes[Piece::PT_KNIGHT]);
		oPositions.push_back(vector3df(-2.5 + i * 5, 0.5, -3.5));
		string<char> str("White knight n°");
		str += '0' + i;
		oNames.push_back(str);
		oColors.push_back(Piece::PC_WHITE);
	}

	for(s32 i = 0; i < 2; ++i)
	{
		oMeshes.push_back(moPiecesMeshes[Piece::PT_KNIGHT]);
		oPositions.push_back(vector3df(-2.5 + i * 5, 0.5, 3.5));
		string<char> str("Black knight n°");
		str += '0' + i;
		oNames.push_back(str);
		oColors.push_back(Piece::PC_BLACK);
	}
	
	// Rooks
	for(s32 i = 0; i < 2; ++i)
	{
		oMeshes.push_back(moPiecesMeshes[Piece::PT_ROOK]);
		oPositions.push_back(vector3df(-3.5 + i * 7, 0.5, -3.5));
		string<char> str("White rook n°");
		str += '0' + i;
		oNames.push_back(str);
		oColors.push_back(Piece::PC_WHITE);
	}

	for(s32 i = 0; i < 2; ++i)
	{
		oMeshes.push_back(moPiecesMeshes[Piece::PT_ROOK]);
		oPositions.push_back(vector3df(-3.5 + i * 7, 0.5, 3.5));
		string<char> str("Black rook n°");
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
	array<irr::core::string<wchar_t> > oArrayMenu;

	for(s32 i = 0; i < oMenu.size(); ++i)
		oArrayMenu.push_back(oMenu[i].c_str());

	mpoMenuState->SetMenu(oArrayMenu);
	SetState(mpoMenuState);

	while(mpoMenuState->sGetChoice() > oMenu.size())
	{
		SetState(mpoPieceViewerState);
		mpoCurrentState = NULL;
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
	std::cout << strMessage << std::endl;
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

void InterfaceIrrlicht::addPieceNode(Piece * poPiece, const Position & oPos)
{
}

void InterfaceIrrlicht::addPieceNode(Piece::PIECE_TYPE eType, Piece::PIECE_COLOR eColor, const Position & oPos)
{
}

Position InterfaceIrrlicht::oGetBoardPosition(const irr::core::vector3df & vNodePosition)
{
	return Position(4 - (round32(vNodePosition.Z + 0.5) - 0.5), round32(vNodePosition.X + 0.5) - 0.5 + 4);
}

vector3df InterfaceIrrlicht::oGetNodePosition(const Position & oPos)
{
	return vector3df(oPos.mY - 3.5, 0.5, oPos.mX + 3.5);
}