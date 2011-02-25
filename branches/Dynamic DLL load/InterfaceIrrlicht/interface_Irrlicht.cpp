#include "CEGUI.h"
#include "RendererModules\Irrlicht\CEGUIIrrlichtRenderer.h"
#include "interface_irrlicht.h"

#define CEGUIXY(a, b) CEGUI::UVector2(CEGUI::UDim(a, 0), CEGUI::UDim(b, 0))

extern "C" __declspec(dllexport) Interface * poGetInstance(struct Interface::stExportedMethods exportedMethods)
{
    return new InterfaceIrrlicht(exportedMethods);
}

bool InterfaceIrrlicht::OnEvent(const SEvent & stEvent)
{

    return false;
}


InterfaceIrrlicht::InterfaceIrrlicht(struct Interface::stExportedMethods exportedMethods) : mpoMainWindow(NULL), mpoSceneManager(NULL), mpoVideoDriver(NULL), miUserSelection(-1)
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

    scene::IMesh * poBoard = mpoSceneManager->getMesh("Meshes/Board.obj");
    scene::IMeshSceneNode * poBoardNode = mpoSceneManager->addMeshSceneNode(poBoard, NULL, -1, core::vector3df(0, 0, 0), core::vector3df(0, 0, 0), core::vector3df(8, 8, 8));

    poBoardNode->setMaterialFlag(video::EMF_LIGHTING, false);
    poBoardNode->setMaterialTexture(0, mpoVideoDriver->getTexture("Images/Echiquier.bmp"));

    mpoSceneManager->setAmbientLight(video::SColorf(1.0, 1.0, 1.0, 0));
    scene::ISceneNode * poCameraContainer = mpoSceneManager->addEmptySceneNode();
    poCameraContainer->setName("cameraContainer");

    scene::ICameraSceneNode * poCamera = mpoSceneManager->addCameraSceneNodeFPS(poCameraContainer, 100, 0.1, 0, NULL, 5, false, 0, true);
    poCamera->setPosition(core::vector3df(0, 10.25, -10.25));
    poCamera->setTarget(core::vector3df(0, 0, 0));
    poCamera->setInputReceiverEnabled(false);

    InitGUI();
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

    CEGUI::Window * poGeneralFrame = mpoGUIWinManager->createWindow("DefaultWindow", "GeneralFrame");
    mpoGUISystem->setGUISheet(poGeneralFrame);

    /*CEGUI::FrameWindow * poFrameWinTest = static_cast<CEGUI::FrameWindow*>(mpoGUIWinManager->createWindow("TaharezLook/FrameWindow", "Test"));
    poGeneralFrame->addChildWindow(poFrameWinTest);
    poFrameWinTest->setPosition(CEGUI::UVector2(CEGUI::UDim(0.25f, 0), CEGUI::UDim(0.25f, 0)));
    poFrameWinTest->setSize(CEGUI::UVector2(CEGUI::UDim(0.5f, 0), CEGUI::UDim(0.5f, 0)));
    poFrameWinTest->setText("Hello world");*/

    CEGUI::Window * poTitle = mpoGUIWinManager->createWindow("TaharezLook/StaticText", "Title");
    poTitle->setPosition(CEGUIXY(0, 0));
    poTitle->setSize(CEGUIXY(1, 0.10));
    poTitle->setProperty("HorzFormatting", "HorzCentred");
    poTitle->setProperty("FrameEnabled", "False");
    poTitle->setProperty("BackgroundEnabled", "False");
    poTitle->setProperty("TextColours", "tl:AAFF0000 tr:AA0000FF bl:AAFF0000 br:AA0000FF");

    poTitle->setText("Poufmate !");
    poGeneralFrame->addChildWindow(poTitle);

    scene::ISceneNode * poCameraContainer = mpoSceneManager->getSceneNodeFromName("cameraContainer");
    
    while(mpoMainWindow->run() && miUserSelection == -1)
    {
        mpoVideoDriver->beginScene(true, true, video::SColor(255, 255, 255, 255));

        poCameraContainer->setRotation(core::vector3df(0, poCameraContainer->getRotation().Y + 0.05, 0));
        mpoSceneManager->drawAll();
        mpoGUISystem->renderGUI();

        mpoVideoDriver->endScene();
    }
 
    poGeneralFrame->destroy();

    if(!mpoMainWindow->run())
        return 6;

    return miUserSelection;
}

char InterfaceIrrlicht::cGetPlayerColorChoice()
{
    return 'W';
}

void InterfaceIrrlicht::InitGUI()
{
    mpoGUI = &CEGUI::IrrlichtRenderer::bootstrapSystem(*mpoMainWindow);
    mpoGUIWinManager = &CEGUI::WindowManager::getSingleton();
    mpoGUISystem = &CEGUI::System::getSingleton();

    CEGUI::DefaultResourceProvider * poResourceProvider = static_cast<CEGUI::DefaultResourceProvider*>(mpoGUISystem->getResourceProvider());
    poResourceProvider->setResourceGroupDirectory("schemes", "datafiles/schemes/");
    poResourceProvider->setResourceGroupDirectory("imagesets", "datafiles/imagesets/");
    poResourceProvider->setResourceGroupDirectory("fonts", "datafiles/fonts/");
    poResourceProvider->setResourceGroupDirectory("layouts", "datafiles/layouts/");
    poResourceProvider->setResourceGroupDirectory("looknfeels", "datafiles/looknfeel/");
    poResourceProvider->setResourceGroupDirectory("lua_scripts", "datafiles/lua_scripts/");

    CEGUI::Imageset::setDefaultResourceGroup("imagesets");
    CEGUI::Font::setDefaultResourceGroup("fonts");
    CEGUI::Scheme::setDefaultResourceGroup("schemes");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
    CEGUI::WindowManager::setDefaultResourceGroup("layouts");
    CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");

    CEGUI::FontManager::getSingleton().create("DejaVuSans-10.font" );
    CEGUI::SchemeManager::getSingleton().create("TaharezLook.scheme");
}