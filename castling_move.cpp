#include "castling_move.h"
#include "board.h"

CastlingMove::CastlingMove(Position oPos1, Position oPos2) : Movement(oPos1, oPos2)
{
	if(oPos1.mY == 4 && oPos2.mY == 2)
		meSide = LEFT;
	else if(oPos1.mY == 4 && oPos2.mY == 6)
		meSide = RIGHT;
	else
		throw exception("This move is not a castling move");

	unsigned int iRookX = (poGetMovingPiece()->eGetColor() == Piece::WHITE ? 7 : 0);
	unsigned int iRookY = (meSide == RIGHT ? 7 : 0);

	mpoRook = spoBoard->poGetPiece(Position(iRookX, iRookY));

	if(!mpoRook
	|| mpoRook->eGetType() != Piece::ROOK
	|| mpoRook->bHasAlreadyMoved())
		throw exception("Your rook has already moved and therefore cannot caslting");

	if(poGetMovingPiece()->bHasAlreadyMoved())
		throw exception("Your king has already moved and therefore cannot castling");

	switch(meSide)
	{
	  case RIGHT :
		for(unsigned int j = moPos1.mY + 1; j <= 6; ++j)
		{
			if(!spoBoard->bIsSquareEmpty(moPos1.mX, j))
				throw exception("The pass is obstructed");
		}
		break;
	  case LEFT :
		for(unsigned int j = moPos1.mY - 1; j >= 2; --j)
		{
			if(!spoBoard->bIsSquareEmpty(moPos1.mX, j))
				throw exception("The pass is obstructed");
		}
		break;
	  default :
		break;
	}
}

void CastlingMove::Execute()
{
	Position oRook(moPos1.mX, (meSide == RIGHT ? 7 : 0));
	Position oRookNewPos(moPos1.mX, (meSide == RIGHT ? 5 : 3));

	spoBoard->MovePiece(moPos1, moPos2);
	spoBoard->MovePiece(oRook, oRookNewPos);
}

void CastlingMove::CancelMovement(Board & oBoard) const
{
	oBoard.SetPiece(oGetCoords1(), poGetMovingPiece());
	oBoard.SetPiece(oGetCoords2(), 0);

	poGetMovingPiece()->SetFirstMove(true);

	unsigned int iXKing = (eGetPlayerColor() == Piece::WHITE ? 7 : 0);

	unsigned int iRookOldY = 0;
	unsigned int iRookNewY = 0;

	switch(meSide)
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

	oBoard.SetPiece(Position(iXKing, iRookOldY), 0);
	oBoard.SetPiece(Position(iXKing, iRookNewY), mpoRook);
	mpoRook->SetFirstMove(true);
}