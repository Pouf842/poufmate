#include "King.h"
#include "board.h"

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

bool King::bIsmovementCorrect(int X1, int Y1, int X2, int Y2, const Board & oBoard) const
{
	if(X1 == X2 && Y1 == Y2)
		return true;

	if(!oBoard.bIsSquareEmpty(X2, Y2) && oBoard.eGetSquareColor(X2, Y2) == eGetColor())
		return false;

	if(abs(X2 - X1) > 1
	|| abs(Y2 - Y1) > 1)
		return false;

	return true;
}