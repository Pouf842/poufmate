#ifndef __INTRO_ANIMATOR_H_
#define __INTRO_ANIMATOR_H_

#include "irrlicht.h"
#include "interface_Irrlicht.h"

class IntroAnimator : public irr::scene::ISceneNodeAnimator
{
protected :
	irr::u32 muFirstCall;
	irr::u32 muLastCall;
	irr::core::vector3df moStartPos;
	irr::core::vector3df moEndPos;
	irr::u32 muTranslationTime;
	InterfaceIrrlicht * mpoCallbackObject;
	void (InterfaceIrrlicht::*mpfCallbackMethod)();
	bool mbCallBacked;
public :
	IntroAnimator(irr::core::vector3df oStartPosition, irr::core::vector3df oEndPosition, irr::u32 uTranslateTime);
	virtual ~IntroAnimator();
	void SetCallback(InterfaceIrrlicht*, void (InterfaceIrrlicht::*)());
	virtual void animateNode(irr::scene::ISceneNode *,irr::u32);
	virtual irr::scene::ISceneNodeAnimator * createClone(irr::scene::ISceneNode *, irr::scene::ISceneManager *);
};

#endif