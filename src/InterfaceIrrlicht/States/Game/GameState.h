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
	irr::core::map<Piece*, irr::scene::ISceneNode*> moPieces;
    irr::scene::ISceneNode * mpoBoardNode;

    void PlaceCamera(bool bBack = false);

public :
	GameState(InterfaceIrrlicht *);
    virtual void Show();
    virtual void Hide();
    virtual void InitBoard(const Board &);
	virtual bool OnEvent(const irr::SEvent &);
};

#endif