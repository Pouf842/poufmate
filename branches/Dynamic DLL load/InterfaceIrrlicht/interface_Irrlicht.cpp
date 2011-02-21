#include "interface_irrlicht.h"

extern "C" __declspec(dllexport) Interface * poGetInstance(struct Interface::stExportedMethods exportedMethods)
{
    return new InterfaceIrrlicht(exportedMethods);
}

InterfaceIrrlicht::InterfaceIrrlicht(struct Interface::stExportedMethods exportedMethods)
{
    mExportedMethods = exportedMethods;

    mpoMainWindow = createDevice(video::EDT_OPENGL,
                                 core::dimension2d<u32>(800, 600),
                                 32,
                                 false,
                                 true,
                                 false,
                                 NULL);

    mpoVideoDriver = mpoMainWindow->getVideoDriver();
    mpoSceneManager = mpoMainWindow->getSceneManager();
    mpoGUIEnvironment = mpoMainWindow->getGUIEnvironment();

    scene::ICameraSceneNode * poCamera = mpoSceneManager->addCameraSceneNodeFPS(NULL, 100, 0.1, 0, NULL, 5, false, 0, true);
    poCamera->setPosition(core::vector3df(0, 10, -10));
    poCamera->setTarget(core::vector3df(0, 0, 0));

    scene::IMesh * poBoard = mpoSceneManager->getMesh("untitled.obj");
    mpoSceneManager->addMeshSceneNode(poBoard, NULL, -1, core::vector3df(0, 0, 0), core::vector3df(0, 0, 0), core::vector3df(8, 8, 8))->setMaterialFlag(video::EMF_LIGHTING, false);
}

InterfaceIrrlicht::~InterfaceIrrlicht()
{
    mpoMainWindow->drop();    
}

void InterfaceIrrlicht::Pause()
{
}

void InterfaceIrrlicht::DisplayGame(const Game &)
{
}

GameEntry InterfaceIrrlicht::oGetGameEntry(Game &)
{
    return GameEntry("A1, A2");
}

void InterfaceIrrlicht::AddMessage(std::string)
{
}

EditionEntry InterfaceIrrlicht::oGetEditionEntry(const GameEdition &)
{
    return EditionEntry("x");
}

std::string InterfaceIrrlicht::strGetIPEntry()
{
    return "0.0.0.0";
}

std::string InterfaceIrrlicht::strGetPortEntry()
{
    return "12345";
}

char InterfaceIrrlicht::cGetNewPieceType(Piece::Color)
{
    return 'K';
}

int InterfaceIrrlicht::iGetMenuEntry(const std::vector<std::string> & oMenuItems)
{
    mpoGUIEnvironment->addStaticText(L"PoufMate !", core::rect<s32>(100, 100, 500, 700), true)->setOverrideFont(mpoGUIEnvironment->getFont("Lucida.png"));

    while(mpoMainWindow->run())
    {
        mpoVideoDriver->beginScene(true, true, video::SColor(255, 255, 255, 255));

        mpoSceneManager->drawAll();
        mpoGUIEnvironment->drawAll();

        mpoVideoDriver->endScene();
    }

    return 0;
}

char InterfaceIrrlicht::cGetPlayerColorChoice()
{
    return 'W';
}
