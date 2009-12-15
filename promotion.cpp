#include "promotion.h"

Promotion::Promotion(Position oPos1, Position oPos2) : Movement(oPos1, oPos2)
{
}

void Promotion::CancelMovement(Board & oBoard) const
{
	delete oBoard.poGetPiece(moPos2);

	Movement::CancelMovement(oBoard);
}