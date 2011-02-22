#include "interface_irrlicht.h"

extern "C" __declspec(dllexport) Interface * poGetInstance(struct Interface::stExportedMethods exportedMethods)
{
    return new InterfaceIrrlicht(exportedMethods);
}

bool InterfaceIrrlicht::OnEvent(const SEvent & event)
{
    if(event.EventType == EET_GUI_EVENT)
    {
        if(event.GUIEvent.EventType == gui::EGET_ELEMENT_HOVERED)
        {
            if(event.GUIEvent.Caller->getType() == gui::EGUIET_BUTTON)
            {
                mpoSelectionToken->setVisible(true);
                mpoSelectionToken->setRelativePosition(core::rect<s32>(180, 110 + (event.GUIEvent.Caller->getID() - 1) * 50, 230, 160 + (event.GUIEvent.Caller->getID() - 1) * 50));
                return true;
            }
        }
        else if(event.GUIEvent.EventType == gui::EGET_BUTTON_CLICKED)
        {
            miUserSelection = event.GUIEvent.Caller->getID();
            return true;
        }
    }
    else
        return false;
}


InterfaceIrrlicht::InterfaceIrrlicht(struct Interface::stExportedMethods exportedMethods) : mpoGUIEnvironment(NULL), mpoMainWindow(NULL), mpoSceneManager(NULL), mpoVideoDriver(NULL), miUserSelection(-1)
{
    mExportedMethods = exportedMethods;

    mpoMainWindow = createDevice(video::EDT_OPENGL,
                                 core::dimension2d<u32>(800, 600),
                                 32,
                                 false,
                                 true,
                                 false,
                                 NULL);

    mpoMainWindow->setEventReceiver(this);

    mpoVideoDriver = mpoMainWindow->getVideoDriver();
    mpoSceneManager = mpoMainWindow->getSceneManager();
    mpoGUIEnvironment = mpoMainWindow->getGUIEnvironment();

    scene::ICameraSceneNode * poCamera = mpoSceneManager->addCameraSceneNodeFPS(NULL, 100, 0.1, 0, NULL, 5, false, 0, true);
    poCamera->setPosition(core::vector3df(0, 10, -10));
    poCamera->setTarget(core::vector3df(0, 0, 0));
    poCamera->setInputReceiverEnabled(false);

    scene::IMesh * poBoard = mpoSceneManager->getMesh("Meshes/Board.obj");
    scene::IMeshSceneNode * poBoardNode = mpoSceneManager->addMeshSceneNode(poBoard, NULL, -1, core::vector3df(0, 0, 0), core::vector3df(0, 0, 0), core::vector3df(8, 8, 8));

    poBoardNode->setMaterialFlag(video::EMF_LIGHTING, false);
    poBoardNode->setMaterialTexture(0, mpoVideoDriver->getTexture("Images/Echiquier.bmp"));
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
    miUserSelection = -1;

    gui::IGUIStaticText * poTest = mpoGUIEnvironment->addStaticText(L"PoufMate !", core::rect<s32>(0, 50, 800, 100));
    poTest->setOverrideFont(mpoGUIEnvironment->getFont("Lucida.png"));
    poTest->setTextAlignment(gui::EGUIA_CENTER, gui::EGUIA_CENTER);
    poTest->setOverrideColor(video::SColor(255, 255, 0, 0));

    for(int i = 0; i < oMenuItems.size(); ++i)
    {
        core::stringw strItem(oMenuItems[i].c_str());
        mpoGUIEnvironment->addButton(core::rect<s32>(250, 110 + 50 * i, 550, 130 + 50 * i), NULL, i + 1, strItem.c_str(), L"Lancer une nouvelle partie contre l'ordinateur")->setOverrideFont(mpoGUIEnvironment->getFont("Lucida.png"));
    }

    video::ITexture * poSelectionTokenImg = mpoVideoDriver->getTexture("Images/token.jpg");
    
    mpoSelectionToken = mpoGUIEnvironment->addImage(poSelectionTokenImg, core::vector2d<s32>(200, 110));
    mpoSelectionToken->setVisible(false);

    while(mpoMainWindow->run() && miUserSelection == -1)
    {
        mpoVideoDriver->beginScene(true, true, video::SColor(255, 255, 255, 255));

        mpoSceneManager->drawAll();
        mpoGUIEnvironment->drawAll();

        mpoVideoDriver->endScene();
    }

    return miUserSelection;
}

char InterfaceIrrlicht::cGetPlayerColorChoice()
{
    return 'W';
}
