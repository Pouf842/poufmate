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

bool Pawn::bIsMovementCorrect(Position oPos1, Position oPos2, const Board & oBoard) const
{
	if(oPos1 == oPos2)
		return true;

	int X1 = oPos1.mX;
	int Y1 = oPos1.mY;
	int X2 = oPos2.mX;
	int Y2 = oPos2.mY;

	/* The black pawn's move forward by increasing the X,
	 * wether the white ones decreased it
	 */
	int iFactor = (eGetColor() == Piece::WHITE ? -1 : 1);

	if((X2 - X1) * iFactor == 2 && Y2 == Y1)	// If the movement is of two sqaure forward, and none on sides
	{
		if(bHasAlreadyMoved())	// If the pawn has already moved (it's not his first move)
			return false;		// The movement is not possible

		if(oBoard.bIsSquareEmpty(X1 + iFactor, Y1) && oBoard.bIsSquareEmpty(X1 + 2 * iFactor, Y1))	// If the two squares are empty
			return true;		// The movement is correct
	}
	else if((X2 - X1) * iFactor == 1 && Y2 == Y1)	// If the movement is of one square forward
	{
		if(oBoard.bIsSquareEmpty(X1 + iFactor, Y1))	// and the square is empty
		{
			return true;		// The movement is correct
		}
	}
	else if((X2 - X1) * iFactor == 1 && abs(Y2 - Y1) == 1)	// If the movement is of one square in diagonal
	{
		if(!oBoard.bIsSquareEmpty(oPos2) && oBoard.eGetSquareColor(oPos2) != eGetColor())	// and the move is a capture (there is a piece of a different color on the finishing square)
			return true;		// The movement is correct
	}

	return false;	// For any other combination of positions, the movement is not correct
}