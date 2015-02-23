#include "Pieces\King.h"
#include "Core\board.h"
#include "Core\position.h"

King::King(Piece::PIECE_COLOR eNewColor)
{
	meColor = eNewColor;
	mbFirstMove = true;
	meType = Piece::PT_KING;
}

bool King::bIsMovementCorrect(Position oPos1, Position oPos2, const Board & oBoard) const
{
	if(oPos1 == oPos2)
		return true;

	int X1 = oPos1.mX;
	int Y1 = oPos1.mY;
	int X2 = oPos2.mX;
	int Y2 = oPos2.mY;

	if((abs(X2 - X1) <= 1	// If the move is of one square
	&& abs(Y2 - Y1) <= 1)
	|| ((X1 == X2) && (Y1 == 4 && (Y2 == 2 || Y2 == 6))))	// Or if it is a castling move
		return true;	// The movement is correct

	return false;	// In any other case, the movement is not possible
}