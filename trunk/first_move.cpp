#include "first_move.h"
#include "board.h"

FirstMove::FirstMove(Position oPos1, Position oPos2) : Movement(oPos1, oPos2)
{
}

void FirstMove::CancelMovement(Board & oBoard) const
{
	oBoard.SetPiece(oGetCoords1(), poGetMovingPiece());
	oBoard.SetPiece(oGetCoords2(), poGetCapturedPiece());

	poGetMovingPiece()->SetFirstMove(true);
}