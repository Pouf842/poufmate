#include "rook.h"
#include "board.h"
#include "position.h"

Rook::Rook(Piece::Color eNewColor)
{
	meColor = eNewColor;
	mbFirstMove = true;
	meType = Piece::ROOK;
}

bool Rook::bIsMovementCorrect(Position oPos1, Position oPos2, const Board & oBoard) const
{
	if(oPos1 == oPos2)
		return true;

	int X1 = oPos1.mX;
	int Y1 = oPos1.mY;
	int X2 = oPos2.mX;
	int Y2 = oPos2.mY;

	if(X1 != X2 && Y1 != Y2)	// If the move is neither horizontal nor vertical
		return false;			// The movement is not possible
	else if(X1 == X2)			// Horizontal move
	{
		int iStep = (Y2 > Y1 ? 1 : -1);	// Left or right

		/* For each squares on the path */
		for(unsigned int i = Y1 + iStep; i != Y2; i += iStep)
			if(!oBoard.bIsSquareEmpty(X1, i))	// If the square is not empty
				return false;					// The movement is not possible
	}
	else if(Y1 == Y2)			// Vertical move
	{
		int iStep = (X2 > X1 ? 1 : -1);	// Forward or backward

		/* For each sqaures on the path */
		for(unsigned int i = X1 + iStep; i != X2; i += iStep)
			if(!oBoard.bIsSquareEmpty(i, Y1))	// If the square is not empty
				return false;					// The movement is not correct
	}

	return true;	// If no precedent verifications failed, the movement is correct
}