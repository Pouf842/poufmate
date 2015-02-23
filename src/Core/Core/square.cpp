#include "square.h"
#include <exception>

using namespace std;

Square::Square() : mpoPiece(0)
{
}

bool Square::bIsEmpty() const
{
	return (mpoPiece == NULL);
}

void Square::SetPiece(Piece * poNewPiece)
{
	mpoPiece = poNewPiece;
}

Piece::PIECE_COLOR Square::eGetPieceColor() const
{
	if(!bIsEmpty())
		return mpoPiece->eGetColor();
	else
		throw exception("Empty square");
}

Piece::PIECE_TYPE Square::eGetPieceType() const
{
	if(!bIsEmpty())
		return mpoPiece->eGetType();
	else
		throw exception("Empty square");
}

Piece * Square::poGetPiece() const
{
	return mpoPiece;
}