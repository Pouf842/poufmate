#ifndef __MOVEMENT_H
#define __MOVEMENT_H_

#include "piece.h"
#include "coordinates.h"

class Movement
{
  protected :
	Coordinates moCoords1;
	Coordinates moCoords2;

	bool mbIsFirstMove;
	bool mbIsCastling;

	Piece * mpoMovingPiece;
	Piece * mpoCapturedPiece;

	Piece::Color mePlayerColor;

  public :
	Movement(Piece::Color, Coordinates oCoords1,
			 Coordinates oCoords2,
			 Piece * poMovingPiece, Piece * poCapturedPiece = 0,
			 bool bIsFirstMove = false, bool bIsCastling = false);
	Coordinates oGetCoords1();
	Coordinates oGetCoords2();

	bool IsFirstMove();
	bool IsCastling();

	Piece * poGetMovingPiece();
	Piece * poGetCapturedPiece();

	Piece::Color eGetPlayerColor();
};

#endif