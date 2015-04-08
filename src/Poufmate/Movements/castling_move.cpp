#include "castling_move.h"
#include "Core/board.h"

using namespace std;

CastlingMove::CastlingMove(Position oPos1, Position oPos2) : Movement(oPos1, oPos2)
{
	try
	{
		if(oPos1.mY == 4 && oPos2.mY == 2)		// If the king is moving from 4 to 2 horizontally
			meSide = LEFT;						// It's a left castling
		else if(oPos1.mY == 4 && oPos2.mY == 6)	// Same with 4 to 6
			meSide = RIGHT;						// Right side
		else
			throw exception("This move is not a castling move");

		unsigned int iRookX = (poGetMovingPiece()->eGetColor() == Piece::PC_WHITE ? 7 : 0);	// Castling Rook x coordinate
		unsigned int iRookY = (meSide == RIGHT ? 7 : 0);									// Castling Rook y coordinate

		mpoRook = spoBoard->poGetPiece(Position(iRookX, iRookY));	// The castling rook

		if(!mpoRook
		|| mpoRook->eGetType() != Piece::PT_ROOK
		|| mpoRook->bHasAlreadyMoved())
			throw exception("Your rook has already moved and therefore cannot castling");

		if(poGetMovingPiece()->bHasAlreadyMoved())
			throw exception("Your king has already moved and therefore cannot castling");

		/* Check if the path is cleared
		 * (each squares between the king and the finishing one) is empty
		 */
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
	catch(exception & e)
	{
		cout << __FUNCTION__ << ":" << __LINE__ << endl;
		throw e;
	}
}

void CastlingMove::Execute()
{
	Movement::Execute();	// Execute the movement (move the king only)

	/* Move the rook */
	Position oRook(moPos1.mX, (meSide == RIGHT ? 7 : 0));		// Old position of the rook
	Position oRookNewPos(moPos1.mX, (meSide == RIGHT ? 5 : 3));	// New position of the rook (depends on the caslting side)

	spoBoard->MovePiece(oRook, oRookNewPos);
}

void CastlingMove::CancelMovement()
{
	Movement::CancelMovement();	// Cancel the castling (move the king only)

	poGetMovingPiece()->SetFirstMove(true);	// The castling is inevitably the first move of the king (see constructor)

	/* Move the rook */
	Position oRook(moPos1.mX, (meSide == RIGHT ? 5 : 3));		// Position of the rook
	Position oRookOldPos(moPos1.mX, (meSide == RIGHT ? 7 : 0));	// Old position of the rook (depends on the caslting side)

	spoBoard->MovePiece(oRook, oRookOldPos);
	mpoRook->SetFirstMove(true);	// The castling is inevitably the first move of the rook (see constructor)
}