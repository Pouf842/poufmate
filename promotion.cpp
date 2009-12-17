#include "promotion.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "pawn.h"

Promotion::Promotion(Position oPos1, Position oPos2, Piece::PieceType eNewPieceType) : Movement(oPos1, oPos2)
{
	switch(eNewPieceType)
	{
	  case Piece::ROOK :
		moNewPiece = new Rook(eGetPlayerColor());
		break;
	  case Piece::KNIGHT :
		moNewPiece = new Knight(eGetPlayerColor());
		break;
	  case Piece::BISHOP :
		moNewPiece = new Bishop(eGetPlayerColor());
		break;
	  case Piece::QUEEN :
		moNewPiece = new Queen(eGetPlayerColor());
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
		moNewPiece = new Rook(eGetPlayerColor());
		break;
	  case 'N' :
	  case 'n' :
		moNewPiece = new Knight(eGetPlayerColor());
		break;
	  case 'B' :
	  case 'b' :
		moNewPiece = new Bishop(eGetPlayerColor());
		break;
	  case 'Q' :
	  case 'q' :
		moNewPiece = new Queen(eGetPlayerColor());
		break;
	  default :
		throw exception((string("Unknown type of piece") + cType).c_str());
		break;
	}	
}

void Promotion::CancelMovement()
{
	Movement::CancelMovement();

	if(moNewPiece)	// The new piece doesn't exists yet...anymore... in the past of the future...**hum**
	{
		delete moNewPiece;
		moNewPiece = NULL;
	}
}