#ifndef __TOOLS_H_
#define __TOOLS_H_

#include "irrlicht.h"
#include "Core/Position.h"
#include <iostream>

inline std::ostream & operator<<(std::ostream & out, const irr::core::vector3df & oVec)
{
	out << "(" << oVec.X << " ; " << oVec.Y << " ; " << oVec.Z << ")";
	return out;
}

inline Position oGetBoardPosition(const irr::core::vector3df & oNodePos)
{
	return Position(irr::core::round32(-oNodePos.Z - 0.6) + 4, irr::core::round32(oNodePos.X - 0.6) + 4);
}

inline irr::core::vector3df vGetNodePosition(int X, int Y)
{
	return irr::core::vector3df(Y - 3.5, 0.5, 3.5 - X);
}

inline irr::core::vector3df vGetNodePosition(const Position & oPos)
{
	return vGetNodePosition(oPos.mX, oPos.mY);
}

//inline void moveNodeInLocalSpace(irr::scene::ISceneNode* node, const irr::core::vector3df& distVect)
//{
//    node->updateAbsolutePosition();
//	irr::core::matrix4 m = node->getAbsoluteTransformation();
//    irr::core::vector3df d = distVect;
//    m.rotateVect(d);
//        
//    irr::core::vector3df pos = node->getAbsolutePosition() + d;
//    node->setPosition(pos);
//}
//
//inline void rotateNodeInLocalSpace(irr::scene::ISceneNode* node, irr::f32 degs, const irr::core::vector3df& axis)
//{
//    node->updateAbsolutePosition();
//    irr::core::matrix4 m2 = node->getAbsoluteTransformation();
//    irr::core::vector3df a = axis;
//    m2.rotateVect(a);
//    a.normalize();
// 
//    irr::core::quaternion q;
//    q.fromAngleAxis(degs * irr::core::DEGTORAD, a);
//    irr::core::matrix4 m1 = q.getMatrix();
// 
//    irr::core::matrix4 m = m1*m2;
//    node->setRotation(m.getRotationDegrees());
//    
//}
//
//inline void revolveNodeInLocalSpace(irr::scene::ISceneNode* node, irr::f32 degs, const irr::core::vector3df& axis, const irr::core::vector3df& pivot)
//{
//    moveNodeInLocalSpace(node, pivot);
//    rotateNodeInLocalSpace(node, degs, axis);
//    moveNodeInLocalSpace(node, -pivot);
//}

#endif