#include "knight.h"
#include <math.h>
#include "board.h"
#include "position.h"

Knight::Knight(Piece::Color eNewColor)
{
	meColor = eNewColor;
	mbFirstMove = true;
	meType = Piece::KNIGHT;
}

bool Knight::bIsMovementCorrect(Position oPos1, Position oPos2, const Board & oBoard) const
{
	if(oPos1 == oPos2)
		return true;

	int X1 = oPos1.mX;
	int Y1 = oPos1.mY;
	int X2 = oPos2.mX;
	int Y2 = oPos2.mY;

	if(abs(X2 - X1) == 1 && abs(Y2 - Y1) == 2	// If the move is of two squares on an axe, and one on the other
	|| abs(X2 - X1) == 2 && abs(Y2 - Y1) == 1)
		return true;		// The movement is correct

	return false;
}