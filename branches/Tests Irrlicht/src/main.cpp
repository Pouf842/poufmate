#include <irrlicht.h>
#include <exception>
#include <string>
#include <sstream>
#include <iostream>
#include "Controller.h"
#include "Ship.h"

using namespace std;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

f32 fElapsedSecs = 0;
s32 sScreenWidth = 800;
s32 sScreenHeight = 600;

template<typename T>
const T & cap(const T & data, const T & minLimit, const T & maxLimit)
{
	T ret;
	ret = max(data, minLimit);
	ret = min(ret, maxLimit);

	return ret;
}

int main()
{
	IrrlichtDevice * poDevice;
	ISceneManager * poSceneManager;
	IVideoDriver * poVideoDriver;
	IGUIEnvironment * poGUI;

	try
	{
		Controller * poController = new Controller();
		poDevice = createDevice(EDT_OPENGL, dimension2d<u32>(sScreenWidth, sScreenHeight), 32, false, false, false, poController);
		
		if(!poDevice)
			throw exception("Cannot create device");

		poDevice->getCursorControl()->setPosition(sScreenWidth >> 1, sScreenHeight >> 1);
		poDevice->getCursorControl()->setVisible(false);
		array<SJoystickInfo> joysticks;
		poDevice->activateJoysticks(joysticks);

		poDevice->setWindowCaption(L"Mes tests Irrlicht");
		poSceneManager = poDevice->getSceneManager();
		poVideoDriver = poDevice->getVideoDriver();
		poGUI = poDevice->getGUIEnvironment();

		IMesh * poCubeMesh = poSceneManager->getGeometryCreator()->createCubeMesh(vector3df(1, 1, 1));
		poSceneManager->getMeshManipulator()->flipSurfaces(poCubeMesh);

		IMeshSceneNode * poCubeNode = poSceneManager->addOctreeSceneNode(poCubeMesh);
		poCubeNode->setPosition(vector3df(0, 0, 0));
		poCubeNode->setRotation(vector3df(90, 0, 0));
		poCubeNode->setScale(vector3df(10000, 10000, 10000));

		poCubeNode->setMaterialFlag(EMF_LIGHTING, false);

		poCubeNode->setMaterialTexture(0, poVideoDriver->getTexture("media/rockwall.jpg"));
		poCubeNode->getMaterial(0).getTextureMatrix(0).setTextureScale(10, 10);
		poCubeNode->getMaterial(0).TextureLayer->TextureWrapU = video::ETC_REPEAT;
		poCubeNode->getMaterial(0).TextureLayer->TextureWrapV = video::ETC_REPEAT;

		IMesh * poShipNodeMesh = poSceneManager->getGeometryCreator()->createSphereMesh(10, 32, 32);
		poSceneManager->getMeshManipulator()->flipSurfaces(poShipNodeMesh);

		IMeshSceneNode * poShipNode = poSceneManager->addOctreeSceneNode(poShipNodeMesh);
		poShipNode->setPosition(vector3df(0, 0, 0));
		poShipNode->setMaterialFlag(EMF_LIGHTING, false);
		poShipNode->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);
		poShipNode->setMaterialTexture(0, poVideoDriver->getTexture("media/earth.jpg"));

		ICameraSceneNode * poCamera = poSceneManager->addCameraSceneNode(/**/poShipNode/*/NULL/**/);
		poCamera->bindTargetAndRotation(false);
		poCamera->setFarValue(20000);

		Ship * poShip = new Ship(poController, poShipNode, poCamera);

		ITriangleSelector * poTriangleSelector = poSceneManager->createOctreeTriangleSelector(poCubeMesh, poCubeNode, 128);
		poCubeNode->setTriangleSelector(poTriangleSelector);
		
		poShipNode->addAnimator(poSceneManager->createCollisionResponseAnimator(poTriangleSelector, poShipNode, vector3df(30, 50, 30), vector3df(0, 0, 0), vector3df(0, 30, 0)));
		//poSceneManager->addLightSceneNode();

		ISceneNode * poEarth = poSceneManager->addSphereSceneNode(50, 64);
		poEarth->getMaterial(0).setTexture(0, poVideoDriver->getTexture("media/earth.jpg"));
		poEarth->setMaterialFlag(EMF_LIGHTING, false);

		ISceneNodeAnimator * poEarthAnimator = poSceneManager->createFlyCircleAnimator(vector3df(0, 0, 0), 100, 2 * PI / 10000);
		poEarth->addAnimator(poEarthAnimator);

		ISceneNodeAnimator * poEarthAnimator2 = poSceneManager->createRotationAnimator(vector3df(0, ((f32) 360) / 1000, 0));
		poEarth->addAnimator(poEarthAnimator2);
		// In order to do framerate independent movement, we have to know
		// how long it was since the last frame
		u32 uThen = poDevice->getTimer()->getTime();

		poGUI->getSkin()->setFont(poGUI->getFont("media/fonthaettenschweiler.bmp"));
		IGUIStaticText * poSpeedText = poGUI->addStaticText(L"", rect<s32>(0, 0, 50, 100), true, false, 0, -1, true);
		poSpeedText->setBackgroundColor(SColor(255, 255, 255, 255));

		IGUIStaticText * poPositionText = poGUI->addStaticText(L"", rect<s32>(750, 500, 800, 600), true, false, 0, -1, true);
		poPositionText->setBackgroundColor(SColor(255, 255, 255, 255));

		poDevice->getCursorControl()->setPosition(sScreenWidth >> 1, sScreenHeight >> 1);
		
		vector2d<s32> vMousePos;
		bool bCapMouse = false;

		while(poDevice->run() && !poController->bExit())
		{
			if(poDevice->isWindowActive())
			{
				u32 uNow = poDevice->getTimer()->getTime();
				fElapsedSecs = (f32) (uNow - uThen) / 1000.f;

				poVideoDriver->beginScene(true, true);//, SColor(0, 255, 255, 0));
				poShip->update();

				std::wstringstream wssText;

				vector3df vData= poShip->vGetSpeed();

				wssText << "vX = " << vData.X << endl;
				wssText << "vY = " << vData.Y << endl;
				wssText << "vZ = " << vData.Z << endl;
				wssText << endl;

				poSpeedText->setText(wssText.str().c_str());

				wssText.str(L"");
				vData = poShipNode->getPosition();

				wssText << "X = " << vData.X << endl;
				wssText << "Y = " << vData.Y << endl;
				wssText << "Z = " << vData.Z << endl;
				wssText << endl;

				poPositionText->setText(wssText.str().c_str());

				poSceneManager->drawAll();
				poGUI->drawAll();
				poVideoDriver->endScene();

				vMousePos = poDevice->getCursorControl()->getPosition();
				if(vMousePos.X < 0 || vMousePos.X > sScreenWidth)
				{
					vMousePos.X = cap(vMousePos.X, 0, sScreenWidth);
					bCapMouse = true;
				}

				if(vMousePos.Y < 0 || vMousePos.Y > sScreenHeight)
				{
					vMousePos.Y = cap(vMousePos.Y, 0, sScreenHeight);
					bCapMouse = true;
				}

				if(bCapMouse)
					poDevice->getCursorControl()->setPosition(vMousePos.X, vMousePos.Y);

				uThen = uNow;
			}
			else
				poDevice->yield();
		}
	}
	catch(const exception & e)
	{
	}

	if(poDevice)
	{
		try
		{
			poDevice->drop();
		}
		catch(...)
		{
		}
	}
}