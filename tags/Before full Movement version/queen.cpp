#include "Queen.h"
#include <math.h>
#include "board.h"
#include <exception>
#include "position.h"

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

bool Queen::bIsMovementCorrect(Position oPos1, Position oPos2, const Board & oBoard) const
{
	if(oPos1 == oPos2)
		return true;

	int X1 = oPos1.mX;
	int Y1 = oPos1.mY;
	int X2 = oPos2.mX;
	int Y2 = oPos2.mY;

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
	}
	else
		return false;

	return true;
}