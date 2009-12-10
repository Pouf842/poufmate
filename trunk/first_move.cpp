#include "first_move.h"
#include "board.h"

FirstMove::FirstMove(Position oPos1, Position oPos2,
					 Piece * poMovingPiece, Piece * poCapturedPiece) : Movement(oPos1, oPos2, poMovingPiece, poCapturedPiece)
{
}

void FirstMove::CancelMovement(Board & oBoard) const
{
	oBoard.SetPiece(oGetCoords1(), poGetMovingPiece());
	oBoard.SetPiece(oGetCoords2(), poGetCapturedPiece());

	poGetMovingPiece()->SetFirstMove(true);
}