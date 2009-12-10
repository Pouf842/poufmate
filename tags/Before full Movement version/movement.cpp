#include "movement.h"
#include "board.h"

Movement::Movement(Coordinates oCoords1, Coordinates oCoords2,
				   Piece * poMovingPiece, Piece * poCapturedPiece) : moCoords1(oCoords1), moCoords2(oCoords2)
{
	mpoMovingPiece = poMovingPiece;
	mpoCapturedPiece = poCapturedPiece;
}

Coordinates Movement::oGetCoords1() const
{
	return moCoords1;
}

Coordinates Movement::oGetCoords2() const
{
	return moCoords2;
}

Piece * Movement::poGetMovingPiece() const
{
	return mpoMovingPiece;
}

Piece * Movement::poGetCapturedPiece() const
{
	return mpoCapturedPiece;
}

Piece::Color Movement::eGetPlayerColor() const
{
	return poGetMovingPiece()->eGetColor();
}

void Movement::CancelMovement(Board & oBoard) const
{
	oBoard.SetPiece(oGetCoords1(), poGetMovingPiece());
	oBoard.SetPiece(oGetCoords2(), poGetCapturedPiece());
}