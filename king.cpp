#include "King.h"
#include "board.h"
#include "coordinates.h"

King::King(Piece::Color eNewColor)
{
	meColor = eNewColor;
	mbFirstMove = true;
	meType = Piece::KING;
}

char King::cGetChar() const
{
	if(eGetColor() == Piece::WHITE)
		return 'K';
	else
		return 'k';
}

bool King::bIsMovementCorrect(Coordinates oCoords1, Coordinates oCoords2, const Board & oBoard) const
{
	if(oCoords1 == oCoords2)
		return true;

	int X1 = oCoords1.mX;
	int Y1 = oCoords1.mY;
	int X2 = oCoords2.mX;
	int Y2 = oCoords2.mY;

	if(abs(X2 - X1) > 1
	|| abs(Y2 - Y1) > 1)
		return false;

	return true;
}