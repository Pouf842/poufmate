#ifndef __PIECE_VIEWER_STATE_H_
#define __PIECE_VIEWER_STATE_H_

#include "../State.h"
#include "../../InterfaceIrrlicht.h"
#include "PieceViewerAnimator.h"

class PieceViewerAnimator;

class PieceViewerState : public State
{
protected :
	irr::scene::ISceneNode * mpoCurrentPiece;
	irr::scene::ILightSceneNode * mpoLight;
	PieceViewerAnimator * mpoAnimator;
	Piece::PIECE_TYPE meCurrentType;
	bool mbCurrentPieceWhite;
    bool mbChangingColor;
    bool mbStop;

	bool mbPresentingPieces;
	void PresentPieces();
	void NextPiece(Piece::PIECE_TYPE, bool = false);
public :
	PieceViewerState(InterfaceIrrlicht *);
    ~PieceViewerState();
    virtual void Show();
    virtual void Hide();
	virtual bool OnEvent(const irr::SEvent &);
};

#endif