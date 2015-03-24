#include "IntroState.h"
#include "IntroAnimator.h"

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;

IntroState::IntroState(InterfaceIrrlicht * poInterface) : State(poInterface), mpoAnimator(NULL)
{
	mpoAnimator = new IntroAnimator(vector3df(0, 0, 500), vector3df(0, 0, 0), 2000);
	mpoInterface->mpoBoardNode->addAnimator(mpoAnimator);
}

IntroState::~IntroState()
{
	mpoInterface->mpoBoardNode->setPosition(vector3df(0, 0, 0));
	mpoInterface->mpoBoardNode->setRotation(vector3df(0, 0, 0));
	mpoInterface->mpoBoardNode->removeAnimator(mpoAnimator);
	delete mpoAnimator;
}