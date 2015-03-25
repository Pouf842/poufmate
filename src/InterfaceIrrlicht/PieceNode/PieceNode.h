#ifndef __PIECE_NODE_H_
#define __PIECE_NODE_H_

#include "irrlicht.h"
#include "Pieces/piece.h"
#include "Core/Position.h"

class PieceNode : irr::scene::ISceneNode
{
protected :
	static const irr::core::map<Piece::PIECE_TYPE, irr::scene::IAnimatedMesh*> * mpoMeshes;
	Piece * mpoPiece;
	Position moBoardPosition;
	ISceneNode * mpoNode;
public :
	PieceNode(Piece *, const Position & = Position(0, 0), irr::scene::ISceneNode * = NULL, irr::scene::ISceneManager * = NULL);
	static void SetMeshes(irr::core::map<Piece::PIECE_TYPE, irr::scene::IAnimatedMesh*> *);

	void SetType(Piece::PIECE_TYPE);
	void SetColor(Piece::PIECE_COLOR);
	void SetPosition(const Position &);
};

#endif