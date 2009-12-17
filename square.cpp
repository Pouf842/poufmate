#include "square.h"
#include <exception>

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

Piece::Color Square::eGetPieceColor() const
{
	if(!bIsEmpty())
		return mpoPiece->eGetColor();
	else
		throw std::exception("Empty square");
}

Piece * Square::poGetPiece() const
{
	return mpoPiece;
}