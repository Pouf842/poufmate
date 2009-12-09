#include "knight.h"
#include <math.h>
#include "board.h"

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

bool Knight::bIsmovementCorrect(int X1, int Y1, int X2, int Y2, const Board & oBoard) const
{
	if(X1 == X2 && Y1 == Y2)
		return true;

	if(abs(X2 - X1) == 1 && abs(Y2 - Y1) == 2
	|| abs(X2 - X1) == 2 && abs(Y2 - Y1) == 1)
		if(oBoard.bIsSquareEmpty(X2, Y2) || oBoard.eGetSquareColor(X2, Y2) != eGetColor())
			return true;
		else
			return false;
	else
		return false;
}