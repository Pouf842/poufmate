#include "castling_move.h"
#include "board.h"

CastlingMove::CastlingMove(Position oPos1, Position oPos2, Piece * poMovingPiece) : Movement(oPos1, oPos2, poMovingPiece, 0)
{
	if(oPos1.mY == 4 && oPos2.mY == 2)
		meSize = LEFT;
	else if(oPos1.mY == 4 && oPos2.mY == 6)
		meSize = RIGHT;
}

void CastlingMove::CancelMovement(Board & oBoard) const
{
	oBoard.SetPiece(oGetCoords1(), poGetMovingPiece());
	oBoard.SetPiece(oGetCoords2(), 0);

	poGetMovingPiece()->SetFirstMove(true);

	unsigned int iXKing = (eGetPlayerColor() == Piece::WHITE ? 7 : 0);

	Piece * poRook = 0;
	unsigned int iRookOldY = 0;
	unsigned int iRookNewY = 0;

	switch(meSize)
	{
	  case LEFT :
		iRookOldY = 3;
		iRookNewY = 0;
		break;
	  case RIGHT :
		iRookOldY = 5;
		iRookNewY = 7;
		break;
	}

	poRook = oBoard.poGetPiece(Position(iXKing, iRookOldY));
	oBoard.SetPiece(Position(iXKing, iRookOldY), 0);
	oBoard.SetPiece(Position(iXKing, iRookNewY), poRook);
	poRook->SetFirstMove(true);
}