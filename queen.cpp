#include "Queen.h"
#include <math.h>
#include "board.h"
#include <exception>
#include "coordinates.h"

using namespace std;

Queen::Queen(Piece::Color eNewColor)
{
	meColor = eNewColor;
	mbFirstMove = true;
	meType = Piece::QUEEN;
}

char Queen::cGetChar() const
{
	if(eGetColor() == Piece::WHITE)
		return 'Q';
	else
		return 'q';
}

bool Queen::bIsmovementCorrect(Coordinates oCoords1, Coordinates oCoords2, const Board & oBoard) const
{
	if(oCoords1 == oCoords2)
		return true;

	int X1 = oCoords1.mX;
	int Y1 = oCoords1.mY;
	int X2 = oCoords2.mX;
	int Y2 = oCoords2.mY;

	if(X1 == X2)
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
	else if(abs(Y2 - Y1) == abs(X2 - X1))
	{
		int iStep = (X2 > X1 ? 1 : -1);
		int jStep = (Y2 > Y1 ? 1 : -1);

		for(unsigned int i = X1 + iStep, j = Y1 + jStep; i != X2 && j != Y2; i += iStep, j += jStep)
			if(!oBoard.bIsSquareEmpty(i, j))
				return false;

		return true;
	}

	return false;
}