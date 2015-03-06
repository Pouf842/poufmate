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