#include "promotion.h"

Promotion::Promotion(Position oPos1, Position oPos2) : Movement(oPos1, oPos2)
{
}

void Promotion::CancelMovement(Board & oBoard) const
{
	Movement::CancelMovement(oBoard);

	delete oBoard.poGetPiece(moPos2);
}