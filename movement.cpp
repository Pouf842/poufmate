#include "movement.h"
#include "board.h"

Board * Movement::spoBoard = NULL;

Movement::Movement(Position oPos1, Position oPos2) : moPos1(oPos1), moPos2(oPos2)
{
	if(!spoBoard)
		throw exception("Board is not defined. Call SetBoard before");

	mpoMovingPiece = spoBoard->poGetPiece(moPos1);
	mpoCapturedPiece = spoBoard->poGetPiece(moPos2);
}

void Movement::SetBoard(Board * oNewBoard)
{
	spoBoard = oNewBoard;
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

void Movement::Execute()
{

}