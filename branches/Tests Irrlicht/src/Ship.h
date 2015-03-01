#ifndef __SHIP_H_
#define __SHIP_H_

#include <irrlicht.h>

class Controller;

class Ship
{
protected :
	irr::core::vector3df mvSpeed;
	const irr::f32 MOVEMENT_ACC;
	const irr::f32 MAX_SPEED;
	irr::scene::ISceneNode * mpoShip;
	Controller * mpoController;

	void updateShip();
	void updateShipPosition();
	void updateShipRotation();

	// Camera control
	irr::f32 ROTATION_SPEED;
	irr::scene::ICameraSceneNode * mpoCamera;
	
	void updateCamera();
public :
	Ship(Controller * poController, irr::scene::ISceneNode * poShip = NULL, irr::scene::ICameraSceneNode * poCamera = NULL);
	virtual void setShip(irr::scene::ISceneNode * poShip);
	virtual void setCamera(irr::scene::ICameraSceneNode * poCamera);
	virtual void setController(Controller * poController);
	virtual void update();
	virtual irr::core::vector3df vGetSpeed();
};

#endif