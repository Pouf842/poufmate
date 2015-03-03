#ifndef __GAME_H_
#define __GAME_H_

#include "irrlicht.h"

class Controller;
class Ship;

class Game
{
protected :
	irr::IrrlichtDevice * mpoDevice;
	irr::scene::ISceneManager * mpoSceneManager;
	irr::gui::IGUIEnvironment * mpoGUI;
	irr::video::IVideoDriver * mpoVideoDriver;
	Ship * mpoShip;
	Controller * mpoController;

	void Init();
	void CreateWorld();
public :
	Game();
	void run();
};

#endif