#include "Bishop.h"
#include "math.h"
#include "board.h"
#include "position.h"

Bishop::Bishop(Piece::Color eNewColor)
{
	meColor = eNewColor;
	mbFirstMove = true;
	meType = Piece::BISHOP;
}

bool Bishop::bIsMovementCorrect(Position oPos1, Position oPos2, const Board & oBoard) const
{
	if(oPos1 == oPos2)
		return true;

	int X1 = oPos1.mX;
	int Y1 = oPos1.mY;
	int X2 = oPos2.mX;
	int Y2 = oPos2.mY;

	if(abs(X2 - X1) == abs(Y2 - Y1))	// If the move is a diagonal
	{
		int iStep = (X2 > X1 ? 1 : -1);	// Forward or backward
		int jStep = (Y2 > Y1 ? 1 : -1);	// Left or right

		/* For each squares on the path */
		for(unsigned int i = X1 + iStep, j = Y1 + jStep; i != X2 && j != Y2; i += iStep, j += jStep)
			if(!oBoard.bIsSquareEmpty(i, j))	// If the square is not empty
				return false;					// The movement is not correct

		return true;
	}

	return false;	// If the move is not a diagonal, it's note valid
}