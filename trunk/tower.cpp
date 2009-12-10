#include "tower.h"
#include "board.h"
#include "coordinates.h"

Tower::Tower(Piece::Color eNewColor)
{
	meColor = eNewColor;
	mbFirstMove = true;
	meType = Piece::TOWER;
}

char Tower::cGetChar() const
{
	if(eGetColor() == WHITE)
		return 'T';
	else
		return 't';
}

bool Tower::bIsmovementCorrect(Coordinates oCoords1, Coordinates oCoords2, const Board & oBoard) const
{
	if(oCoords1 == oCoords2)
		return true;

	int X1 = oCoords1.mX;
	int Y1 = oCoords1.mY;
	int X2 = oCoords2.mX;
	int Y2 = oCoords2.mY;

	if(X1 != X2 && Y1 != Y2)
		return false;
	else if(X1 == X2)
	{
		int iStep = (Y2 > Y1 ? 1 : -1);

		for(unsigned int i = Y1 + iStep; i != Y2; i += iStep)
			if(!oBoard.bIsSquareEmpty(X1, i))
				return false;
	}
	else if(Y1 == Y2)
	{
		int iStep = (X2 > X1 ? 1 : -1);

		for(unsigned int i = X1 + iStep; i != X2; i += iStep)
			if(!oBoard.bIsSquareEmpty(i, Y1))
				return false;
	}

	return false;
}