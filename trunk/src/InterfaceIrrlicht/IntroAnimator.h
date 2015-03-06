#ifndef __INTRO_H_
#define __INTRO_H_

#include "irrlicht.h"

class IntroAnimator : public irr::scene::ISceneNodeAnimator
{
protected :
	irr::u32 muFirstCall;
	irr::u32 muLastCall;
	irr::core::vector3df moStartPos;
	irr::core::vector3df moEndPos;
	irr::u32 muTranslationTime;
	bool mbDone;
public :
	IntroAnimator(irr::core::vector3df oStartPosition, irr::core::vector3df oEndPosition, irr::u32 uTranslateTime);
	virtual void animateNode(irr::scene::ISceneNode *,irr::u32);
	virtual irr::scene::ISceneNodeAnimator * createClone(irr::scene::ISceneNode *, irr::scene::ISceneManager *);

	bool bIsDone();
};

#endif