#include "tower.h"
#include "board.h"

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

bool Tower::bIsmovementCorrect(int X1, int Y1, int X2, int Y2, const Board & oBoard) const
{
	if(X1 == X2 && Y1 == Y2)
		return true;

	if(!oBoard.bIsSquareEmpty(X2, Y2) && oBoard.eGetSquareColor(X2, Y2) == eGetColor())
		return false;

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