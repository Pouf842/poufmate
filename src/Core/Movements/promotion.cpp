#include "promotion.h"
#include "Pieces\rook.h"
#include "Pieces\knight.h"
#include "Pieces\bishop.h"
#include "Pieces\queen.h"
#include "Pieces\pawn.h"

using namespace std;

Promotion::Promotion(Position oPos1, Position oPos2, Piece::PIECE_TYPE eNewPieceType) : Movement(oPos1, oPos2)
{
	try
	{
		switch(eNewPieceType)
		{
		  case Piece::PT_ROOK :
			mpoNewPiece = new Rook(eGetPlayerColor());
			break;
		  case Piece::PT_KNIGHT :
			mpoNewPiece = new Knight(eGetPlayerColor());
			break;
		  case Piece::PT_BISHOP :
			mpoNewPiece = new Bishop(eGetPlayerColor());
			break;
		  case Piece::PT_QUEEN :
			mpoNewPiece = new Queen(eGetPlayerColor());
			break;
		  default :
			throw exception("Unknown type of piece");
			break;
		}
	}
	catch(exception & e)
	{
		cout << __FUNCTION__ << ":" << __LINE__ << endl;
		throw e;
	}
}

void Promotion::CancelMovement()
{
	Movement::CancelMovement();
	spoBoard->SetPiece(moPos1, mpoMovingPiece);

	if(mpoNewPiece)	// The new piece doesn't exists yet...anymore... in the past of the future...**hum**
	{
		delete mpoNewPiece;
		mpoNewPiece = NULL;
	}
}

void Promotion::Execute()
{
	spoBoard->SetPiece(moPos2, mpoNewPiece);
	spoBoard->SetPiece(moPos1, NULL);
}