#include "knight.h"
#include <math.h>
#include "board.h"
#include "coordinates.h"

Knight::Knight(Piece::Color eNewColor)
{
	meColor = eNewColor;
	mbFirstMove = true;
	meType = Piece::KNIGHT;
}

char Knight::cGetChar() const
{
	if(eGetColor() == Piece::WHITE)
		return 'N';
	else
		return 'n';
}

bool Knight::bIsmovementCorrect(Coordinates oCoords1, Coordinates oCoords2, const Board & oBoard) const
{
	if(oCoords1 == oCoords2)
		return true;

	int X1 = oCoords1.mX;
	int Y1 = oCoords1.mY;
	int X2 = oCoords2.mX;
	int Y2 = oCoords2.mY;

	if(abs(X2 - X1) == 1 && abs(Y2 - Y1) == 2
	|| abs(X2 - X1) == 2 && abs(Y2 - Y1) == 1)
		return true;

	return false;
}