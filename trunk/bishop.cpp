#include "Bishop.h"
#include "math.h"
#include "board.h"

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

bool Bishop::bIsmovementCorrect(int X1, int Y1, int X2, int Y2, const Board & oBoard) const
{
	if(X1 == X2 && Y1 == Y2)
		return true;

	if(!oBoard.bIsSquareEmpty(X2, Y2) && oBoard.eGetSquareColor(X2, Y2) == eGetColor())
		return false;

	if(X1 == X2 && Y1 == Y2)
		return true;
	else if(abs(X2 - X1) == abs(Y2 - Y1))
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