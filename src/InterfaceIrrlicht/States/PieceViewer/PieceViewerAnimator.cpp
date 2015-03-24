#include "PieceViewerAnimator.h"
#include "../../Tools.h"

using namespace std;
using namespace irr;
using namespace core;
using namespace scene;

PieceViewerAnimator::PieceViewerAnimator(const vector3df & vPivot) : muLastCall(0), mvPivot(vPivot), mbStarted(false)
{
}

void PieceViewerAnimator::animateNode(ISceneNode * poNode, u32 uTime)
{
	if(!mbStarted)
		return;

	float fFactor = (uTime - muLastCall) / ((float) 5000);
	quaternion qRotation;

	/*/float fGapFactor = (fFactor > 1 ? 1 : fFactor);

	while(fFactor > 2)
		fFactor -= 2;

	qRotation.fromAngleAxis(2 * PI * fFactor, vector3df(0, 1, 0));

	vector3df vRotation(-0.5 * fGapFactor, -1, 0);
	vRotation = vRotation.normalize() * (mvPivot - poNode->getPosition()).getLength();
	qRotation.getMatrix().rotateVect(vRotation);

	poNode->setPosition(mvPivot + vRotation);

	qRotation.rotationFromTo(vector3df(0, 1, 0), -vRotation);
	poNode->setRotation(qRotation.getMatrix().getRotationDegrees());
	/*/

	while(fFactor > 1)
		fFactor -= 1;

	poNode->setRotation(vector3df(0, 360 * fFactor, 0));/**/
}

ISceneNodeAnimator * PieceViewerAnimator::createClone(ISceneNode * poNode, ISceneManager * poSceneManager)
{
	return NULL;
}

void PieceViewerAnimator::SetPivot(const vector3df & vNewPivot)
{
	mvPivot = vNewPivot;
}

void PieceViewerAnimator::Start(u32 uNow)
{
	muLastCall = uNow;
	mbStarted = true;
}