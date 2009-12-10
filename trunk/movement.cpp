#include "movement.h"

Movement::Movement(Piece::Color ePlayer,
				   Coordinates oCoords1, Coordinates oCoords2,
				   Piece * poMovingPiece, Piece * poCapturedPiece,
				   bool bIsFirstMove, bool bIsCastling) : moCoords1(oCoords1), moCoords2(oCoords2)
{
	mePlayerColor = ePlayer;

	mpoMovingPiece = poMovingPiece;
	mpoCapturedPiece = poCapturedPiece;

	mbIsFirstMove = bIsFirstMove;
	mbIsCastling = bIsCastling;
}

Coordinates Movement::oGetCoords1()
{
	return moCoords1;
}

Coordinates Movement::oGetCoords2()
{
	return moCoords2;
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