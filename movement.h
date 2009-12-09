#ifndef __MOVEMENT_H
#define __MOVEMENT_H_

#include "piece.h"

class Movement
{
  protected :
	unsigned int mX1;
	unsigned int mY1;
	unsigned int mX2;
	unsigned int mY2;

	bool mbIsFirstMove;
	bool mbIsCastling;

	Piece * mpoMovingPiece;
	Piece * mpoCapturedPiece;

	Piece::Color mePlayerColor;

  public :
	Movement(Piece::Color, unsigned int X1, unsigned int Y1,
			 unsigned int X2, unsigned int Y2,
			 Piece * poMovingPiece, Piece * poCapturedPiece = 0,
			 bool bIsFirstMove = false, bool bIsCastling = false);
	unsigned int iGetX1();
	unsigned int iGetX2();
	unsigned int iGetY1();
	unsigned int iGetY2();

	bool IsFirstMove();
	bool IsCastling();

	Piece * poGetMovingPiece();
	Piece * poGetCapturedPiece();

	Piece::Color eGetPlayerColor();
};

#endif