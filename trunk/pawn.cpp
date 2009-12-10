#include "pawn.h"
#include <math.h>
#include <algorithm>
#include "board.h"
#include "position.h"

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

bool Pawn::bIsMovementCorrect(Position oPos1, Position oPos2, const Board & oBoard) const
{
	if(oPos1 == oPos2)
		return true;

	int X1 = oPos1.mX;
	int Y1 = oPos1.mY;
	int X2 = oPos2.mX;
	int Y2 = oPos2.mY;

	int iFactor = (eGetColor() == Piece::WHITE ? -1 : 1);

	if((X2 - X1) * iFactor == 2 && Y2 == Y1)
	{
		if(bHasAlreadyMoved())
			return false;

		if(oBoard.bIsSquareEmpty(X1 + iFactor, Y1) && oBoard.bIsSquareEmpty(X1 + 2 * iFactor, Y1))
			return true;
	}
	else if((X2 - X1) * iFactor == 1 && Y2 == Y1)
	{
		if(oBoard.bIsSquareEmpty(X1 + iFactor, Y1))
			return true;
	}
	else if((X2 - X1) * iFactor == 1 && abs(Y2 - Y1) == 1)
		if(!oBoard.bIsSquareEmpty(oPos2) && oBoard.eGetSquareColor(oPos2) != eGetColor())
			return true;

	return false;
}