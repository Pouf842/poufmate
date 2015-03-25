#include "PieceNode.h"

#include <exception>

using namespace std;
using namespace irr;
using namespace core;
using namespace scene;

const irr::core::map<Piece::PIECE_TYPE, irr::scene::IAnimatedMesh*> * PieceNode::mpoMeshes = NULL;

PieceNode::PieceNode(Piece * poPiece, const Position & oPos, irr::scene::ISceneNode * poParent, irr::scene::ISceneManager * poSceneManager) :
	ISceneNode(poParent, poSceneManager),
	mpoPiece(),
	moBoardPosition(oPos)
{
	if(!mpoMeshes)
		throw exception("Meshes are not initialized");

	if(!mpoMeshes->find(poPiece->eGetType()))
		throw exception("Piece mesh could not be found");
}

void PieceNode::SetType(Piece::PIECE_TYPE eType)
{
}

void PieceNode::SetColor(Piece::PIECE_COLOR eColor)
{
}

void PieceNode::SetPosition(const Position & oPos)
{
}

void PieceNode::SetMeshes(irr::core::map<Piece::PIECE_TYPE, irr::scene::IAnimatedMesh*> * poMeshes)
{
	mpoMeshes = poMeshes;
}