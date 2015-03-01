#include "Ship.h"
#include "Controller.h"

#include <iostream>
#include <exception>
#include <string>

using namespace std;
using namespace irr;
using namespace core;
using namespace scene;

extern f32 fElapsedSecs;
extern s32 sScreenWidth;
extern s32 sScreenHeight;

ostream & operator<<(ostream & stream, const vector3df & vec)
{
	stream << vec.X << " ; " << vec.Y << " ; " << vec.Z << ")" << endl;
	return stream;
}

Ship::Ship(Controller * poController, ISceneNode * poShip, ICameraSceneNode * poCamera) : mpoShip(poShip),
																						  mpoCamera(poCamera),
																						  MOVEMENT_ACC(1000),
																						  mvSpeed(0, 0, 0),
																						  MAX_SPEED(500),
																						  ROTATION_SPEED(750)
{
	setController(poController);
}

void Ship::setController(Controller * poController)
{
	if(!poController)
		throw exception("Ship can't be instancied without a controller");

	mpoController = poController;
}

void Ship::setShip(ISceneNode * poShip)
{
	mpoShip = poShip;
}

void Ship::setCamera(ICameraSceneNode * poCamera)
{
	mpoCamera = poCamera;
}

void Ship::update()
{
	if(mpoShip)
		updateShip();

	if(mpoCamera)
		updateCamera();
}

void Ship::updateShip()
{
	updateShipPosition();
	updateShipRotation();
}

void Ship::updateShipPosition()
{
	vector3df vThrottle;

	if(!mpoController->bAutoStop())
	{
		EKEY_CODE sKeysPositive[3] = {KEY_RIGHT, KEY_RSHIFT, KEY_UP};
		EKEY_CODE sKeysNegative[3] = {KEY_LEFT, KEY_RCONTROL, KEY_DOWN};
		f32 * sThrottleAxe[3] = {&vThrottle.X, &vThrottle.Y, &vThrottle.Z};
		f32 * sSpeedAxe[3] = {&mvSpeed.X, &mvSpeed.Y, &mvSpeed.Z};

		for(u32 i = 0; i < 3; ++i)
		{
			if(mpoController->bIsKeyDown(sKeysPositive[i]))
				*sThrottleAxe[i] = MOVEMENT_ACC;
			else if(mpoController->bIsKeyDown(sKeysNegative[i]))
				*sThrottleAxe[i] = -MOVEMENT_ACC;
			else
				*sThrottleAxe[i] = 0;
		}

		matrix4 mShipOrientation;
		mShipOrientation.setRotationDegrees(mpoShip->getRotation());
		mShipOrientation.transformVect(vThrottle);
		mvSpeed += vThrottle * fElapsedSecs;
	}
	else
	{
		vThrottle = -mvSpeed;
		vThrottle = vThrottle.normalize() * MOVEMENT_ACC;

		mvSpeed += vThrottle * fElapsedSecs;

		if(mvSpeed.getLengthSQ() < 25)
		{
			mvSpeed = vector3df();
			mpoController->stopAutoStop();
		}
	}

	if(mvSpeed.getLength() > MAX_SPEED)
		mvSpeed = mvSpeed.normalize() * MAX_SPEED;

	mpoShip->setPosition(mpoShip->getPosition() + mvSpeed * fElapsedSecs);
}

void Ship::updateShipRotation()
{
	vector3df vRotation(0, 0, 0);

	/*EKEY_CODE sKeysPositive[3] = {KEY_KEY_I, KEY_KEY_L, KEY_KEY_U};
	EKEY_CODE sKeysNegative[3] = {KEY_KEY_K, KEY_KEY_J, KEY_KEY_O};
	f32 * sRotationAxe[3] = {&vRotation.X, &vRotation.Y, &vRotation.Z};

	for(u32 i = 0; i < 3; ++i)
	{
		if(bIsKeyDown(sKeysPositive[i]))
			*sRotationAxe[i] = ROTATION_SPEED;
		else if(bIsKeyDown(sKeysNegative[i]))
			*sRotationAxe[i] = -ROTATION_SPEED;

		if(*sRotationAxe[i] > 360)
			*sRotationAxe[i] -= 360;
		else if(*sRotationAxe[i] < -360)
			*sRotationAxe[i] += 360;
	}*/

	f32 * sRotationAxe[4]  = {&vRotation.Z, &vRotation.X, NULL, &vRotation.Y};

	SEvent::SJoystickEvent oJoystickState = mpoController->oGetJoystickState();

	for(u32 i = 0; i < oJoystickState.NUMBER_OF_AXES - 1; ++i)
		if(sRotationAxe[i])
			if(oJoystickState.Axis[i] > 6000
			||  oJoystickState.Axis[i] < -6000)
				*sRotationAxe[i] = ((float) oJoystickState.Axis[i]) / 32727 * 360;

	vRotation.X = -vRotation.X;
	vRotation.Z = -vRotation.Z;

	if(vRotation.X != 0
	|| vRotation.Y != 0
	|| vRotation.Z != 0)
	{
		vRotation *= fElapsedSecs;
		matrix4 mTransform;
		mTransform.setRotationDegrees(mpoShip->getRotation());
		matrix4 mRotation;
		mRotation.setRotationDegrees(vRotation);
		mTransform *= mRotation;
		mpoShip->setRotation(mTransform.getRotationDegrees());
	}
}

void Ship::updateCamera()
{
	vector3df vUp(0, 1, 0);
	vector3df vForward(0, 0, 1);

	SEvent::SMouseInput oMouseState = mpoController->oGetMouseState();
	vector2df mousePosRelativeToCenter(oMouseState.X - (sScreenWidth >> 1), oMouseState.Y - (sScreenHeight >> 1));
	vector2df mouseRatio(mousePosRelativeToCenter.X / (sScreenWidth >> 1), mousePosRelativeToCenter.Y / (sScreenHeight >> 1));
	mouseRatio.X *= 60;
	mouseRatio.Y *= 60;

	vector3df vCameraOrientation = vector3df(mouseRatio.Y, mouseRatio.X, 0);

	matrix4 mTransform;
	mTransform.setRotationDegrees(mpoShip->getRotation());

	matrix4 mCameraRotation;
	mCameraRotation.setRotationDegrees(vCameraOrientation);
	mTransform *= mCameraRotation;

	mTransform.transformVect(vUp);
	mTransform.transformVect(vForward);

	mpoCamera->setUpVector(vUp);
	mpoCamera->setTarget(mpoShip->getPosition() + vForward);

	/*vector3df vRotate(0, 0, 0);

	if(bIsKeyDown(KEY_KEY_J))
		vRotate.Y = -ROTATION_SPEED;
	else if(bIsKeyDown(KEY_KEY_L))
		vRotate.Y = ROTATION_SPEED;

	vector3df vNewRotation = mpoCamera->getRotation() + vRotate * fElapsedSecs;
	mpoCamera->setRotation(vNewRotation);*/
}

vector3df Ship::vGetSpeed()
{
	return mvSpeed;
}
