#include "promotion.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "pawn.h"

using namespace std;

Promotion::Promotion(Position oPos1, Position oPos2, Piece::PieceType eNewPieceType) : Movement(oPos1, oPos2)
{
	switch(eNewPieceType)
	{
	  case Piece::ROOK :
		mpoNewPiece = new Rook(eGetPlayerColor());
		break;
	  case Piece::KNIGHT :
		mpoNewPiece = new Knight(eGetPlayerColor());
		break;
	  case Piece::BISHOP :
		mpoNewPiece = new Bishop(eGetPlayerColor());
		break;
	  case Piece::QUEEN :
		mpoNewPiece = new Queen(eGetPlayerColor());
		break;
	  default :
		throw exception("Unknown type of piece");
		break;
	}	
}

Promotion::Promotion(Position oPos1, Position oPos2, char cType) : Movement(oPos1, oPos2)
{
	switch(cType)
	{
	  case 'R' :
	  case 'r' :
		mpoNewPiece = new Rook(eGetPlayerColor());
		break;
	  case 'N' :
	  case 'n' :
		mpoNewPiece = new Knight(eGetPlayerColor());
		break;
	  case 'B' :
	  case 'b' :
		mpoNewPiece = new Bishop(eGetPlayerColor());
		break;
	  case 'Q' :
	  case 'q' :
		mpoNewPiece = new Queen(eGetPlayerColor());
		break;
	  default :
		throw exception((string("Unknown type of piece") + cType).c_str());
		break;
	}	
}

void Promotion::CancelMovement()
{
	Movement::CancelMovement();

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