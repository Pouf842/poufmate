#include "InterfaceIrrlicht.h"
#include "Pieces/Piece.h"
#include "States/IncludeStates.h"
#include "Tools.h"

#include <vector>
#include <iostream>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace gui;

s32 ID_BOARD = 1;
s32 ID_PIECE = 2;

extern "C" __declspec(dllexport) Interface * poGetInterface(Controller * poController)
{
    Interface * poInterface = new InterfaceIrrlicht(poController);

    return poInterface;
}

InterfaceIrrlicht::InterfaceIrrlicht(Controller * poController) : mpoCurrentState(NULL), mpoCameraFPS(NULL), mpoCamera(NULL), mpoCurrentCamera(NULL), mbStop(false)
{
    mpoController = poController;
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

    IntroState oIntro(this);
    oIntro.Show();

	/*SetState(new TestState(this));
	delete mpoCurrentState;
	mpoCurrentState = NULL;/**/

	mpoMenuState    = new MenuState(this);
	mpoGameState    = new GameState(this);
    //mpoEditionState = new EditionState(this);
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
    mpoBoardNode = CreateBoardNode();

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

ISceneNode * InterfaceIrrlicht::CreateBoardNode()
{
    ISceneNode * poNode = mpoSceneManager->addMeshSceneNode(mpoBoardMesh, NULL, ID_BOARD);
    poNode->setName("Board");
    ITriangleSelector * poTriangleSelector = mpoSceneManager->createTriangleSelector(mpoBoardMesh, poNode);
    poNode->setTriangleSelector(poTriangleSelector);
    poTriangleSelector->drop();
    poNode->setMaterialFlag(EMF_LIGHTING, true);
    ITexture * poBoardTexture = mpoVideoDriver->getTexture("Medias/Images/board.bmp");
    poNode->setMaterialTexture(0, poBoardTexture);

    return poNode;
}

void InterfaceIrrlicht::SetMenuState(std::vector<std::string> const * poMenu)
{
    if(poMenu)
    {
        array<string<wchar_t> > oWMenu;

        for each(std::string str in *poMenu)
            oWMenu.push_back(string<wchar_t>(str.c_str()));

        mpoMenuState->SetMenu(oWMenu);
    }

    SetState(mpoMenuState);
}

void InterfaceIrrlicht::SetGameState(const Board & oBoard)
{
    mpoGameState->InitBoard(oBoard);
    SetState(mpoGameState);
}

void InterfaceIrrlicht::SetPieceViewerState()
{
    try
    {
        State * poLastState = mpoCurrentState;

        SetState(mpoPieceViewerState);
        SetState(poLastState);
    }
    catch(std::exception & e)
    {
        std::cout << __FUNCTION__ << ":" << __LINE__ << " : " << e.what() << std::endl;
        throw e;
    }
}

void InterfaceIrrlicht::Run()
{
    mbStop = false;

    while(mpoDevice->run() && !mbStop)
    {
        if(mpoDevice->isWindowActive())
        {
            mpoVideoDriver->beginScene();
            mpoSceneManager->drawAll();
            mpoGUI->drawAll();
            mpoVideoDriver->endScene();
        }
        else
            mpoDevice->yield();
    }
}

void InterfaceIrrlicht::Quit()
{
    mbStop = true;
}

Piece::PIECE_TYPE InterfaceIrrlicht::eGetPromotionNewPiece()
{
    return Piece::PT_PAWN;
}

void InterfaceIrrlicht::PlacePieces()
{
	array<Position> oPositions;
	array<string<char> > oNames;
	array<Piece::PIECE_TYPE> oTypes;
	array<Piece::PIECE_COLOR> oColors;

	/*/ White pawns
	for(s32 i = 0; i < 8; ++i)
	{
		oPositions.push_back(Position(6, i));
		string<char> str("White pawn n°");
		str += '0' + i;
		oNames.push_back(str);
		oTypes.push_back(Piece::PT_PAWN);
		oColors.push_back(Piece::PC_WHITE);
	}

	// Black pawns
	for(s32 i = 0; i < 8; ++i)
	{
		oPositions.push_back(Position(1, i));
		string<char> str("Black pawn n°");
		str += '0' + i;
		oNames.push_back(str);
		oTypes.push_back(Piece::PT_PAWN);
		oColors.push_back(Piece::PC_BLACK);
	}

	// Kings
	oPositions.push_back(Position(7, 4));
	oNames.push_back("White king");
	oTypes.push_back(Piece::PT_KING);
	oColors.push_back(Piece::PC_WHITE);

	oPositions.push_back(Position(0, 4));
	oNames.push_back("Black king");
	oTypes.push_back(Piece::PT_KING);
	oColors.push_back(Piece::PC_BLACK);

	// Queens
	oPositions.push_back(Position(7, 3));
	oNames.push_back("White queen");
	oTypes.push_back(Piece::PT_QUEEN);
	oColors.push_back(Piece::PC_WHITE);

	oPositions.push_back(Position(0, 3));
	oNames.push_back("Black queen");
	oTypes.push_back(Piece::PT_QUEEN);
	oColors.push_back(Piece::PC_BLACK);
	
	// Bishops
	for(s32 i = 0; i < 2; ++i)
	{
		oPositions.push_back(Position(7, 2 + 3 * i));
		string<char> str("White bishop n°");
		str += '0' + i;
		oNames.push_back(str);
		oTypes.push_back(Piece::PT_BISHOP);
		oColors.push_back(Piece::PC_WHITE);
	}

	for(s32 i = 0; i < 2; ++i)
	{
		oPositions.push_back(Position(0, 2 + 3 * i));
		string<char> str("Black bishop n°");
		str += '0' + i;
		oNames.push_back(str);
		oTypes.push_back(Piece::PT_BISHOP);
		oColors.push_back(Piece::PC_BLACK);
	}
	
	// Knights
	for(s32 i = 0; i < 2; ++i)
	{
		oPositions.push_back(Position(7, 1 + 5 * i));
		string<char> str("White knight n°");
		str += '0' + i;
		oNames.push_back(str);
		oTypes.push_back(Piece::PT_KNIGHT);
		oColors.push_back(Piece::PC_WHITE);
	}

	for(s32 i = 0; i < 2; ++i)
	{
		oPositions.push_back(Position(0, 1 + 5 * i));
		string<char> str("Black knight n°");
		str += '0' + i;
		oNames.push_back(str);
		oTypes.push_back(Piece::PT_KNIGHT);
		oColors.push_back(Piece::PC_BLACK);
	}
	
	// Rooks
	for(s32 i = 0; i < 2; ++i)
	{
		oPositions.push_back(Position(7, 7 * i));
		string<char> str("White rook n°");
		str += '0' + i;
		oNames.push_back(str);
		oTypes.push_back(Piece::PT_ROOK);
		oColors.push_back(Piece::PC_WHITE);
	}

	for(s32 i = 0; i < 2; ++i)
	{
		oPositions.push_back(Position(0, 7 * i));
		string<char> str("Black rook n°");
		str += '0' + i;
		oNames.push_back(str);
		oTypes.push_back(Piece::PT_ROOK);
		oColors.push_back(Piece::PC_BLACK);
	}*/

	oPositions.push_back(Position(0, 6));
	oNames.push_back("White knight");
	oTypes.push_back(Piece::PT_KNIGHT);
	oColors.push_back(Piece::PC_WHITE);

	oPositions.push_back(Position(1, 6));
	oNames.push_back("White king");
	oTypes.push_back(Piece::PT_KING);
	oColors.push_back(Piece::PC_WHITE);

	oPositions.push_back(Position(5, 3));
	oNames.push_back("Black king");
	oTypes.push_back(Piece::PT_KING);
	oColors.push_back(Piece::PC_BLACK);

	ISceneNode * poNode;

	for(s32 i = 0; i < oPositions.size(); ++i)
		addPieceNode(oTypes[i], oColors[i], oPositions[i], oNames[i]);
}


/*void InterfaceIrrlicht::DisplayMessage(const std::string strMessage)
{
	std::cout << strMessage << std::endl;
}*/

void InterfaceIrrlicht::SetState(State * poNewState)
{
	if(mpoCurrentState)
		mpoCurrentState->Hide();

	mpoCurrentState = poNewState;
	mpoDevice->setEventReceiver(mpoCurrentState);

    mpoCurrentState->Show();
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

ISceneNode * InterfaceIrrlicht::addPieceNode(Piece * poPiece, const Position & oPos, irr::core::string<char> strName, ISceneNode * poParent)
{
    try
    {
        if(poPiece)
            return addPieceNode(poPiece->eGetType(), poPiece->eGetColor(), oPos, strName, poParent);
    }
    catch(std::exception & e)
    {
        std::cout << __FUNCTION__ << ":" << __LINE__ << " : " << e.what() << std::endl;
        throw e;
    }
}

ISceneNode * InterfaceIrrlicht::addPieceNode(Piece::PIECE_TYPE eType, Piece::PIECE_COLOR eColor, const Position & oPos, string<char> strName, ISceneNode * poParent)
{
	ISceneNode * poNode = mpoSceneManager->addMeshSceneNode(moPiecesMeshes[eType], poParent ? poParent : mpoBoardNode, ID_PIECE, vGetNodePosition(oPos));
	poNode->setScale(vector3df(0.5, 0.5, 0.5));
	poNode->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);

	if(eColor == Piece::PC_WHITE)
	{
		poNode->getMaterial(0).AmbientColor  = SColor(255, 220, 220, 220);
		poNode->getMaterial(0).SpecularColor = SColor(255, 255, 255, 255);
	}
	else
	{	
		poNode->getMaterial(0).AmbientColor = SColor(255, 0, 0, 0);
		poNode->getMaterial(0).DiffuseColor = SColor(255, 0, 0, 0);
	}

	poNode->setName(strName.c_str());

	ITriangleSelector * poTriangleSelector = mpoSceneManager->createTriangleSelector(moPiecesMeshes[eType], poNode);
	poNode->setTriangleSelector(poTriangleSelector);
	poTriangleSelector->drop();

	return poNode;
}

void InterfaceIrrlicht::RotateCamera(float fXDegrees, float fYDegrees, float fZDegrees)
{
	ICameraSceneNode * poCamera = mpoSceneManager->getActiveCamera();
	vector3df oCameraToTarget = poCamera->getTarget() - poCamera->getAbsolutePosition();

	vector3df oBaseRotation(oCameraToTarget.getHorizontalAngle());

	poCamera->bindTargetAndRotation(true);

	u32 uStartTime = mpoDevice->getTimer()->getTime();

	const float TOTAL_ROT_TIME = 1000.0;
	bool bOver = false;

	while(mpoDevice->run() && !bOver)
	{
		if(mpoDevice->isWindowActive())
		{
			mpoVideoDriver->beginScene();
			mpoSceneManager->drawAll();
			mpoGUI->drawAll();
			mpoVideoDriver->endScene();

			u32 uNow = mpoDevice->getTimer()->getTime();
			vector3df vRotation(fXDegrees, fYDegrees, fZDegrees);
			vRotation *= ((uNow - uStartTime) / TOTAL_ROT_TIME);

			if(uNow - uStartTime > TOTAL_ROT_TIME)
			{
				vRotation = vector3df(fXDegrees, fYDegrees, fZDegrees);
				bOver = true;
			}
			
			poCamera->setRotation(oBaseRotation + vRotation);
		}
		else
			mpoDevice->yield();
	}
}

/*void InterfaceIrrlicht::RevolveCamera(const vector3df & vAxis, float fDegrees, float fRevolveTime)
{
	ICameraSceneNode * poCamera = mpoSceneManager->getActiveCamera();
	u32 uStartTime = mpoDevice->getTimer()->getTime();
	const float TOTAL_ROT_TIME = fRevolveTime;
	bool bOver = false;
	vector3df vPos = poCamera->getPosition();

	while(mpoDevice->run() && !bOver)
	{
		if(mpoDevice->isWindowActive())
		{
			mpoVideoDriver->beginScene();
			mpoSceneManager->drawAll();
			mpoGUI->drawAll();
			mpoVideoDriver->endScene();

			u32 uNow = mpoDevice->getTimer()->getTime();

			float fRotAngle = fDegrees * ((uNow - uStartTime) / TOTAL_ROT_TIME);

			if(uNow - uStartTime > TOTAL_ROT_TIME)
			{
				fRotAngle = fDegrees;
				bOver = true;
			}

			fRotAngle = degToRad(fRotAngle);

			quaternion qRotation;
			qRotation.fromAngleAxis(fRotAngle, vAxis);
			vector3df vNewPos(vPos);
			qRotation.getMatrix().rotateVect(vNewPos);
			
			poCamera->setPosition(vNewPos);
		}
		else
			mpoDevice->yield();
	}
}*/