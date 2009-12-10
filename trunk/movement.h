#ifndef __MOVEMENT_H_
#define __MOVEMENT_H_

#include "piece.h"
#include "coordinates.h"

class Movement
{
  protected :
	Coordinates moCoords1;
	Coordinates moCoords2;

	Piece * mpoMovingPiece;
	Piece * mpoCapturedPiece;

  public :
	Movement(Coordinates oCoords1,
			 Coordinates oCoords2,
			 Piece * poMovingPiece, Piece * poCapturedPiece = 0);
	Coordinates oGetCoords1() const;
	Coordinates oGetCoords2() const;
	virtual void CancelMovement(Board &) const;

	Piece * poGetMovingPiece() const;
	Piece * poGetCapturedPiece() const;

	Piece::Color eGetPlayerColor() const;
};

#endif