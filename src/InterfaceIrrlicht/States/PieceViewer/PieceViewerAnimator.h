#ifndef __PIECE_VIEWER_ANIMATOR_H_
#define __PIECE_VIEWER_ANIMATOR_H_

#include "irrlicht.h"

class PieceViewerAnimator : public irr::scene::ISceneNodeAnimator
{
protected :
	irr::core::vector3df mvPivot;
	bool mbStarted;
	irr::u32 muLastCall;
public :
	PieceViewerAnimator(const irr::core::vector3df & vPivot = irr::core::vector3df(0, 0, 0));
	virtual void animateNode(irr::scene::ISceneNode *, irr::u32);
	virtual irr::scene::ISceneNodeAnimator * createClone(irr::scene::ISceneNode *, irr::scene::ISceneManager *);
	void SetPivot(const irr::core::vector3df &);
	void Start(irr::u32);
};

#endif
