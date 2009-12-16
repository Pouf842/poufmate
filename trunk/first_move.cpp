#include "first_move.h"
#include "board.h"

FirstMove::FirstMove(Position oPos1, Position oPos2) : Movement(oPos1, oPos2)
{
}

void FirstMove::CancelMovement(Board & oBoard) const
{
	Movement::CancelMovement(oBoard);

	poGetMovingPiece()->SetFirstMove(true);
}