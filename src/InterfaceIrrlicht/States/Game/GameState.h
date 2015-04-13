#ifndef __GAME_STATE_H_
#define __GAME_STATE_H_

#include "../State.h"
#include "Core/board.h"

class GameState : public State
{
protected :
	irr::scene::ISceneNode * mpoHighlightedPiece;
	irr::core::vector3df moRelColl;
	bool mbIsDragging;
    irr::core::list<irr::scene::ISceneNode*> moPossibleMoves;
	irr::core::map<Piece *, irr::scene::ISceneNode *> moPieces;
    irr::scene::ISceneNode * mpoBoardNode;
    irr::video::ITexture * mpoPossibleMoveTex;

    void PlaceCamera(bool bBack = false);

public :
    GameState(InterfaceIrrlicht *);
    virtual void MovePiece(Piece *, const Position &);
    virtual void RemovePiece(Piece *);
    virtual void AddPiece(Piece *, const Position &);
    virtual void PieceEatPiece(Piece *, Piece *);
    virtual void Show();
    virtual void Hide();
    virtual void InitBoard(const Board &);
	virtual bool OnEvent(const irr::SEvent &);
};

#endif