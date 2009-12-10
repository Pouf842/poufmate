#ifndef __MOVEMENT_H_
#define __MOVEMENT_H_

#include "piece.h"
#include "position.h"

class Movement
{
  protected :
	Position moPos1;
	Position moPos2;

	Piece * mpoMovingPiece;
	Piece * mpoCapturedPiece;

  public :
	Movement(Position oPos1,
			 Position oPos2,
			 Piece * poMovingPiece, Piece * poCapturedPiece = 0);
	Position oGetCoords1() const;
	Position oGetCoords2() const;
	virtual void CancelMovement(Board &) const;

	Piece * poGetMovingPiece() const;
	Piece * poGetCapturedPiece() const;

	Piece::Color eGetPlayerColor() const;
};

#endif