#include <math.h>
#include "en_passant.h"
#include "../Pieces/pawn.h"

using namespace std;

EnPassant::EnPassant(Position oPos1, Position oPos2, Movement * poLastMovement) : Movement(oPos1, oPos2)
{
	try
	{
		if(abs(oPos2.mX - oPos1.mX) != 1
		|| abs(oPos2.mY - oPos1.mY) != 1)
			throw exception("This move is not an en passant");

		if(spoBoard->bIsSquareEmpty(oPos1.mX, oPos2.mY))
			throw exception("There is no piece to capture");

		if(spoBoard->eGetSquareType(Position(oPos1.mX, oPos2.mY)) != Piece::PT_PAWN)
			throw exception("The piece to capture must be a pawn");

		if(oPos2.mY != poLastMovement->oGetCoords2().mY
		|| !poLastMovement->bIs2SquaresPawnMove())
			throw exception("En passant can only be executed directly after a two steps move by the captured pawn");

		mpoCapturedPiece = spoBoard->poGetPiece(oPos1.mX, oPos2.mY);
	}
	catch(exception & e)
	{
		cout << __FUNCTION__ << ":" << __LINE__ << endl;
		throw e;
	}
}

void EnPassant::Execute()
{
	spoBoard->MovePiece(moPos1, moPos2);
	spoBoard->SetPiece(Position(moPos1.mX, moPos2.mY), NULL);
}

void EnPassant::CancelMovement()
{
	spoBoard->MovePiece(moPos2, moPos1);
	spoBoard->SetPiece(Position(moPos1.mX, moPos2.mY), mpoCapturedPiece);
}