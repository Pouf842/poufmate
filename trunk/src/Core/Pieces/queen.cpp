#include "Queen.h"
#include <math.h>
#include <exception>
#include "Core\board.h"
#include "Core\position.h"

using namespace std;

Queen::Queen(Piece::PIECE_COLOR eNewColor)
{
	meColor = eNewColor;
	mbFirstMove = true;
	meType = Piece::PT_QUEEN;
}

bool Queen::bIsMovementCorrect(Position oPos1, Position oPos2, const Board & oBoard) const
{
	if(oPos1 == oPos2)
		return true;

	int X1 = oPos1.mX;
	int Y1 = oPos1.mY;
	int X2 = oPos2.mX;
	int Y2 = oPos2.mY;

	if(X1 == X2)	// Horizontal move
	{
		int iStep = (Y2 > Y1 ? 1 : -1);	// Left or right

		/* For each squares on the path */
		for(unsigned int i = Y1 + iStep; i != Y2; i += iStep)
			if(!oBoard.bIsSquareEmpty(X1, i))	// If the square is not empty
				return false;					// The movement is not possible
	}
	else if(Y1 == Y2)	// Vertical move
	{
		int iStep = (X2 > X1 ? 1 : -1);	// Forward or backward

		/* For each squares on the path */
		for(unsigned int i = X1 + iStep; i != X2; i += iStep)
			if(!oBoard.bIsSquareEmpty(i, Y1))	// If the square is not empty
				return false;					// The movement is not possible
	}
	else if(abs(Y2 - Y1) == abs(X2 - X1))	// Diagonal move
	{
		int iStep = (X2 > X1 ? 1 : -1);	// Forward or backward
		int jStep = (Y2 > Y1 ? 1 : -1);	// Left or right

		/* For each squares on the path */
		for(unsigned int i = X1 + iStep, j = Y1 + jStep; i != X2 && j != Y2; i += iStep, j += jStep)
			if(!oBoard.bIsSquareEmpty(i, j))	// If the square is not empty
				return false;					// The movement is not possible
	}
	else
		return false;	// If the movement is neither horizontal, vertical or diagonal, it's not correct

	return true;	// If no error was encountered in the precedent treatment, the movement is correct
}