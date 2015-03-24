#ifndef __PIECE_NODE_H_
#define __PIECE_NODE_H_

#include "irrlicht.h"
#include "Core/Position.h"

class Piece;

class PieceNode : irr::scene::ISceneNode
{
protected :
	Piece * mpoPiece;
	Position moBoardPosition;
	ISceneNode * mpoNode;
public :
	PieceNode(irr::scene::IAnimatedMesh *, Piece * = NULL);
};

#endif