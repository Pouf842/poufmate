#include "promotion.h"

Promotion::Promotion(Position oPos1, Position oPos2, Piece * poPiece1, Piece * poPiece2) : Movement(oPos1, oPos2, poPiece1, poPiece2)
{
}

void Promotion::CancelMovement(Board & oBoard) const
{
	delete oBoard.poGetPiece(moPos2);

	Movement::CancelMovement(oBoard);
}