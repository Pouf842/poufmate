#include "movement.h"
#include "Core/board.h"

using namespace std;

Board * Movement::spoBoard = NULL;

Movement::Movement(Position oPos1, Position oPos2) : moPos1(oPos1), moPos2(oPos2)
{
	try
	{
		if(!spoBoard)
			throw exception("Board is not defined. Call SetBoard before");

		if(oPos1 == oPos2)
			throw exception("No movement");

		if(spoBoard->bIsSquareEmpty(oPos1))
			throw exception("There is no piece on the starting square");

		if(!spoBoard->bIsSquareEmpty(oPos2) && spoBoard->eGetSquareColor(oPos1) == spoBoard->eGetSquareColor(oPos2))
			throw exception("The two pieces are on the same side");

		if(!spoBoard->poGetPiece(oPos1)->bIsMovementCorrect(oPos1, oPos2, *spoBoard))
			throw exception("Invalid move");

		mpoMovingPiece = spoBoard->poGetPiece(moPos1);
		mpoCapturedPiece = spoBoard->poGetPiece(moPos2);
	}
	catch(exception & e)
	{
		cout << __FUNCTION__ << ":" << __LINE__ << endl;
		throw e;
	}
}

void Movement::SetBoard(Board * oNewBoard)
{
	spoBoard = oNewBoard;
}

Position Movement::oGetCoords1() const
{
	return moPos1;
}

Position Movement::oGetCoords2() const
{
	return moPos2;
}

Piece * Movement::poGetMovingPiece() const
{
	return mpoMovingPiece;
}

Piece * Movement::poGetCapturedPiece() const
{
	return mpoCapturedPiece;
}

Piece::PIECE_COLOR Movement::eGetPlayerColor() const
{
	return poGetMovingPiece()->eGetColor();
}

void Movement::CancelMovement()
{
	spoBoard->MovePiece(oGetCoords2(), oGetCoords1());
	spoBoard->SetPiece(oGetCoords2(), poGetCapturedPiece());
}

void Movement::Execute()
{
	spoBoard->MovePiece(oGetCoords1(), oGetCoords2());
	poGetMovingPiece()->SetFirstMove(false);
}

bool Movement::bIs2SquaresPawnMove() const
{
	return (mpoMovingPiece->eGetType() == Piece::PT_PAWN && abs(moPos1.mX - moPos2.mX) == 2);
}
