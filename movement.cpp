#include "movement.h"
#include "board.h"

Movement::Movement(Position oPos1, Position oPos2,
				   Piece * poMovingPiece, Piece * poCapturedPiece) : moPos1(oPos1), moPos2(oPos2)
{
	mpoMovingPiece = poMovingPiece;
	mpoCapturedPiece = poCapturedPiece;
}

Position Movement::oGetCoords1() const
{
	return moPos1;
}

Position Movement::oGetCoords2() const
{
	return moPos2;
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