#include "pawn.h"
#include <math.h>
#include <algorithm>
#include "board.h"
#include "coordinates.h"

using namespace std;

Pawn::Pawn(Piece::Color eNewColor)
{
	meColor = eNewColor;
	mbFirstMove = true;
	meType = Piece::PAWN;
}

char Pawn::cGetChar() const
{
	if(eGetColor() == Piece::WHITE)
		return 'P';
	else
		return 'p';
}

bool Pawn::bIsmovementCorrect(Coordinates oCoords1, Coordinates oCoords2, const Board & oBoard) const
{
	if(oCoords1 == oCoords2)
		return true;

	int X1 = oCoords1.mX;
	int Y1 = oCoords1.mY;
	int X2 = oCoords2.mX;
	int Y2 = oCoords2.mY;

	int iFactor = (eGetColor() == Piece::WHITE ? -1 : 1);

	if((X2 - X1) * iFactor == 2 && Y2 == Y1)
	{
		if(oBoard.bIsSquareEmpty(X1 + iFactor, Y1) && oBoard.bIsSquareEmpty(X1 + 2 * iFactor, Y1))
			return true;
	}
	else if((X2 - X1) * iFactor == 1 && Y2 == Y1)
	{
		if(oBoard.bIsSquareEmpty(X1 + iFactor, Y1))
			return true;
	}
	else if((X2 - X1) * iFactor == 1 && abs(Y2 - Y1) == 1)
		if(!oBoard.bIsSquareEmpty(oCoords2) && oBoard.eGetSquareColor(oCoords2) != eGetColor())
			return true;

	return false;
}