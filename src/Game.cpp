#ifdef __DEBUG_
	#include <string>
	#include <sstream>
	#include <iostream>
#endif

#include <exception>
#include "Game.h"
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

Game::Game()
{
}

void Game::Init()
{
	mpoController = new Controller();
	mpoDevice = createDevice(EDT_OPENGL, dimension2d<u32>(sScreenWidth, sScreenHeight), 32, false, false, false, mpoController);
	
	if(!mpoDevice)
		throw exception("Cannot create device");

	mpoSceneManager = mpoDevice->getSceneManager();
	mpoVideoDriver = mpoDevice->getVideoDriver();
	mpoGUI = mpoDevice->getGUIEnvironment();

	array<SJoystickInfo> josticks;
	mpoDevice->activateJoysticks(josticks);
	mpoDevice->setWindowCaption(L"Mes tests Irrlicht");

	mpoDevice->getCursorControl()->setPosition(sScreenWidth >> 1, sScreenHeight >> 1);
	mpoDevice->getCursorControl()->setVisible(false);
}

void Game::CreateWorld()
{	
	IMesh * poCubeMesh = mpoSceneManager->getGeometryCreator()->createCubeMesh(vector3df(1, 1, 1));
	mpoSceneManager->getMeshManipulator()->flipSurfaces(poCubeMesh);

	IMeshSceneNode * poCubeNode = mpoSceneManager->addOctreeSceneNode(poCubeMesh);
	poCubeNode->setPosition(vector3df(0, 0, 0));
	poCubeNode->setRotation(vector3df(90, 0, 0));
	poCubeNode->setScale(vector3df(10000, 10000, 10000));

	poCubeNode->setMaterialFlag(EMF_LIGHTING, false);

	poCubeNode->setMaterialTexture(0, mpoVideoDriver->getTexture("media/rockwall.jpg"));
	poCubeNode->getMaterial(0).getTextureMatrix(0).setTextureScale(10, 10);
	poCubeNode->getMaterial(0).TextureLayer->TextureWrapU = video::ETC_REPEAT;

	IMesh * poShipNodeMesh = mpoSceneManager->getGeometryCreator()->createSphereMesh(10, 32, 32);
	mpoSceneManager->getMeshManipulator()->flipSurfaces(poShipNodeMesh);

	IMeshSceneNode * mpoShipNode = mpoSceneManager->addOctreeSceneNode(poShipNodeMesh);
	mpoShipNode->setPosition(vector3df(0, 0, 0));
	mpoShipNode->setMaterialFlag(EMF_LIGHTING, false);
	mpoShipNode->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);
	mpoShipNode->setMaterialTexture(0, mpoVideoDriver->getTexture("media/earth.jpg"));

	ICameraSceneNode * poCamera = mpoSceneManager->addCameraSceneNode(/**/mpoShipNode/*/NULL/**/);
	poCamera->bindTargetAndRotation(false);
	poCamera->setFarValue(20000);

	mpoShip = new Ship(mpoController, mpoShipNode, poCamera);

	ITriangleSelector * poTriangleSelector = mpoSceneManager->createOctreeTriangleSelector(poCubeMesh, poCubeNode, 128);
	poCubeNode->setTriangleSelector(poTriangleSelector);
	
	mpoShipNode->addAnimator(mpoSceneManager->createCollisionResponseAnimator(poTriangleSelector, mpoShipNode, vector3df(30, 50, 30), vector3df(0, 0, 0), vector3df(0, 30, 0)));
	//mpoSceneManager->addLightSceneNode();

	ISceneNode * poEarth = mpoSceneManager->addSphereSceneNode(50, 64);
	poEarth->getMaterial(0).setTexture(0, mpoVideoDriver->getTexture("media/earth.jpg"));
	poEarth->setMaterialFlag(EMF_LIGHTING, false);

	ISceneNodeAnimator * poEarthAnimator = mpoSceneManager->createFlyCircleAnimator(vector3df(0, 0, 0), 100, 2 * PI / 10000);
	poEarth->addAnimator(poEarthAnimator);

	ISceneNodeAnimator * poEarthAnimator2 = mpoSceneManager->createRotationAnimator(vector3df(0, ((f32) 360) / 1000, 0));
	poEarth->addAnimator(poEarthAnimator2);
}

void Game::run()
{
	try
	{
		Init();
		CreateWorld();

		// In order to do framerate independent movement, we have to know
		// how long it was since the last frame
		u32 uThen = mpoDevice->getTimer()->getTime();
		
		IGUIStaticText * poSpeedText = mpoGUI->addStaticText(L"", rect<s32>(0, 0, 50, 100), true, true, NULL, -1, true);

		vector2d<s32> vMousePos;
		bool bCapMouse = false;

		while(mpoDevice->run() && !mpoController->bExit())
		{
			if(mpoDevice->isWindowActive())
			{
				u32 uNow = mpoDevice->getTimer()->getTime();
				fElapsedSecs = (f32) (uNow - uThen) / 1000.f;

				mpoVideoDriver->beginScene(true, true);//, SColor(0, 255, 255, 0));
				mpoShip->update();

				wstringstream debugSpeed;
				debugSpeed << "dX = " << mpoShip->vGetSpeed().X << endl;
				debugSpeed << "dY = " << mpoShip->vGetSpeed().Y << endl;
				debugSpeed << "dZ = " << mpoShip->vGetSpeed().Z << endl;

				poSpeedText->setText(debugSpeed.str().c_str());

				mpoSceneManager->drawAll();
				mpoGUI->drawAll();
				mpoVideoDriver->endScene();

				vMousePos = mpoDevice->getCursorControl()->getPosition();
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
					mpoDevice->getCursorControl()->setPosition(vMousePos.X, vMousePos.Y);

				uThen = uNow;
			}
			else
				mpoDevice->yield();
		}
	}
	catch(const exception & e)
	{
	}

	if(mpoDevice)
	{
		try
		{
			mpoDevice->drop();
		}
		catch(...)
		{
		}
	}
}
