#include "IntroAnimator.h"

using namespace irr;
using namespace scene;
using namespace core;

IntroAnimator::IntroAnimator(vector3df oStartPosition, vector3df oEndPosition, u32 uTranslateTime) : muFirstCall(0),
																									 muLastCall(0),
																									 moStartPos(oStartPosition),
																									 moEndPos(oEndPosition),
																									 muTranslationTime(uTranslateTime),
																									 mpoCallbackObject(NULL),
																									 mpfCallbackMethod(NULL),
																									 mbCallBacked(false)
{
}

IntroAnimator::~IntroAnimator()
{
}

void IntroAnimator::animateNode(ISceneNode * poNode, u32 uTime)
{
	if(muFirstCall == 0)
		muFirstCall = uTime;

	vector3df oRotationSpeed(0, 5*3.6, 0);

	float fTotalElapsedTime = uTime - muFirstCall;
	float fLastElapsedTime = uTime - muLastCall;
	float fFactor = (fTotalElapsedTime) / muTranslationTime;
	if(fFactor > 1)
		fFactor = 1;

	if(fTotalElapsedTime < muTranslationTime * 1.5)
	{
		fFactor = sin(fFactor * PI / 2);

		vector3df oTrajectory(moEndPos - moStartPos);
		vector3df oPos(moStartPos + oTrajectory * fFactor);
		poNode->setPosition(oPos);

		fFactor *= 0.95;
		fFactor = 1 - fFactor;

		poNode->setRotation(poNode->getRotation() + oRotationSpeed * fFactor * fLastElapsedTime / 10);
	}
	else
	{
		if(poNode->getPosition() != moEndPos)
			poNode->setPosition(moEndPos);
		
		poNode->setRotation(poNode->getRotation() + oRotationSpeed * 0.05 * fLastElapsedTime / 10);

		if(!mbCallBacked)
		{
			if(mpoCallbackObject && mpfCallbackMethod)
				(mpoCallbackObject->*mpfCallbackMethod)();
		}
	}

	muLastCall = uTime;
}

ISceneNodeAnimator * IntroAnimator::createClone(ISceneNode *, ISceneManager *)
{
	return NULL;
}