#include "first_move.h"
#include "Core\board.h"

FirstMove::FirstMove(Position oPos1, Position oPos2) : Movement(oPos1, oPos2)
{
}

void FirstMove::CancelMovement()
{
	Movement::CancelMovement();

	poGetMovingPiece()->SetFirstMove(true);
}