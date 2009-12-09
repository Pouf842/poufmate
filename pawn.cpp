#include "pawn.h"
#include <math.h>
#include <algorithm>
#include "board.h"

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

bool Pawn::bIsmovementCorrect(int X1, int Y1, int X2, int Y2, const Board & oBoard) const
{
	if(X1 == X2 && Y1 == Y2)
		return true;

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
		if(!oBoard.bIsSquareEmpty(X2, Y2) && oBoard.eGetSquareColor(X2, Y2) != eGetColor())
			return true;

	return false;
}