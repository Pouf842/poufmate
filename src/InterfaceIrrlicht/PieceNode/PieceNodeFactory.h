#ifndef __PIECE_NODE_FACTORY_H_
#define __PIECE_NODE_FACTORY_H_

#include "irrlicht.h"

class PieceNodeFactory : irr::scene::ISceneNodeFactory
{
public :
	PieceNodeFactory();
	irr::scene::ISceneNode * addSceneNode(const irr::c8 *, irr::scene::ISceneNode *);
	irr::scene::ISceneNode * irr::scene::ISceneNodeFactory::addSceneNode(irr::scene::ESCENE_NODE_TYPE,irr::scene::ISceneNode *);
	irr::u32 irr::scene::ISceneNodeFactory::getCreatableSceneNodeTypeCount(void) const;
	irr::scene::ESCENE_NODE_TYPE irr::scene::ISceneNodeFactory::getCreateableSceneNodeType(irr::u32) const;
	const irr::c8 * irr::scene::ISceneNodeFactory::getCreateableSceneNodeTypeName(irr::scene::ESCENE_NODE_TYPE) const;
	const irr::c8 * irr::scene::ISceneNodeFactory::getCreateableSceneNodeTypeName(irr::u32) const;
};

#endif
