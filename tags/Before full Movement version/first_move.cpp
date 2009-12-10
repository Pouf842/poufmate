#include "first_move.h"
#include "board.h"

FirstMove::FirstMove(Coordinates oCoords1, Coordinates oCoords2,
					 Piece * poMovingPiece, Piece * poCapturedPiece) : Movement(oCoords1, oCoords2, poMovingPiece, poCapturedPiece)
{
}

void FirstMove::CancelMovement(Board & oBoard) const
{
	oBoard.SetPiece(oGetCoords1(), poGetMovingPiece());
	oBoard.SetPiece(oGetCoords2(), poGetCapturedPiece());

	poGetMovingPiece()->SetFirstMove(true);
}