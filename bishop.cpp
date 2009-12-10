#include "Bishop.h"
#include "math.h"
#include "board.h"
#include "coordinates.h"

Bishop::Bishop(Piece::Color eNewColor)
{
	meColor = eNewColor;
	mbFirstMove = true;
	meType = Piece::BISHOP;
}

char Bishop::cGetChar() const
{
	if(eGetColor() == Piece::WHITE)
		return 'B';
	else
		return 'b';
}

bool Bishop::bIsMovementCorrect(Coordinates oCoords1, Coordinates oCoords2, const Board & oBoard) const
{
	if(oCoords1 == oCoords2)
		return true;

	int X1 = oCoords1.mX;
	int Y1 = oCoords1.mY;
	int X2 = oCoords2.mX;
	int Y2 = oCoords2.mY;

	if(abs(X2 - X1) == abs(Y2 - Y1))
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