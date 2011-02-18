#include <irrlicht.h>
#include <iostream>

using namespace irr;

class MyEventManager : public IEventReceiver
{
  public :
    MyEventManager(scene::IAnimatedMeshSceneNode * poMeshSceneNode, IrrlichtDevice * poMainWindow, scene::ICameraSceneNode * poCamera) : mpoMeshSceneNode(poMeshSceneNode),
                                                                                                                                         mpoMainWindow(poMainWindow),
                                                                                                                                         mpoCamera(poCamera),
                                                                                                                                         fDirection(0)
    {
    }

    virtual bool OnEvent(const SEvent & stEvent)
    {
        switch(stEvent.EventType)
        {
          case EET_KEY_INPUT_EVENT :
          {
            switch(stEvent.KeyInput.Key)
            {
              case KEY_KEY_A :
              {
                fDirection = (stEvent.KeyInput.PressedDown ? 0.5 : 0);
                break;
              }
              case KEY_KEY_Q :
              {
                fDirection = (stEvent.KeyInput.PressedDown ? -0.5 : 0);
                break;
              }
              default :
              {
                return false;
              }
            }

            return true;
            break;
          }
          case EET_MOUSE_INPUT_EVENT :
          {
            if(stEvent.MouseInput.Event == EMIE_RMOUSE_LEFT_UP)
            {
                mpoMainWindow->getCursorControl()->setVisible(!mpoMainWindow->getCursorControl()->isVisible());
                mpoCamera->setInputReceiverEnabled(!mpoCamera->isInputReceiverEnabled());
                return true;
            }
            break;
          }
          default :
          {
            return false;
            break;
          }
        }

        return false;
    }

    void moveMesh()
    {
        if(fDirection != 0)
        {
            core::vector3df oPosition = mpoMeshSceneNode->getPosition();
            oPosition.X += fDirection;

            mpoMeshSceneNode->setPosition(oPosition);
        }
    }

  private :
    scene::IAnimatedMeshSceneNode * mpoMeshSceneNode;
    scene::ICameraSceneNode * mpoCamera;
    IrrlichtDevice * mpoMainWindow;
    float fDirection;
};

int main(int argc, char * argv[])
{
    IrrlichtDevice * poMainWindow = createDevice(video::EDT_OPENGL,                   // Graphic API
                                                 core::dimension2d<u32>(800, 600),    // Window size
                                                 32,                                  // Color depth
                                                 false,                               // Fullscreen
                                                 true,                                // Stencil buffer
                                                 false,                               // Vertical sync
                                                 NULL);                               // IEventReceiver*

    if(!poMainWindow)
        std::cerr << "Error : Device couldn't be created" << std::endl;

    // Initialization
    video::IVideoDriver * poVideoDriver = poMainWindow->getVideoDriver();
    scene::ISceneManager * poSceneManager = poMainWindow->getSceneManager();
    gui::IGUIEnvironment * poGUI = poMainWindow->getGUIEnvironment();

    // The GUI font
    gui::IGUIFont * poLucidaGUIFont = poGUI->getFont("media/fontlucida.png");

    // The menu
        // The title
    poGUI->addStaticText(L"Apprendre Irrlicht les yeux fermés avec le\n"
    L"'Petit guide d'Irrlicht' de Kevin Leonhart", core::rect<s32>(100, 20, 400, 60), true, true, NULL, -1, true)->setOverrideFont(poLucidaGUIFont);
    poGUI->addButton(core::rect<s32>(100, 80, 150, 100), NULL, -1, L"Cliquez-moi");

    /*/ The room
    scene::IMesh * poRoom = poSceneManager->getMesh("media/room.3ds");
    scene::IMeshSceneNode * poRoomNode = poSceneManager->addMeshSceneNode(poRoom);
    poRoomNode->setMaterialTexture(0, poVideoDriver->getTexture("media/rockwall.jpg"));*/

    // The map
    poMainWindow->getFileSystem()->addZipFileArchive("media/map-20kdm2.pk3");
    scene::IAnimatedMesh * poMap = poSceneManager->getMesh("20kdm2.bsp");
    scene::ISceneNode * poMapNode = poSceneManager->addOctreeSceneNode(poMap);
    poMapNode->setPosition(core::vector3df(-1300, -144, -1249));

    // Sydney
    scene::IAnimatedMesh * poSydney = poSceneManager->getMesh("media/sydney.md2");
    scene::IAnimatedMeshSceneNode * poSydneyNode = poSceneManager->addAnimatedMeshSceneNode(poSydney);
    poSydneyNode->setMaterialTexture(0, poVideoDriver->getTexture("media/sydney.bmp"));
    poSydneyNode->setPosition(core::vector3df(0, 500, -50));

    // Faerie
    scene::IAnimatedMesh * poFaerie = poSceneManager->getMesh("media/faerie.md2");
    scene::IAnimatedMeshSceneNode * poFaerieNode = poSceneManager->addAnimatedMeshSceneNode(poFaerie);
    poFaerieNode->setMaterialTexture(0, poVideoDriver->getTexture("media/faerie5.bmp"));
    poFaerieNode->setPosition(core::vector3df(0, 500, 0));

    // Gun
    scene::IMesh * poGun = poSceneManager->getMesh("media/gun.md2");
    scene::IMeshSceneNode * poGunNode = poSceneManager->addMeshSceneNode(poGun);//, NULL, 0, core::vector3df(0, 0, 0));
    poGunNode->setMaterialTexture(0, poVideoDriver->getTexture("media/gun.jpg"));
    poGunNode->setPosition(core::vector3df(0, 500, 50));

    // Tests node
    scene::ISceneNode * poTestsNode = poFaerieNode;
    poTestsNode->setMaterialFlag(video::EMF_LIGHTING, false);
    poTestsNode->setMaterialFlag(video::EMF_FOG_ENABLE, true);

    // Camera
        // Keymap
    SKeyMap stCameraKeys[5];
    stCameraKeys[0].Action = EKA_JUMP_UP;
    stCameraKeys[0].KeyCode = KEY_SPACE;

    stCameraKeys[1].Action = EKA_MOVE_FORWARD;
    stCameraKeys[1].KeyCode = KEY_UP;

    stCameraKeys[2].Action = EKA_MOVE_BACKWARD;
    stCameraKeys[2].KeyCode = KEY_DOWN;

    stCameraKeys[3].Action = EKA_STRAFE_LEFT;
    stCameraKeys[3].KeyCode = KEY_LEFT;

    stCameraKeys[4].Action = EKA_STRAFE_RIGHT;
    stCameraKeys[4].KeyCode = KEY_RIGHT;

    //scene::ICameraSceneNode * poCamera = poSceneManager->addCameraSceneNode(NULL, core::vector3df(50, 0, 0), core::vector3df(0, 5, 25));
    scene::ICameraSceneNode * poCamera = poSceneManager->addCameraSceneNodeFPS(NULL, 100, 0.1, 0, stCameraKeys, 5, false, 0, true);
    poCamera->setPosition(core::vector3df(50, 200, 0));

    // Light
    /*scene::ILightSceneNode * poDiffuseLight = poSceneManager->addLightSceneNode(NULL, core::vector3df(50, 200, 0), video::SColor(0, 255, 200, 200), 200);
    poDiffuseLight->getLightData().Type = video::ELT_DIRECTIONAL;*/
    poSceneManager->setAmbientLight(video::SColor(0, 255, 255, 255));

    // General set-up
    poMainWindow->setWindowCaption(L"Tests d'Irrlicht");
    poMainWindow->getCursorControl()->setVisible(false);
    poVideoDriver->setFog(video::SColor(0, 255, 255, 255), video::EFT_FOG_EXP2, 0, 0, 0.01, true);

    // Override material
    /*poVideoDriver->getOverrideMaterial().EnableFlags = video::EMF_WIREFRAME;
    poVideoDriver->getOverrideMaterial().Material.setFlag(video::EMF_WIREFRAME, true);
    poVideoDriver->getOverrideMaterial().EnablePasses = scene::ESNRP_SOLID;*/

    // Event manager
    MyEventManager oEventManager(poSydneyNode, poMainWindow, poCamera);
    poMainWindow->setEventReceiver(&oEventManager);
    
    // Particles
    scene::IParticleSystemSceneNode * poParticleSysNode = poSceneManager->addParticleSystemSceneNode(false);
    scene::IParticleEmitter * poEmitter = poParticleSysNode->createBoxEmitter(
        core::aabbox3d<f32>(-6,0,-6,6,1,6), // coordonnees de la boite
        core::vector3df(0.0f,0.06f,0.0f),        // direction de diffusion
        80,100,                                       // nb particules emises a la sec min / max
        video::SColor(0,255,255,255),            // couleur la plus sombre
        video::SColor(0,255,255,255),            // couleur la plus claire
        600, 1200,                                    // duree de vie min / max
        0,                                            // angle max d'ecart / direction prevue
        core::dimension2df(8.0f,8.0f),           // taille minimum
        core::dimension2df(14.0f,14.0f));        // taille maximum

    poParticleSysNode->setEmitter(poEmitter);
    poEmitter->drop();

    poParticleSysNode->setMaterialFlag(video::EMF_LIGHTING, false);
    poParticleSysNode->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
    poParticleSysNode->setMaterialTexture(0, poVideoDriver->getTexture("media/fire.bmp"));
    poParticleSysNode->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);

    scene::IParticleAffector * poFadeOutAffector = poParticleSysNode->createFadeOutParticleAffector(video::SColor(0, 255, 0, 0), 1200);
    scene::IParticleAffector * poGravityAffector = poParticleSysNode->createGravityAffector(core::vector3df(0, -0.0001, 0), 1200);

    poParticleSysNode->addAffector(poFadeOutAffector);
    poParticleSysNode->addAffector(poGravityAffector);

    poFadeOutAffector->drop();
    poGravityAffector->drop();

    // Main loop

        // Camera position
    core::vector3df oCameraPosition;
    gui::IGUIStaticText * poCameraPositionText = poGUI->addStaticText(L"0 ; 0 ; 0", core::rect<s32>(100, 120, 250, 130), true, false, NULL, -1, true);

    while(poMainWindow->run())  // While the window isn't closed
    {
        oCameraPosition = poCamera->getPosition();
        wchar_t strCameraPosition[100];
        swprintf(strCameraPosition, L"%f ; %f ; %f", (float) oCameraPosition.X, (float) oCameraPosition.Y, (float) oCameraPosition.Z);

        poCameraPositionText->setText(strCameraPosition);

        // Initialize rendering
        poVideoDriver->beginScene(true,                                     // Back buffer (for double buffering)
                                  true,                                     // Z buffer
                                  video::SColor(255, 255, 255, 255));       // Background

        oEventManager.moveMesh();
        poSceneManager->drawAll();                                          // Draw all objects in scene
        poGUI->drawAll();

        poVideoDriver->endScene();                                          // Display render on screen
    }

    poMainWindow->drop();

    return 0;
}