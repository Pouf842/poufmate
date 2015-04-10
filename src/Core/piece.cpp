#include "piece.h"

Piece::PIECE_COLOR Piece::eGetColor() const
{
	return meColor;
}

void Piece::SetFirstMove(bool bFirstMove)
{
	mbFirstMove = bFirstMove;
}

bool Piece::bHasAlreadyMoved() const
{
	return !bIsFirstMove();
}

bool Piece::bIsFirstMove() const
{
	return mbFirstMove;
}

Piece::PIECE_TYPE Piece::eGetType() const
{
	return meType;
}

std::ostream & operator<<(std::ostream & out, const Piece & piece)
{
	std::string strPiece;

	strPiece = (piece.eGetColor() == Piece::PC_WHITE ? "White " : "Black ");
	
	switch(piece.eGetType())
	{
		case Piece::PT_PAWN:
			strPiece += "pawn";
			break;
		case Piece::PT_ROOK:
			strPiece += "rook";
			break;
		case Piece::PT_KNIGHT:
			strPiece += "knight";
			break;
		case Piece::PT_BISHOP:
			strPiece += "bishop";
			break;
		case Piece::PT_QUEEN:
			strPiece += "queen";
			break;
		case Piece::PT_KING:
			strPiece += "king";
			break;
		case Piece::PT_NONE:
			strPiece += "nothing";
			break;
		default:
			break;
	}

	out << strPiece;

	return out;
}