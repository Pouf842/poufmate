#include "movement.h"

Movement::Movement(Piece::Color ePlayer,
				   unsigned int X1, unsigned int Y1,
				   unsigned int X2, unsigned int Y2,
				   Piece * poMovingPiece, Piece * poCapturedPiece,
				   bool bIsFirstMove, bool bIsCastling)
{
	mePlayerColor = ePlayer;
	mX1 = X1;
	mX2 = X2;
	mY1 = Y1;
	mY2 = Y2;

	mpoMovingPiece = poMovingPiece;
	mpoCapturedPiece = poCapturedPiece;

	mbIsFirstMove = bIsFirstMove;
	mbIsCastling = bIsCastling;
}

unsigned int Movement::iGetX1()
{
	return mX1;
}

unsigned int Movement::iGetX2()
{
	return mX2;
}

unsigned int Movement::iGetY1()
{
	return mY1;
}

unsigned int Movement::iGetY2()
{
	return mY2;
}

Piece * Movement::poGetMovingPiece()
{
	return mpoMovingPiece;
}

Piece * Movement::poGetCapturedPiece()
{
	return mpoCapturedPiece;
}

Piece::Color Movement::eGetPlayerColor()
{
	return mePlayerColor;
}